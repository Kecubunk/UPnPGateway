// UPnPService.h
#include <stdio.h>
#include <string>

using namespace std;

#ifndef UPNPSERVICE_H
#define UPNPSERVICE_H

class UPnPService {
  string type;
  string version;
  string id;
  string SCPDURL;
  string controlURL;
  string eventSubURL;

public:
  UPnPService();
  ~UPnPService();

  bool operator==(const UPnPService &);

  void setType(string inputType);
  void setVersion(string inputVersion);
  void setId(string inputId);
  void setSCPDURL(string inputSCPDURL);
  void setControlURL(string inputControlURL);
  void setEventSubURL(string inputEventSubURL);

  string getServiceXML();
  string getType();
  string getVersion();
  string getId();
  string getSCPDURL();
  string getControlURL();
  string getEventSubURL();
};

#endif
