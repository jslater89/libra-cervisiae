#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <ESP8266WiFiType.h>
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
#include <DoubleResetDetector.h>
#include <HX711.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <pgmspace.h>
#include "src/ArduinoJson/ArduinoJson.h"

/**
 * LIBRA CERVISIAE is a scale controller for homebrewing use.
 * 
 */

// Debug options
#define DEBUG_TIMINGS false
#define DEBUG_DS18XXX false
#define DEBUG_HX711 false
#define LOG_REQUESTS true

// Build types
#define WEMOS
//#define PCB
//#define NODEMCU

#ifdef WEMOS
#define DS18B20_POWER_PIN 12
#define DS18B20_DATA_PIN 13

#elif defined PCB
#define DS18B20_POWER_PIN 14
#define DS18B20_DATA_PIN 12

#elif defined NODEMCU
#define DS18B20_POWER_PIN 12
#define DS18B20_DATA_PIN 13

#endif

/****** Configuration options *******/
// How long between readings in hydrometer mode?
int delaySeconds; // half an hour

// What is the name of this hydrometer? Also used
// as the SSID for hotspot mode.
char hydrometerName[51];

// What is fully-charged battery voltage for this hydrometer?
float fullVoltage;

// What wifi network should this hydrometer connect
// to in hydrometer mode?
char wifiNetwork[41];

// What password should it use?
char wifiPassword[41];

// API root, path, port
char apiRoot[101];
char apiPath[101];
int apiPort;

// API key for Graviton
char apiKey[51];

// Should this hydrometer boot into hotspot mode?
boolean bootToHotspot;

// How should this hydrometer do output?
// 0: no output
// 1: Graviton output
// 2: Google Drive output
int outputMode;

// How should we adjust for the load cell's temperature response?
// rawOutput += (observed - base) * factor
// calibratedOutput += (observed - base) * factor / scaleFactor
// A negative compensation factor means that the scale reads higher
// at lower temperatures. A positive compensation factor means that
// the scale reads higher at higher temperatures.
double tempCompensationBase; // F
double tempCompensationFactor;

// The tare offset is the difference between the HX711 ADC
// output and 0.
double tareOffset;

// The scale factor is the divisor to apply to the HX711 ADC
// output to get the weight in grams.
double scaleFactor;

// The weight of the non-wort equipment going on the scale,
// in grams.
double equipmentWeight;

// The starting mass for the batch, not including equipment weight,
// in grams.
double startingWortMass;

// The starting gravity of the batch, in SG@68F.
double startingWortGravity;

// The list of DS18B20s connected; filled in at boot
uint8_t tempSensors[2][8];

// The DS18B20 address to use for load cell
// temperature compensation.
uint8_t boardTempAddr[8];

// The DS18B20 address to use for wort temperature
// reporting.
uint8_t wortTempAddr[8];
/****** End configuration *******/

// Tare in progress
boolean tareInProgress = false;

// Calibration in progress
boolean calibrationInProgress = false;

DoubleResetDetector drd(5 /* timeout */, 10 /* address */);
boolean hotspotMode;
long bootMillis;

HX711 scale;
OneWire oneWire(DS18B20_DATA_PIN);
DallasTemperature sensors(&oneWire);

void setup() {
  bootMillis = millis();
  Serial.begin(115200);

  Serial.println();
  Serial.println(F("Libra Cervisiae powered on"));

  WiFi.disconnect(); // disconnect to avoid stomping on other operations
  WiFi.persistent(false); // don't write to flash

  // start filesystem
  boolean result = SPIFFS.begin();
  if(!result) {
    Serial.println(F("Unable to start SPIFFS"));
  }

  // read in config
  result = loadConfig();
  if(!result) {
    Serial.println(F("Unable to load configuration"));
  }
  printConfig();

  initSensors();

  hotspotMode = bootToHotspot || drd.detectDoubleReset();

  if(DEBUG_TIMINGS) {
    Serial.print(F("Startup finished: ")); Serial.println(millis() - bootMillis);
  }

  // enter hotspot mode if there's no network configured
  if(hotspotMode || strcmp(wifiNetwork, "your_ssid") == 0) {
    Serial.println(F("Hotspot mode selected"));
    hotspotSetup();
  }
  else {
    Serial.println(F("Hydrometer mode selected"));
    hydrometerSetup();
  }
}

void loop() {
  if(hotspotMode) {
    hotspotLoop();
  }
  else {
    hydrometerLoop();
  }
}

boolean tryConnect() {
  WiFi.begin(wifiNetwork, wifiPassword);

  Serial.print(F("Connecting to "));
  Serial.print(wifiNetwork); Serial.print(F(" "));

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(500);
    Serial.print(F("."));

    if(i++ > 20) {
      Serial.println();
      Serial.println(F("Connection timed out"));
      return false;
    }
  }

  Serial.println();
  Serial.println(F("Connected!"));
  return true;
}

