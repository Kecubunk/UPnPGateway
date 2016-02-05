#include "UPnPService.h"

using namespace std;

UPnPService::UPnPService() {}
UPnPService::~UPnPService() {}

bool UPnPService::operator==(const UPnPService &param) {
  return id.compare(param.id);
}

string UPnPService::getServiceXML() {
  ostringstream stream;
  stream << "<service>"
         << "<serviceType>urn:schemas-upnp-org:service:" << type << ":"
         << version << "</serviceType>"
         << "<serviceId>urn:upnp-org:serviceId:" << id << "</serviceId>"
         << "<SCPDURL>" << SCPDURL << "</SCPDURL>"
         << "<controlURL>" << controlURL << "</controlURL>"
         << "<eventSubURL>" << eventSubURL << "</eventSubURL>"
         << "</service>";
  return stream.str();
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
