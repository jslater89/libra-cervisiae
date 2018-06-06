#include <WiFiServer.h>
#include <ESP8266WiFiType.h>
#include <WiFiServerSecure.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WebServerSecure.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include <MatrixMath.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <DoubleResetDetector.h>

/**
 * PENDULUM is a tilting hydrometer for homebrewing use.
 * 
 */

DoubleResetDetector drd(5 /* timeout */, 10 /* address */);
boolean hotspotMode;

void setup() {
  Serial.begin(115200);

  Serial.println();
  Serial.println("Pendulum powered on");

  WiFi.disconnect(); // disconnect to avoid stomping on other operations
  WiFi.persistent(false); // don't write to flash

  // start filesystem
  boolean result = SPIFFS.begin();
  if(!result) {
    Serial.println("Unable to start SPIFFS");
  }

  // read in config
  result = loadConfig();
  if(!result) {
    Serial.println("Unable to load configuration");
  }
  printConfig();

  hotspotMode = drd.detectDoubleReset();

  if(hotspotMode) {
    Serial.println("Hotspot mode selected");
    hotspotSetup();
  }
  else {
    Serial.println("Hydrometer mode selected");
    hydrometerSetup();
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  if(hotspotMode) {
    hotspotLoop();
  }
  else {
    hydrometerLoop();
  }
}
