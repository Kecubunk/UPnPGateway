#include "Arduino.h"
#include <ESP8266UPnP.h>
#include <OneWire.h>
#include <DS2438.h>
#include <ESP8266WiFi.h>
#include "UPnPDevice.h"
#include "UPnPService.h"
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "Computacao-LUPS";
const char *password = "fuckyoutorrent";

ESP8266WebServer HTTP(80);

template class basic_string<char>;

// template class throw_logic_error;

void setup() {

  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting WiFi...");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() == WL_CONNECTED) {
    Serial.printf("OK\n");
    Serial.printf("Starting UPnP...");
    UPnPDevice device;

    device.setFriendlyName("Gateway LUPS");
    device.setDeviceVersion("1.0");
    device.setDeviceType("GatewayNativo");
    device.setManufacturer("LUPS");
    device.setManufacturerURL("http://lups.inf.ufpel.edu.br/");
    device.setModelDescription("versao 1");
    device.setModelName("Gateway Nativo");
    device.setModelNumber("1.0");
    device.setModelURL("http://lups.inf.ufpel.edu.br/");
    device.setSerialNumber("12002983");
    device.setPresentationURL("http://lups.inf.ufpel.edu.br/");

    // device.addDevice(UPnPDevice inputDevice);
    // device.addService(UPnPService inputService);
    // device.addIcon(UPnPIcon inputIcon);

    HTTP.on("/index.html", HTTP_GET, []() {
      HTTP.send(
          200, "text/plain",
          "ESP8266 - Gateway EXEHDA-IoT \n\n -> "
          "IP/temp?sensor=1 a 7 para "
          "ler temperatura DS18B20; \n -> IP/temp2438?sensor=1 a 7 para "
          "ler temperatura DS2438; \n -> IP/umidade?sensor=1 a 7 para ler "
          "umidade com HIH4000 e DS2438 \n -> IP/luz?sensor=1 a 7 para ler "
          "presenca de luz com LDR e DS2438.");
    });
    HTTP.on("/description.xml", HTTP_GET, []() { UPnP.schema(HTTP.client()); });
    HTTP.begin();

    UPnP.setDevice(device);
    UPnP.setSchemaURL("description.xml");
    UPnP.setHTTPPort(80);
    UPnP.begin();

    Serial.printf("OK");
    Serial.printf("Starting HTTP Server...");

    Serial.printf("OK\n");
  } else {
    Serial.printf("Failed\n");
    while (1)
      delay(100);
  }
}

void loop() {
  HTTP.handleClient();
  delay(1);
}
