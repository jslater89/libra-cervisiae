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
#include <DoubleMatrixMath.h>
#include <ArduinoJson.h>
#include <DoubleResetDetector.h>
#include <HX711.h>
#include <DallasTemperature.h>
#include <OneWire.h>

/**
 * PENDULUM is a hydrometer for homebrewing use.
 * 
 */

// Build types
#define WEMOS
//#define PCB
//#define NODEMCU

/****** Configuration options *******/
// How long between readings in hydrometer mode?
int delaySeconds = 1800; // half an hour

// What is the name of this hydrometer? Also used
// as the SSID for hotspot mode.
char hydrometerName[51] = "pendulum";

// What is fully-charged battery voltage for this hydrometer?
float fullVoltage = 4.2;

// What wifi network should this hydrometer connect
// to in hydrometer mode?
char wifiNetwork[51] = "";

// What password should it use?
char wifiPassword[51] = "";

// API root, path, port
char apiRoot[151] = "";
char apiPath[151] = "";
int apiPort = 80;

// API key for Graviton
char apiKey[51] = "";

// What are the coefficients for the weight->gravity
// polynomial?
double gravityCoefficients[3] = {0, 0, 0};

// Should this hydrometer boot into hotspot mode?
bool bootToHotspot = false;

// How should this hydrometer do output?
// 0: no output
// 1: Graviton output
int outputMode = 0;

/****** End configuration *******/

DoubleResetDetector drd(5 /* timeout */, 10 /* address */);
boolean hotspotMode;
#define DEBUG_TIMINGS true
long bootMillis;

void setup() {
  bootMillis = millis();
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

  hotspotMode = bootToHotspot || drd.detectDoubleReset();

  if(DEBUG_TIMINGS) Serial.print("Startup finished: "); Serial.println(millis() - bootMillis);

  // enter hotspot mode if there's no network configured
  if(hotspotMode || strcmp(wifiNetwork, "your_ssid") == 0) {
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

bool tryConnect() {
  WiFi.begin(wifiNetwork, wifiPassword);

  Serial.print("Connecting to ");
  Serial.print(wifiNetwork); Serial.print(" ");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(500);
    Serial.print(".");

    if(i++ > 20) {
      Serial.println();
      Serial.println("Connection timed out");
      return false;
    }
  }

  Serial.println();
  Serial.println("Connected!");
  return true;
}

