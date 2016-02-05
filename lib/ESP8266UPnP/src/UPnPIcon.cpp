#include "UPnPIcon.h"

using namespace std;

UPnPIcon::UPnPIcon() {}
UPnPIcon::~UPnPIcon() {}

bool UPnPIcon::operator==(const UPnPIcon &param) {
  return url.compare(param.url);
}

string UPnPIcon::getIconXML() {
  string stream;
  stream = "<icon>";
  stream += "<mimetype>";
  stream += mimetype;
  stream += "</mimetype>";
  stream += "<height>";
  stream += height;
  stream += "</height>";
  stream += "<width>";
  stream += width;
  stream += "</width>";
  stream += "<depth>";
  stream += depth;
  stream += "</depth>";
  stream += "<url>";
  stream += url;
  stream += "</url>";
  stream += "</icon>";
  return stream;
}

// Setters
void UPnPIcon::setMimetype(string inputMimetype) { mimetype = inputMimetype; };
void UPnPIcon::setHeight(int inputHeight) { height = inputHeight; };
void UPnPIcon::setWidth(int inputWidth) { width = inputWidth; };
void UPnPIcon::setDepth(int inputDepth) { depth = inputDepth; };
void UPnPIcon::setUrl(string inputUrl) { url = inputUrl; };

// Getters
string UPnPIcon::getMimetype() { return mimetype; };
int UPnPIcon::getHeight() { return height; };
int UPnPIcon::getWidth() { return width; };
int UPnPIcon::getDepth() { return depth; };
string UPnPIcon::getUrl() { return url; };
