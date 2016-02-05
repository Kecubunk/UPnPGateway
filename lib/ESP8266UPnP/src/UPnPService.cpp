#include "UPnPService.h"

using namespace std;

UPnPService::UPnPService() {}
UPnPService::~UPnPService() {}

bool UPnPService::operator==(const UPnPService &param) {
  return id.compare(param.id);
}

string UPnPService::getServiceXML() {
  string stream;
  stream = "<service>";
  stream += "<serviceType>urn:schemas-upnp-org:service:";
  stream += type;
  stream += ":";
  stream += version;
  stream += "</serviceType>";
  stream += "<serviceId>urn:upnp-org:serviceId:";
  stream += id;
  stream += "</serviceId>";
  stream += "<SCPDURL>";
  stream += SCPDURL;
  stream += "</SCPDURL>";
  stream += "<controlURL>";
  stream += controlURL;
  stream += "</controlURL>";
  stream += "<eventSubURL>";
  stream += eventSubURL;
  stream += "</eventSubURL>";
  stream += "</service>";
  return stream;
}

// Setters
void UPnPService::setType(string inputType) { type = inputType; };
void UPnPService::setVersion(string inputVersion) { version = inputVersion; };
void UPnPService::setId(string inputId) { id = inputId; };
void UPnPService::setSCPDURL(string inputSCPDURL) { SCPDURL = inputSCPDURL; };
void UPnPService::setControlURL(string inputControlURL) {
  controlURL = inputControlURL;
};
void UPnPService::setEventSubURL(string inputEventSubURL) {
  eventSubURL = inputEventSubURL;
};

// Getters
string UPnPService::getType() { return type; };
string UPnPService::getVersion() { return version; };
string UPnPService::getId() { return id; };
string UPnPService::getSCPDURL() { return SCPDURL; };
string UPnPService::getControlURL() { return controlURL; };
string UPnPService::getEventSubURL() { return eventSubURL; };
