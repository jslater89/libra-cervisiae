
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
  server.on("/live", HTTP_GET, handleLive);
  server.on("/live/update", HTTP_GET, handleLiveUpdate);
  server.on("/calibrate", HTTP_POST, handleCalibrate);
  //server.on("/calibrate/temperature", HTTP_POST, handleTempCalibrate);
  server.on("/config", HTTP_GET, handleConfig);
  server.on("/config/current", HTTP_GET, getConfig);
  server.on("/config", HTTP_POST, updateConfig);

  server.begin();
}

// Hotspot loop
void hotspotLoop() {
  
}

// The root page is a menu which allows the selection
// of live mode or config mode.
void handleRoot() {
  
}

// The live page is a page which refreshes the current
// tilt, caluculated gravity, and temperature every
// few seconds. It also has inputs for calibration
// data points.
void handleLive() {
  
}

// The live update endpoint returns a JSON object containing
// the current temperature, accelerometer readings, tilt,
// and gravity.
void handleLiveUpdate() {
  
}

// The calibrate endpoint accepts a JSON array of calibration
// points (measured tilts and gravity readings), and returns
// an object containing either an array of calibration
// coefficients or an error.
void handleCalibrate() {
  
}

// The config page presents configuration options.
void handleConfig() {
  
}

// The get config endpoint returns a JSON object containing
// the current configuration.
void getConfig() {
  
}

// The update config endpoint accepts a JSON object containing
// a configuration, and sets the internal configuration to those
// values.
void updateConfig() {
  
}

