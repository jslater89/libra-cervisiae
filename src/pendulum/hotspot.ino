
/**
 * Hotspot mode is for configuring and calibrating the Pendulum.
 * 
 * The functions in this file load web page files from the file
 * system and serve them to clients, or send JSON responses in
 * response to AJAX requests from the web page files.
 */

ESP8266WebServer server(80);

void hotspotSetup() {
  char nameArray[hydrometerName.length() + 1];
  hydrometerName.toCharArray(nameArray, 0, hydrometerName.length());
  WiFi.softAP(nameArray, "pendulum");

  server.on("/", HTTP_GET, handleRoot);
  server.on("/live", HTTP_GET, handleLiveUpdate);
  server.on("/calibration", HTTP_POST, updateCalibration);
  server.on("/config", HTTP_GET, getConfig);
  server.on("/config", HTTP_POST, updateConfig);

  server.begin();
}

// Hotspot loop
void hotspotLoop() {
  
}

// The root page returns an HTML file containing
// embedded styles and scripts 
void handleRoot() {
  
}

// The live update endpoint returns a JSON object containing
// the current temperature, tilt, gravity, and battery.
//
// JSON tags: temperature, tilt, gravity, battery
void handleLiveUpdate() {
  
}

// The calibrate endpoint accepts a JSON array of calibration
// points (measured tilts and gravity readings), and returns
// a status code corresponding to the result.
void updateCalibration() {
  
}


// The get config endpoint returns a JSON object containing
// the current configuration, in config-saving format.
void getConfig() {
  
}

// The update config endpoint accepts a JSON object containing
// a configuration, and sets the internal configuration to those
// values.
void updateConfig() {
  
}

