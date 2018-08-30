
/**
 * Hotspot mode is for configuring and calibrating the Libra Cervisiae.
 * 
 * The functions in this file load web page files from the file
 * system and serve them to clients, or send JSON responses in
 * response to AJAX requests from the web page files.
 */

#include <FS.h>
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

#include "src/ArduinoJson/ArduinoJson.h"
#include "libra-cervisiae.h"
#include "utils.h"
#include "sensors.h"
#include "scale.h"
#include "temperature.h"
#include "config.h"
#include "output.h"
#include "hydrometer.h"
#include "hotspot.h"

ESP8266WebServer server(80);
#define READ_INTERVAL 10000

long lastSensorReading = 0;
double hotspotBoardTemp;
double hotspotWortTemp;
double hotspotGravity;
double hotspotABW;
double hotspotABV;
int hotspotRawWeight;
double hotspotCalibratedWeight;

boolean connectedToWifi;
long lastSensorUpload = 0;

void hotspotSetup() {  
  connectedToWifi = false;
  if(strcmp(wifiNetwork, "your_ssid") != 0 || strlen(wifiNetwork) == 0) {
    Serial.print(F("Wifi network settings found; trying to connect to network ")); Serial.println(wifiNetwork);

    boolean connectionResult = tryConnect();
    if(!connectionResult) {
      Serial.println(F("Unable to connect to existing wifi network"));
    }
    else {
      Serial.println(F("Connected to existing network."));
      connectedToWifi = true;
      lastSensorUpload = millis();
    }
  }

  if(!connectedToWifi) {
    Serial.print(F("Starting hotspot with name ")); Serial.print(hydrometerName); Serial.println(F(" and password libra-cervisiae"));
    boolean apResult = WiFi.softAP(hydrometerName, "libra-cervisiae");
    if(!apResult) {
      Serial.println(F("Failed to start webserver!"));
    }
  }

  Serial.print(F("Starting mDNS at ")); Serial.print(hydrometerName); Serial.println(F(".local"));
  boolean result = MDNS.begin(hydrometerName);

  if(!result) {
    Serial.println(F("Failed to start mDNS responder"));
  }

  startServer();
  Serial.print(F("Started hotspot mode on address ")); Serial.println(WiFi.localIP());
}

bool tryConnect() {
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

void startServer() {
  server.serveStatic("/", SPIFFS, "/main.html");
  server.serveStatic("/temps.html", SPIFFS, "/temps.html");
  server.serveStatic("/scale.html", SPIFFS, "/scale.html");
  server.serveStatic("/config.html", SPIFFS, "/config.html"); 
  server.serveStatic("/app.js", SPIFFS, "/app.js");
  server.serveStatic("/style.css", SPIFFS, "/style.css");
  
  server.on("/live", HTTP_GET, handleLiveUpdate);
  server.on("/calibrate", HTTP_POST, updateCalibration);
  server.on("/tare", HTTP_POST, updateTare);
  server.on("/equipmentweight", HTTP_POST, updateEquipmentWeight);
  server.on("/config", HTTP_GET, getConfig);
  server.on("/config", HTTP_POST, updateConfig);
  server.on("/tempsensors", HTTP_GET, getTempSensors);

  Serial.println(F("Web server started"));
  server.begin();
}

// Hotspot loop
void hotspotLoop() {
  server.handleClient();
  
  drd.loop();

  if(tareInProgress) {
    tareLoop();
    return;
  }

  if(calibrationInProgress) {
    calibrateLoop();
    return;
  }

  // If lastSensorReading is larger than millis(), millis()
  // has overflowed.
  if(lastSensorReading > millis()) {
    lastSensorReading = 0;
    lastSensorUpload = 0;
  }

  if(millis() - lastSensorReading > READ_INTERVAL) {
     // Start up and shut down the sensors for each read
    startSensors();
    
    readWortTemp(&hotspotWortTemp);
    readBoardTemp(&hotspotBoardTemp);
    averageWeight(&hotspotRawWeight, 5);
    averageCalibratedWeight(&hotspotCalibratedWeight, 15);
    temperatureCorrectCalibrated(hotspotBoardTemp, &hotspotCalibratedWeight);
  
    stopSensors();

    double wortWeight = hotspotCalibratedWeight - equipmentWeight;
    hotspotABW = getBatchABW(wortWeight);
    hotspotABV = calculateABV(hotspotABW);
    double gravity = calculateGravity(startingWortGravity, hotspotABV);
    hotspotGravity = gravity;
  
    lastSensorReading = millis();
  }

  if(connectedToWifi && millis() - lastSensorUpload > delaySeconds * 1000) {
    handleOutput(hotspotGravity, hotspotABW, hotspotABV, hotspotWortTemp, hotspotCalibratedWeight, startingWortMass - hotspotCalibratedWeight - equipmentWeight);
    lastSensorUpload = millis();
  }
}

// The live update endpoint returns a JSON object containing
// the current temperature, weight, gravity, and battery.
//
// JSON tags: temperature, weight, gravity, battery
void handleLiveUpdate() {
  const size_t bufferSize = JSON_OBJECT_SIZE(4);
  DynamicJsonBuffer jsonBuffer(bufferSize);
  
  JsonObject& root = jsonBuffer.createObject();
  root[F("wortTemperature")] = hotspotWortTemp;
  root[F("boardTemperature")] = hotspotBoardTemp;
  root[F("rawWeight")] = hotspotRawWeight;
  root[F("abw")] = hotspotABW;
  root[F("abv")] = hotspotABV;
  root[F("gravity")] = hotspotGravity;
  root[F("calibratedWeight")] = hotspotCalibratedWeight;
  
  char prettyJSON[root.measurePrettyLength() + 2];
  root.prettyPrintTo((char*) prettyJSON, root.measurePrettyLength() + 1);
  prettyJSON[root.measurePrettyLength() + 1] = 0;

  if(LOG_REQUESTS) Serial.println("handled live update");
  server.send(200, "application/json", prettyJSON);
}


void updateTare() {
  if(!server.hasArg("plain")) {
    server.send(400, "text/plain", "no body");
    return;
  }

  if(tareInProgress || calibrationInProgress) {
    server.send(400, "text/plain", "tare or calibration in progress");
  }

  const size_t bufferSize = JSON_OBJECT_SIZE(2) + 120;
  DynamicJsonBuffer jsonBuffer(bufferSize);

  JsonObject& root = jsonBuffer.parseObject(server.arg("plain"));
  double time = root[F("time")];

  startSensors();
  
  tareScale(time * 1000);

  if(LOG_REQUESTS) Serial.println("handled tare");
  server.send(200, "text/plain", "tare in progress");
}

void updateEquipmentWeight() {
  if(!server.hasArg("plain")) {
    server.send(400, "text/plain", "no body");
    return;
  }

  if(tareInProgress || calibrationInProgress) {
    server.send(400, "text/plain", "tare or calibration in progress");
  }

  const size_t bufferSize = JSON_OBJECT_SIZE(2) + 120;
  DynamicJsonBuffer jsonBuffer(bufferSize);

  JsonObject& root = jsonBuffer.parseObject(server.arg("plain"));

  double w = root[F("weight")];
  
  if(w == 0) {
    startSensors();

    averageCalibratedWeight(&w, 10);

    stopSensors();
  }
  
  equipmentWeight = w;
  saveConfig();

  if(LOG_REQUESTS) Serial.println("handled equipment update");
  server.send(200, "text/plain", "equipment weight set");
}

// The calibrate endpoint accepts a known weight in grams, and calibrates
// the scale to read that value.
void updateCalibration() {
  if(!server.hasArg("plain")) {
    server.send(400, "text/plain", "no body");
    return;
  }

  if(tareInProgress || calibrationInProgress) {
    server.send(400, "text/plain", "tare or calibration in progress");
  }

  const size_t bufferSize = JSON_OBJECT_SIZE(2) + 120;
  DynamicJsonBuffer jsonBuffer(bufferSize);

  JsonObject& root = jsonBuffer.parseObject(server.arg("plain"));
  double weight = root["weight"];
  int time = root["time"];
  time = time * 1000;

  startSensors();
  
  calibrateScale(weight, time);

  if(LOG_REQUESTS) Serial.println("handled calibration");
  server.send(200, "text/plain", "calibration updated");
}


// The get config endpoint returns a JSON object containing
// the current configuration, in config-saving format.
void getConfig() {
  char configJSON[1024];
  getConfigJSON(configJSON, 1024);

  if(LOG_REQUESTS) Serial.println("handled config get");
  server.send(200, "application/json", configJSON);
}

// The update config endpoint accepts a JSON object containing
// a configuration, and sets the internal configuration to those
// values.
void updateConfig() {
  if(!server.hasArg("plain")) {
    server.send(400, "text/plain", "no body");
    return;
  }

  boolean result = decodeJSON(server.arg("plain"), false);

  if(!result) {
    server.send(400, "text/plain", "JSON parse error");
    return;
  }

  yield();
  
  result = saveConfig();

  if(!result) {
    server.send(500, "text/plain", "error saving config");
    return;
  }

  if(LOG_REQUESTS) Serial.println("handled config post");
  server.send(200, "text/plain", "ok");
}

void getTempSensors() {
  const size_t bufferSize = JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(2);
  DynamicJsonBuffer jsonBuffer(bufferSize);
  JsonObject& root = jsonBuffer.createObject();

  uint8_t* d0 = tempSensors[0];
  uint8_t* d1 = tempSensors[1];

  char aStr0[65], aStr1[65];
  convertUint8ToChar(d0, aStr0, 8);
  convertUint8ToChar(d1, aStr1, 8);

  startSensors();

  double t0, t1;
  readTempByAddress(d0, &t0);
  readTempByAddress(d1, &t1);

  stopSensors();
  
  JsonArray& sensors = root.createNestedArray("sensors");
  JsonObject& sensors0 = sensors.createNestedObject();
  sensors0["id"] = aStr0;
  sensors0["temp"] = t0;
  
  JsonObject& sensors1 = sensors.createNestedObject();
  sensors1["id"] = aStr1;
  sensors1["temp"] = t1;

  char prettyJSON[root.measurePrettyLength() + 2];
  root.prettyPrintTo((char*) prettyJSON, root.measurePrettyLength() + 1);
  prettyJSON[root.measurePrettyLength() + 1] = 0;

  if(LOG_REQUESTS) Serial.println("handled temp sensors get");
  server.send(200, "application/json", prettyJSON);
}
