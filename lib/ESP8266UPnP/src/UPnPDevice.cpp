#include "UPnPDevice.h"

using namespace std;

UPnPDevice::UPnPDevice() {}
UPnPDevice::~UPnPDevice() {}

bool UPnPDevice::operator==(const UPnPDevice &param) {
  return uuid.compare(param.uuid);
}

void UPnPDevice::addDevice(UPnPDevice inputDevice) {
  deviceList.push_back(inputDevice);
}
void UPnPDevice::addService(UPnPService inputService) {
  serviceList.push_back(inputService);
}
void UPnPDevice::addIcon(UPnPIcon inputIcon) { iconList.push_back(inputIcon); }

void UPnPDevice::removeDevice(UPnPDevice inputDevice) {
  deviceList.remove(inputDevice);
}
void UPnPDevice::removeService(UPnPService inputService) {
  serviceList.remove(inputService);
}
void UPnPDevice::removeIcon(UPnPIcon inputIcon) { iconList.remove(inputIcon); }

bool UPnPDevice::emptyDeviceList() { return deviceList.empty(); }
bool UPnPDevice::emptyServiceList() { return serviceList.empty(); }
bool UPnPDevice::emptyIconList() { return iconList.empty(); }

string UPnPDevice::getDeviceXML() {
  ostringstream stream;
  stream << "HTTP/1.1 200 OK\r\n"
         << "Content-Type: text/xml\r\n"
         << "Connection: close\r\n"
         << "Access-Control-Allow-Origin: *\r\n"
         << "\r\n"
         << "<?xml version=\"1.0\"?>"
         << "<root xmlns=\"urn:schemas-upnp-org:device-1-0\">"
         << "<specVersion>"
         << "<major>2</major>"
         << "<minor>0</minor>"
         << "</specVersion>"
         << "<device>"
         << "<deviceType>" << deviceType << "</deviceType>"
         << "<friendlyName>" << friendlyName << "</friendlyName>"
         << "<manufacturer>" << manufacturer << "</manufacturer>"
         << "<manufacturerURL>" << manufacturerURL << "</manufacturerURL>"
         << "<modelDescription>" << modelDescription << "</modelDescription>"
         << "<modelName>" << modelName << "</modelName>"
         << "<modelNumber>" << modelNumber << "</modelNumber>"
         << "<modelURL>" << modelURL << "</modelURL>"
         << "<serialNumber>" << serialNumber << "</serialNumber>"
         << "<UDN>uuid:" << uuid << "</UDN>"
         << "<presentationURL>" << presentationURL << "</presentationURL>"
         << "</root>\r\n"
         << "\r\n";
  if (!emptyIconList()) {
    stream << "<iconList>";
    for (list<UPnPIcon>::iterator it = iconList.begin(); it != iconList.end();
         ++it)
      stream << (*it).getIconXML();
    stream << "</iconList>";
  }

  if (!emptyServiceList()) {
    stream << "<serviceList>";
    for (list<UPnPService>::iterator it = serviceList.begin();
         it != serviceList.end(); ++it)
      stream << (*it).getServiceXML();
    stream << "</serviceList>";
  }

  if (!emptyDeviceList()) {
    stream << "<deviceList>";
    for (list<UPnPDevice>::iterator it = deviceList.begin();
         it != deviceList.end(); ++it)
      stream << (*it).getDeviceXML();
    stream << "</deviceList>";
  }

  return stream.str();
}

// Setters
void UPnPDevice::setDeviceVersion(string inputDeviceVersion) {
  deviceVersion = inputDeviceVersion;
}
void UPnPDevice::setDeviceType(string inputDeviceType) {
  deviceType = inputDeviceType;
}
void UPnPDevice::setFriendlyName(string inputFriendlyName) {
  friendlyName = inputFriendlyName;
}
void UPnPDevice::setManufacturer(string inputManufacturer) {
  manufacturer = inputManufacturer;
}
void UPnPDevice::setManufacturerURL(string inputManufacturerURL) {
  manufacturerURL = inputManufacturerURL;
}
void UPnPDevice::setModelDescription(string inputModelDescription) {
  modelDescription = inputModelDescription;
}
void UPnPDevice::setModelName(string inputModelName) {
  modelName = inputModelName;
}
void UPnPDevice::setModelNumber(string inputModelNumber) {
  modelNumber = inputModelNumber;
}
void UPnPDevice::setModelURL(string inputModelURL) { modelURL = inputModelURL; }
void UPnPDevice::setSerialNumber(string inputSerialNumber) {
  serialNumber = inputSerialNumber;
}
void UPnPDevice::setUuid(string inputUuid) { uuid = inputUuid; }
void UPnPDevice::setPresentationURL(string inputPresentationURL) {
  presentationURL = inputPresentationURL;
}

// Getters
string UPnPDevice::getDeviceVersion() { return deviceVersion; }
string UPnPDevice::getDeviceType() { return deviceType; }
string UPnPDevice::getFriendlyName() { return friendlyName; }
string UPnPDevice::getManufacturer() { return manufacturer; }
string UPnPDevice::getManufacturerURL() { return manufacturerURL; }
string UPnPDevice::getModelDescription() { return modelDescription; }
string UPnPDevice::getModelName() { return modelName; }
string UPnPDevice::getModelNumber() { return modelNumber; }
string UPnPDevice::getModelURL() { return modelURL; }
string UPnPDevice::getSerialNumber() { return serialNumber; }
string UPnPDevice::getUuid() { return uuid; }
string UPnPDevice::getPresentationURL() { return presentationURL; }
