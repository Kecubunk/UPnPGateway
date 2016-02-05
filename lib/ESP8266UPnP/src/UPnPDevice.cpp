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
  string stream;
  stream = "HTTP/1.1 200 OK\r\n";
  stream += "Content-Type: text/xml\r\n";
  stream += "Connection: close\r\n";
  stream += "Access-Control-Allow-Origin: *\r\n";
  stream += "\r\n";
  stream += "<?xml version=\"1.0\"?>";
  stream += "<root xmlns=\"urn:schemas-upnp-org:device-1-0\">";
  stream += "<specVersion>";
  stream += "<major>2</major>";
  stream += "<minor>0</minor>";
  stream += "</specVersion>";
  stream += "<device>";
  stream += "<deviceType>";
  stream += deviceType;
  stream += "</deviceType>";
  stream += "<friendlyName>";
  stream += friendlyName;
  stream += "</friendlyName>";
  stream += "<manufacturer>";
  stream += manufacturer;
  stream += "</manufacturer>";
  stream += "<manufacturerURL>";
  stream += manufacturerURL;
  stream += "</manufacturerURL>";
  stream += "<modelDescription>";
  stream += modelDescription;
  stream += "</modelDescription>";
  stream += "<modelName>";
  stream += modelName;
  stream += "</modelName>";
  stream += "<modelNumber>";
  stream += modelNumber;
  stream += "</modelNumber>";
  stream += "<modelURL>";
  stream += modelURL;
  stream += "</modelURL>";
  stream += "<serialNumber>";
  stream += serialNumber;
  stream += "</serialNumber>";
  stream += "<UDN>uuid:";
  stream += uuid;
  stream += "</UDN>";
  stream += "<presentationURL>";
  stream += presentationURL;
  stream += "</presentationURL>";
  stream += "</root>\r\n";
  stream += "\r\n";
  if (!emptyIconList()) {
    stream += "<iconList>";
    for (list<UPnPIcon>::iterator it = iconList.begin(); it != iconList.end();
         ++it)
      stream += (*it).getIconXML();
    stream += "</iconList>";
  }

  if (!emptyServiceList()) {
    stream += "<serviceList>";
    for (list<UPnPService>::iterator it = serviceList.begin();
         it != serviceList.end(); ++it)
      stream += (*it).getServiceXML();
    stream += "</serviceList>";
  }

  if (!emptyDeviceList()) {
    stream += "<deviceList>";
    for (list<UPnPDevice>::iterator it = deviceList.begin();
         it != deviceList.end(); ++it)
      stream += (*it).getDeviceXML();
    stream += "</deviceList>";
  }

  return stream;
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
