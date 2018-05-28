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
#include <FS.h>
#include <MatrixMath.h>

/**
 * PENDULUM is a tilting hydrometer for homebrewing use.
 * 
 */

boolean hotspotMode = false;

void setup() {
  // if double-reset
  // hotspotMode = true

  if(hotspotMode) hotspotSetup();

  // read in configuration
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
