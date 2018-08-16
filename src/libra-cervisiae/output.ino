
void handleOutput(double gravity, double abw, double abv, double temperature, double weight, double weightDelta) {
  if(outputMode == 0) {
    return;
  }
  else if(outputMode == 1) {
    sendToGraviton(gravity, abw, abv, temperature, weight, weightDelta);
  }
  else if(outputMode == 2) {
    sendToGoogleDrive(gravity, abw, abv, temperature, weight, weightDelta);
  }
}

/** 
 *  Outputs
 */

void sendToGraviton(double gravity, double abw, double abv, double temperature, double weight, double weightDelta) {
  char gravitonJSON[250];
  int contentLength = getGravitonJSON(gravitonJSON, 250, gravity, temperature, weight);

  WiFiClient client;
  Serial.print(F("API root: ")); Serial.println(apiRoot);
  Serial.print(F("API port: ")); Serial.println(apiPort);
  Serial.println(F("Reading: "));
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
        Serial.println(F("Timeout sending request"));
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
    Serial.println(F("Failed to connect"));
  }

  Serial.println(F("Finished upload"));
  client.stop();
}

// returns content length
int getGravitonJSON(char* dest, int n, double g, double t, double w) {
  const size_t bufferSize = JSON_OBJECT_SIZE(4);
  DynamicJsonBuffer jsonBuffer(bufferSize);
  
  JsonObject& root = jsonBuffer.createObject();
  root[F("name")] = hydrometerName;
  root[F("gravity")] = g;
  root[F("weight")] = w;
  root[F("temperature")] = t;
  
  int written = root.printTo(dest, n);
  return root.measureLength();
}

void sendToGoogleDrive(double gravity, double abw, double abv, double temperature, double weight, double weightDelta) {
  Serial.println(F("Google Drive output is not yet implemented"));
}

