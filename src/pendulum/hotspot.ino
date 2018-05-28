

ESP8266WebServer server(80);

void hotspotSetup() {
  WiFi.softAP("test", "testpw");

  server.on("/", handleRoot);
  server.on("/live", handleLive);
  server.on("/live/update", handleLiveUpdate);
  server.on("/config", HTTP_GET, handleConfig);
  server.on("/config", HTTP_POST, handleConfig);
}

// Hotspot loop
void hotspotLoop() {
  // set up hotspot
}

void handleRoot() {
  
}

void handleLive() {
  
}

void handleLiveUpdate() {
  
}

void handleConfig() {
  
}

void updateConfig() {
  
}

