/*
ESP8266 Simple Service Discovery
Copyright (c) 2015 Hristo Gochkov

Original (Arduino) version by Filippo Sallemi, July 23, 2014.
Can be found at: https://github.com/nomadnt/uUPnP

License (MIT license):
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.

*/

#ifndef ESP8266UPNP_H
#define ESP8266UPNP_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "UPnPDevice.h"
#include <WiFiUdp.h>
#include <string>
#include <sstream>

#define UPnP_INTERVAL 1200
#define UPnP_PORT 1900
#define UPnP_METHOD_SIZE 10
#define UPnP_URI_SIZE 2
#define UPnP_BUFFER_SIZE 64
#define UPnP_MULTICAST_TTL 2

class UdpContext;

typedef enum { NONE, SEARCH, NOTIFY } upnp_method_t;

struct UPnPTimer;

class UPnPEnv {
public:
  UPnPEnv();
  ~UPnPEnv();

  bool begin();
  void setHTTPPort(uint16_t port);
  void setTTL(uint8_t ttl);

  void schema(WiFiClient client);
  void setSchemaURL(string url);
  void setDevice(UPnPDevice inputDevice);
  UPnPDevice getDevice();

protected:
  void send(upnp_method_t method);
  void update();
  void startTimer();
  static void onTimerStatic(UPnPEnv *self);

  UPnPDevice device;
  UdpContext *server;
  UPnPTimer *timer;
  uint16_t port;
  uint8_t ttl;

  uint32_t localIP;
  IPAddress respondToAddr;
  uint16_t respondToPort;

  bool pending;
  unsigned short delay;
  unsigned long process_time;
  unsigned long notify_time;

  string schemaURL;
};

extern UPnPEnv UPnP;

#endif
