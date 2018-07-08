/**
 * Config holds functions related to configuration JSON, saving to SPIFFS, and
 * reading from SPIFFS.
 * 
{
  "delaySeconds": 100,
  "hydrometerName": "01234567890123456789012345678901234567890123456789",
  "fullVoltage": 4.20000000000001,
  "wifiNetwork": "01234567890123456789012345678901234567890123456789",
  "wifiPassword": "01234567890123456789012345678901234567890123456789",
  "gravityCoefficients": [1.000000000001, 1.000000000001, 1.000000000001],
  "apiKey": "01234567890123456789012345678901234567890123456789",
  "apiRoot": "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
}
 */

// What are the coefficients for correcting for temperature?
// Taken from a hydrometer correction chart
const double temperatureCoefficients[3] = {0.00000154854, -0.000102756, -0.000167605};

void printConfig() {
  Serial.print("Hydrometer name: "); Serial.println(hydrometerName);
  Serial.print("Delay seconds: "); Serial.println(delaySeconds);
  Serial.print("Full voltage: "); Serial.println(fullVoltage);
  Serial.print("Wifi network: "); Serial.println(wifiNetwork);
  Serial.print("Wifi password: "); Serial.println(wifiPassword);
  Serial.print("API root: "); Serial.println(apiRoot);
  Serial.print("API port: "); Serial.println(apiPort);
  Serial.print("API key: "); Serial.println(apiKey);
  Serial.print("a: "); Serial.println(gravityCoefficients[0], 10);
  Serial.print("b: "); Serial.println(gravityCoefficients[1], 10);
  Serial.print("c: "); Serial.println(gravityCoefficients[2], 10);
}

void getConfigJSON(char* buf, int lim) {
  const size_t bufferSize = 2*JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(10);
  DynamicJsonBuffer jsonBuffer(bufferSize);
  
  JsonObject& root = jsonBuffer.createObject();
  root["delaySeconds"] = delaySeconds;
  root["hydrometerName"] = hydrometerName;
  root["fullVoltage"] = fullVoltage;
  root["wifiNetwork"] = wifiNetwork;
  root["wifiPassword"] = wifiPassword;
  
  JsonArray& c = root.createNestedArray("gravityCoefficients");
  c.add(gravityCoefficients[0]);
  c.add(gravityCoefficients[1]);
  c.add(gravityCoefficients[2]);

  root["apiRoot"] = apiRoot;
  root["apiKey"] = apiKey;
  root["apiPort"] = apiPort;
  root.prettyPrintTo(buf, lim);
}

// saves config to config.json in FS
boolean saveConfig() {
  File f = SPIFFS.open("/config.json", "w");
  if(!f) {
    Serial.println("Unable to open config file");
    return false;
  }

  char configJSON[1024];
  getConfigJSON(configJSON, 1024);
  f.print(configJSON);
  f.close();

  return true;
}

// loads config fromconfig.json in FS
boolean loadConfig() {
  // ensure null-termination; the 51st element is always 0 in arrays where only
  // 50 elements are copied.
  hydrometerName[50] = wifiNetwork[50] = wifiPassword[50] = apiKey[50] = apiRoot[150] = 0;
  
  File f = SPIFFS.open("/config.json", "r");
  if(!f) {
    Serial.println("Unable to load config file");
    return false;
  }

  String contents = f.readString();
  f.close();
  boolean result = decodeJSON(contents, true);

  if(!result) {
    Serial.println("Unable to decode JSON");
    return false;
  }
  else {
    return true;
  }
}

boolean decodeJSON(String json, boolean decodeCoefficients) {
  const size_t bufferSize = 2*JSON_ARRAY_SIZE(3) + JSON_OBJECT_SIZE(10) + 650;
  DynamicJsonBuffer jsonBuffer(bufferSize);  
  JsonObject& root = jsonBuffer.parseObject(json);

  if(strlen(root["hydrometerName"]) > 50 || strlen(root["hydrometerName"]) == 0) return false;
  if(strlen(root["wifiNetwork"]) > 50) return false;
  if(strlen(root["wifiPassword"]) > 50) return false;
  if(strlen(root["apiKey"]) > 50) return false;
  if(strlen(root["apiRoot"]) > 150) return false;

  if(root["delaySeconds"] > 4200 || root["delaySeconds"] < 0) return false;
  if(root["fullVoltage"] < 3.2) return false;
  
  delaySeconds = root["delaySeconds"];
  strncpy(hydrometerName, root["hydrometerName"], 50);
  strncpy(wifiNetwork, root["wifiNetwork"], 50);
  strncpy(wifiPassword, root["wifiPassword"], 50);
  strncpy(apiKey, root["apiKey"], 50);
  strncpy(apiRoot, root["apiRoot"], 150);
  apiPort = root["apiPort"];

  fullVoltage = root["fullVoltage"];

  if(decodeCoefficients) {
    JsonArray& loadedCoefficients = root["gravityCoefficients"];
    gravityCoefficients[0] = loadedCoefficients[0];
    gravityCoefficients[1] = loadedCoefficients[1];
    gravityCoefficients[2] = loadedCoefficients[2];
  }

  return true;
}

/* encoding

 */
