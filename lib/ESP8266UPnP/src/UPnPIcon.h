// UPnPIcon.h
#include <stdio.h>
#include <string>

using namespace std;

#ifndef UPNPICON_H
#define UPNPICON_H

class UPnPIcon {
  string mimetype;
  int height;
  int width;
  int depth;
  string url;

public:
  UPnPIcon();
  ~UPnPIcon();

  bool operator==(const UPnPIcon &);

  void setMimetype(string inputMimetype);
  void setHeight(int inputHeight);
  void setWidth(int inputWidth);
  void setDepth(int inputDepth);
  void setUrl(string inputUrl);

  string getIconXML();
  string getMimetype();
  int getHeight();
  int getWidth();
  int getDepth();
  string getUrl();
};

#endif
