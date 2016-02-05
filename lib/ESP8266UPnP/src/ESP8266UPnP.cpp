#define LWIP_OPEN_SRC
#include "ESP8266UPnP.h"
#include "debug.h"

extern "C" {
#include "osapi.h"
#include "ets_sys.h"
#include "user_interface.h"
}

#include "lwip/opt.h"
#include "lwip/udp.h"
#include "lwip/inet.h"
#include "lwip/igmp.h"
#include "lwip/mem.h"
#include "include/UdpContext.h"

using namespace std;

#define DEBUG_UPnP Serial

static const IPAddress UPnP_MULTICAST_ADDR(239, 255, 255, 250);

static const string ssdp_response_template = "HTTP/1.1 200 OK\r\n"
                                             "EXT:\r\n"
                                             "ST: upnp:rootdevice\r\n";

static const string ssdp_notify_template = "NOTIFY * HTTP/1.1\r\n"
                                           "HOST: 239.255.255.250:1900\r\n"
                                           "NT: upnp:rootdevice\r\n"
                                           "NTS: ssdp:alive\r\n";

static const string ssdp_packet_template =
    "%s" // _ssdp_response_template / _ssdp_notify_template
    "CACHE-CONTROL: max-age=%u\r\n"          // UPnP_INTERVAL
    "SERVER: Arduino/1.0 UPNP/1.1 %s/%s\r\n" // _modelName, _modelNumber
    "USN: uuid:%s\r\n"                       // _uuid
    "LOCATION: http://%u.%u.%u.%u:%u/%s\r\n" // WiFi.localIP(), _port,
                                             // _schemaURL
    "\r\n";

struct UPnPTimer {
  ETSTimer timer;
};

UPnPEnv::UPnPEnv()
    : server(0), timer(new UPnPTimer), port(80), ttl(UPnP_MULTICAST_TTL),
      respondToPort(0), pending(false), delay(0), process_time(0),
      notify_time(0) {
  schemaURL = "upnp/schema.xml";
}

UPnPEnv::~UPnPEnv() { delete timer; }

bool UPnPEnv::begin() {
  pending = false;

  uint32_t chipId = ESP.getChipId();
  char _uuid[37];

  sprintf(_uuid, "38323636-4558-4dda-9188-cda0e6%02x%02x%02x",
          (uint16_t)((chipId >> 16) & 0xff), (uint16_t)((chipId >> 8) & 0xff),
          (uint16_t)chipId & 0xff);

  device.setUuid(_uuid);

#ifdef DEBUG_UPnP
  DEBUG_UPnP.printf("UPnP UUID: %s\n", (char *)_uuid);
#endif

  if (server) {
    server->unref();
    server = 0;
  }

  server = new UdpContext;
  server->ref();

  ip_addr_t ifaddr;
  ifaddr.addr = WiFi.localIP();
  ip_addr_t multicast_addr;
  multicast_addr.addr = (uint32_t)UPnP_MULTICAST_ADDR;
  if (igmp_joingroup(&ifaddr, &multicast_addr) != ERR_OK) {
    DEBUGV("UPnP failed to join igmp group");
    return false;
  }

  if (!server->listen(*IP_ADDR_ANY, UPnP_PORT)) {
    return false;
  }

  server->setMulticastInterface(ifaddr);
  server->setMulticastTTL(ttl);
  server->onRx(std::bind(&UPnPEnv::update, this));
  if (!server->connect(multicast_addr, UPnP_PORT)) {
    return false;
  }

  startTimer();

  return true;
}

void UPnPEnv::send(upnp_method_t method) {
  string MyIp;
  MyIp = char(WiFi.localIP()[0]);
  MyIp += ".";
  MyIp += char(WiFi.localIP()[2]);
  MyIp += ".";
  MyIp += char(WiFi.localIP()[2]);
  MyIp += ".";
  MyIp += char(WiFi.localIP()[3]);

  string buffer;

  if (method == NONE)
    buffer = ssdp_response_template;
  else
    buffer = ssdp_notify_template;

  char tmp[16];
  itoa(UPnP_INTERVAL, tmp, 15);

  buffer += "CACHE-CONTROL: max-age=";
  buffer += tmp;
  buffer += "\r\n";
  buffer += "SERVER: Arduino/1.0 UPNP/1.1 ";
  buffer += device.getModelName();
  buffer += "/";
  buffer += device.getModelNumber();
  buffer += "\r\n";
  buffer += "USN: uuid:";
  buffer += device.getUuid();
  buffer += "\r\n";
  buffer += "LOCATION: http://";
  buffer += MyIp;
  buffer += ":";
  buffer += port;
  buffer += "/";
  buffer += schemaURL;
  buffer += "\r\n";
  buffer += "\r\n";

  string strBuffer = buffer;

  int len = strBuffer.size();

  server->append(strBuffer.c_str(), len);

  ip_addr_t remoteAddr;
  uint16_t remotePort;
  if (method == NONE) {
    remoteAddr.addr = respondToAddr;
    remotePort = respondToPort;
#ifdef DEBUG_UPnP
    DEBUG_UPnP.print("Sending Response to ");
#endif
  } else {
    remoteAddr.addr = UPnP_MULTICAST_ADDR;
    remotePort = UPnP_PORT;
#ifdef DEBUG_UPnP
    DEBUG_UPnP.println("Sending Notify to ");
#endif
  }
#ifdef DEBUG_UPnP
  DEBUG_UPnP.print(IPAddress(remoteAddr.addr));
  DEBUG_UPnP.print(":");
  DEBUG_UPnP.println(remotePort);
#endif

  server->send(&remoteAddr, remotePort);
}

void UPnPEnv::schema(WiFiClient client) {
  client.printf(device.getDeviceXML().c_str());
}

void UPnPEnv::update() {
  if (!pending && server->next()) {
    upnp_method_t method = NONE;

    respondToAddr = server->getRemoteAddress();
    respondToPort = server->getRemotePort();

    typedef enum { METHOD, URI, PROTO, KEY, VALUE, ABORT } states;
    states state = METHOD;

    typedef enum { START, MAN, ST, MX } headers;
    headers header = START;

    uint8_t cursor = 0;
    uint8_t cr = 0;

    char buffer[UPnP_BUFFER_SIZE] = {0};

    while (server->getSize() > 0) {
      char c = server->read();

      (c == '\r' || c == '\n') ? cr++ : cr = 0;

      switch (state) {
      case METHOD:
        if (c == ' ') {
          if (strcmp(buffer, "M-SEARCH") == 0)
            method = SEARCH;
          else if (strcmp(buffer, "NOTIFY") == 0)
            method = NOTIFY;

          if (method == NONE)
            state = ABORT;
          else
            state = URI;
          cursor = 0;

        } else if (cursor < UPnP_METHOD_SIZE - 1) {
          buffer[cursor++] = c;
          buffer[cursor] = '\0';
        }
        break;
      case URI:
        if (c == ' ') {
          if (strcmp(buffer, "*"))
            state = ABORT;
          else
            state = PROTO;
          cursor = 0;
        } else if (cursor < UPnP_URI_SIZE - 1) {
          buffer[cursor++] = c;
          buffer[cursor] = '\0';
        }
        break;
      case PROTO:
        if (cr == 2) {
          state = KEY;
          cursor = 0;
        }
        break;
      case KEY:
        if (cr == 4) {
          pending = true;
          process_time = millis();
        } else if (c == ' ') {
          cursor = 0;
          state = VALUE;
        } else if (c != '\r' && c != '\n' && c != ':' &&
                   cursor < UPnP_BUFFER_SIZE - 1) {
          buffer[cursor++] = c;
          buffer[cursor] = '\0';
        }
        break;
      case VALUE:
        if (cr == 2) {
          switch (header) {
          case START:
            break;
          case MAN:
#ifdef DEBUG_UPnP
            DEBUG_UPnP.printf("MAN: %s\n", (char *)buffer);
#endif
            break;
          case ST:
            if (strcmp(buffer, "ssdp:all")) {
              state = ABORT;
#ifdef DEBUG_UPnP
              DEBUG_UPnP.printf("REJECT: %s\n", (char *)buffer);
#endif
            }
            // if the search type matches our type, we should respond instead of
            // ABORT
            if (strcmp(buffer, device.getDeviceType().c_str()) == 0) {
              pending = true;
              process_time = millis();
              state = KEY;
            }
            break;
          case MX:
            delay = random(0, atoi(buffer)) * 1000L;
            break;
          }

          if (state != ABORT) {
            state = KEY;
            header = START;
            cursor = 0;
          }
        } else if (c != '\r' && c != '\n') {
          if (header == START) {
            if (strncmp(buffer, "MA", 2) == 0)
              header = MAN;
            else if (strcmp(buffer, "ST") == 0)
              header = ST;
            else if (strcmp(buffer, "MX") == 0)
              header = MX;
          }

          if (cursor < UPnP_BUFFER_SIZE - 1) {
            buffer[cursor++] = c;
            buffer[cursor] = '\0';
          }
        }
        break;
      case ABORT:
        pending = false;
        delay = 0;
        break;
      }
    }
  }

  if (pending && (millis() - process_time) > delay) {
    pending = false;
    delay = 0;
    send(NONE);
  } else if (notify_time == 0 ||
             (millis() - notify_time) > (UPnP_INTERVAL * 1000L)) {
    notify_time = millis();
    send(NOTIFY);
  }

  if (pending) {
    while (server->next())
      server->flush();
  }
}

void UPnPEnv::setSchemaURL(string url) { schemaURL = url; }

void UPnPEnv::setDevice(UPnPDevice inputDevice) { device = inputDevice; }
UPnPDevice UPnPEnv::getDevice() { return device; }

void UPnPEnv::setHTTPPort(uint16_t inPort) { port = inPort; }

void UPnPEnv::setTTL(const uint8_t inTtl) { ttl = inTtl; }

void UPnPEnv::onTimerStatic(UPnPEnv *self) { self->update(); }

void UPnPEnv::startTimer() {
  ETSTimer *tm = &(timer->timer);
  const int interval = 1000;
  os_timer_disarm(tm);
  os_timer_setfn(tm, reinterpret_cast<ETSTimerFunc *>(&UPnPEnv::onTimerStatic),
                 reinterpret_cast<void *>(this));
  os_timer_arm(tm, interval, 1 /* repeat */);
}

UPnPEnv UPnP;
