
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
  WiFiClientSecure client;
  boolean result = client.connect("script.google.com", 443);

  if(result) {
    const int pathLength = 300;
    char path[pathLength];
    strcpy(path, "GET ");
    strncpy(path + strlen(path), apiPath, pathLength - strlen(path));
  
    const char* gravityParam = "?gravity=";
    const char* abwParam = "&abw=";
    const char* abvParam = "&abv=";
    const char* tempParam = "&wortTemp=";
    const char* weightParam = "&weight=";
    const char* weightDeltaParam = "&weightDelta=";
  
    strncpy(path + strlen(path), gravityParam, pathLength - strlen(path));
    snprintf(path + strlen(path), gravity, "%f", pathLength - strlen(path));
  
    strncpy(path + strlen(path), abwParam, pathLength - strlen(path));
    snprintf(path + strlen(path), abw, "%f", pathLength - strlen(path));
  
    strncpy(path + strlen(path), abvParam, pathLength - strlen(path));
    snprintf(path + strlen(path), abv, "%f", pathLength - strlen(path));
  
    strncpy(path + strlen(path), tempParam, pathLength - strlen(path));
    snprintf(path + strlen(path), temperature, "%f", pathLength - strlen(path));
  
    strncpy(path + strlen(path), weightParam, pathLength - strlen(path));
    snprintf(path + strlen(path), weight, "%f", pathLength - strlen(path));
  
    strncpy(path + strlen(path), weightDeltaParam, pathLength - strlen(path));
    snprintf(path + strlen(path), weightDelta, "%f", pathLength - strlen(path));

    strncpy(path + strlen(path), " HTTP/1.1", pathLength - strlen(path));
    
    client.println("GET /api/v1/reading HTTP/1.1");
    client.print("Host: "); client.println("script.google.com");
    client.println("Cache-Control: no-cache");

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

