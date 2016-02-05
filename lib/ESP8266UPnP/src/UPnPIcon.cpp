#include "UPnPIcon.h"

using namespace std;

UPnPIcon::UPnPIcon() {}
UPnPIcon::~UPnPIcon() {}

bool UPnPIcon::operator==(const UPnPIcon &param) {
  return url.compare(param.url);
}

string UPnPIcon::getIconXML() {
  ostringstream stream;
  stream << "<icon>"
         << "<mimetype>" << mimetype << "</mimetype>"
         << "<height>" << height << "</height>"
         << "<width>" << width << "</width>"
         << "<depth>" << depth << "</depth>"
         << "<url>" << url << "</url>"
         << "</icon>";
  return stream.str();
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
