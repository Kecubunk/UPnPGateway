// UPnPDevice.h
#include <stdio.h>
#include "UPnPIcon.h"
#include "UPnPService.h"
#include <string>
#include <list>
#include <sstream>

using namespace std;

#ifndef UPNPDEVICE_H
#define UPNPDEVICE_H

class UPnPDevice {
  string deviceVersion;
  string deviceType;
  string friendlyName;
  string manufacturer;
  string manufacturerURL;
  string modelDescription;
  string modelName;
  string modelNumber;
  string modelURL;
  string serialNumber;
  string uuid;
  string presentationURL;

  list<UPnPIcon> iconList;
  list<UPnPService> serviceList;
  list<UPnPDevice> deviceList;

public:
  UPnPDevice();
  ~UPnPDevice();
  bool operator==(const UPnPDevice &);

  void addDevice(UPnPDevice inputDevice);
  void addService(UPnPService inputService);
  void addIcon(UPnPIcon inputIcon);

  void removeDevice(UPnPDevice inputDevice);
  void removeService(UPnPService inputService);
  void removeIcon(UPnPIcon inputIcon);

  bool emptyDeviceList();
  bool emptyServiceList();
  bool emptyIconList();

  void setDeviceVersion(string inputDeviceVersion);
  void setDeviceType(string inputDeviceType);
  void setFriendlyName(string inputFriendlyName);
  void setManufacturer(string inputManufacturer);
  void setManufacturerURL(string inputManufacturerURL);
  void setModelDescription(string inputManufacturerDescription);
  void setModelName(string inputModelName);
  void setModelNumber(string inputModelNumber);
  void setModelURL(string inputModelURL);
  void setSerialNumber(string inputSerialNumber);
  void setUuid(string inputUuid);
  void setPresentationURL(string inputPresentationURL);

  string getDeviceXML();
  string getDeviceVersion();
  string getDeviceType();
  string getFriendlyName();
  string getManufacturer();
  string getManufacturerURL();
  string getModelDescription();
  string getModelName();
  string getModelNumber();
  string getModelURL();
  string getSerialNumber();
  string getUuid();
  string getPresentationURL();
};

#endif
