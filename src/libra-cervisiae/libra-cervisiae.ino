
#include <WiFi.h>
#include <SPIFFS.h>
#include <pgmspace.h>
#include "libra-cervisiae.h"
#include "config.h"
#include "hotspot.h"
#include "hydrometer.h"
#include "sensors.h"

/**
 * LIBRA CERVISIAE is a scale controller for homebrewing use.
 * 
 */

DoubleResetDetector drd(5 /* timeout */, 0 /* address */);
long bootMillis;
boolean tareInProgress = false;
boolean calibrationInProgress = false;

boolean hotspotMode;

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

  if(DEBUG_TIMINGS) {
    Serial.print(F("Config loaded: ")); Serial.println(millis() - bootMillis);
  }

  initSensors();

  hotspotMode = true; //bootToHotspot || !result | drd.detectDoubleReset();

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
