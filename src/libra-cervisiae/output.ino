
void handleOutput(double gravity, double temperature, double voltage) {
  if(outputMode == 0) {
    return;
  }
  else if(outputMode == 1) {
    sendToGraviton(gravity, temperature, voltage);
  }
}

/** 
 *  Outputs
 */

void sendToGraviton(double gravity, double temperature, double voltage) {
  char gravitonJSON[250];
  int contentLength = getGravitonJSON(gravitonJSON, 250, gravity, temperature, voltage);

  WiFiClient client;
  Serial.print("API root: "); Serial.println(apiRoot);
  Serial.print("API port: "); Serial.println(apiPort);
  Serial.println("Reading: ");
  Serial.println(gravitonJSON);
  boolean result = client.connect(apiRoot, apiPort);

  if(result) {
    client.println("POST /api/v1/reading HTTP/1.1");
    client.print("Host: "); client.println(apiRoot);
    client.println("Cache-Control: no-cache");
    client.println("Content-Type: application/json");
    client.print("Authorization: Bearer "); client.println(apiKey);
    client.print("Content-Length: ");
    client.println(contentLength);
    client.println();
    client.println(gravitonJSON);

    long timeout = 10000;
    unsigned long currentMillis = millis(), previousMillis = millis();

    while(!client.available()){
    
      if((currentMillis - previousMillis) > timeout){
        Serial.println("Timeout sending request");
        break;
      }
      delay(50);
      currentMillis = millis();
    }

    while(client.available()) {
      client.setTimeout(1000);
      String line = client.readStringUntil('\n');
      Serial.println(line);

      yield();
    }
  }
  else {
    Serial.println("Failed to connect");
  }

  Serial.println("Finished upload");
  client.stop();
}

// returns content length
int getGravitonJSON(char* dest, int n, double g, double t, double v) {
  const size_t bufferSize = JSON_OBJECT_SIZE(4);
  DynamicJsonBuffer jsonBuffer(bufferSize);
  
  JsonObject& root = jsonBuffer.createObject();
  root["name"] = hydrometerName;
  root["gravity"] = g;
  root["battery"] = v;
  root["temperature"] = t;
  
  int written = root.printTo(dest, n);
  return root.measureLength();
}


