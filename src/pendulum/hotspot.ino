
/**
 * Hotspot mode is for configuring and calibrating the Pendulum.
 * 
 * The functions in this file load web page files from the file
 * system and serve them to clients, or send JSON responses in
 * response to AJAX requests from the web page files.
 */

ESP8266WebServer server(80);
#define READ_INTERVAL 10000

int lastSensorReading = 0;
double hotspotTemp;
double hotspotGravity;
int hotspotWeight;
double hotspotVoltage;

void hotspotSetup() {
  Serial.print("Starting hotspot with name "); Serial.println(hydrometerName);
  Serial.println(" and password pendulum");
  WiFi.softAP(hydrometerName, "pendulum");

  // main.html has scripts/styles embedded.
  server.serveStatic("/", SPIFFS, "/main.html");
  
  server.on("/live", HTTP_GET, handleLiveUpdate);
  server.on("/calibration", HTTP_POST, updateCalibration);
  server.on("/config", HTTP_GET, getConfig);
  server.on("/config", HTTP_POST, updateConfig);

  boolean result = MDNS.begin("pendulum");

  if(!result) {
    Serial.println("Failed to start mDNS responder");
  }

  server.begin();
  Serial.println("Started hotspot mode");
}

// Hotspot loop
void hotspotLoop() {
  server.handleClient();
  drd.loop();

  if(millis() - lastSensorReading > READ_INTERVAL) {
     // Start up and shut down the sensors for each read
    sensorSetup();
    
    readTemp(&hotspotTemp);
    averageWeight(&hotspotWeight, 25);
  
    sensorShutdown();
  
    double gravity = calculateGravity(hotspotWeight / 1000.0);
    hotspotGravity = compensateTemperature(gravity, hotspotTemp);
  
    hotspotVoltage = readVoltage();

    lastSensorReading = millis();
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
  root["temperature"] = hotspotTemp;
  root["weight"] = hotspotWeight;
  root["gravity"] = hotspotGravity;
  root["battery"] = hotspotVoltage;
  
  char prettyJSON[root.measurePrettyLength() + 2];
  root.prettyPrintTo((char*) prettyJSON, root.measurePrettyLength() + 1);
  prettyJSON[root.measurePrettyLength() + 1] = 0;

  server.send(200, "application/json", prettyJSON);
}

// The calibrate endpoint accepts a JSON array of calibration
// points (measured weights and gravity readings), and returns
// a status code corresponding to the result.
void updateCalibration() {
  if(!server.hasArg("plain")) {
    server.send(400, "text/plain", "no body");
    return;
  }

  const size_t bufferSize = 2*JSON_ARRAY_SIZE(8) + JSON_OBJECT_SIZE(2) + 120;
  DynamicJsonBuffer jsonBuffer(bufferSize);

  JsonObject& root = jsonBuffer.parseObject(server.arg("plain"));
  JsonArray& jsonWeights = root["weights"];
  JsonArray& jsonGravities = root["gravities"];

  int weightElements = jsonWeights.size();
  int gravityElements = jsonGravities.size();

  if(weightElements != gravityElements) {
    server.send(400, "text/plain", "mismatched data");
    return;
  }
  
  int elements = weightElements;

  if(elements < 4) {
    server.send(400, "text/plain", "4 or more data points required");
    return;
  }
  
  float weights[elements];
  float gravities[elements];
  float coefficients[3];

  for(int i = 0; i < elements; i++) {
    if(i < 3) coefficients[i] = 0;

    double adjustedWeight = jsonWeights[i];
    adjustedWeight /= 1000.0;
    weights[i] = adjustedWeight;
    gravities[i] = jsonGravities[i];

    Serial.print("Weight: ");
    Serial.print(weights[i]);
    Serial.print(" Gravity: ");
    Serial.println(gravities[i]);
  }

  int error = regressGravities(gravities, weights, elements, coefficients);
  if(error != 0) {
    server.send(400, "text/plain", "regression failed");
  }

  yield();

  Serial.println(coefficients[0]);
  Serial.println(coefficients[1]);
  Serial.println(coefficients[2]);
  gravityCoefficients[0] = coefficients[0];
  gravityCoefficients[1] = coefficients[1];
  gravityCoefficients[2] = coefficients[2];

  boolean result = saveConfig();
  if(!result) {
    server.send(500, "text/plain", "error saving config");
    return;
  }

  server.send(200, "text/plain", "calibration updated");
}


// The get config endpoint returns a JSON object containing
// the current configuration, in config-saving format.
void getConfig() {
  char configJSON[1024];
  getConfigJSON(configJSON, 1024);
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
  
  server.send(200, "text/plain", "ok");
}

