#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266UPnP.h>

const char* ssid = "************";
const char* password = "***********";

ESP8266WebServer HTTP(80);

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting WiFi...");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if(WiFi.waitForConnectResult() == WL_CONNECTED){

    Serial.printf("Starting HTTP...\n");
    HTTP.on("/index.html", HTTP_GET, [](){
      HTTP.send(200, "text/plain", "Hello World!");
    });
    HTTP.on("/description.xml", HTTP_GET, [](){
      UPnP.schema(HTTP.client());
    });
    HTTP.begin();

    Serial.printf("Starting UPnP...\n");
    UPnP.setSchemaURL("description.xml");
    UPnP.setHTTPPort(80);
    UPnP.setName("Philips hue clone");
    UPnP.setSerialNumber("001788102201");
    UPnP.setURL("index.html");
    UPnP.setModelName("Philips hue bridge 2012");
    UPnP.setModelNumber("929000226503");
    UPnP.setModelURL("http://www.meethue.com");
    UPnP.setManufacturer("Royal Philips Electronics");
    UPnP.setManufacturerURL("http://www.philips.com");
    UPnP.begin();

    Serial.printf("Ready!\n");
  } else {
    Serial.printf("WiFi Failed\n");
    while(1) delay(100);
  }
}

void loop() {
  HTTP.handleClient();
  delay(1);
}
