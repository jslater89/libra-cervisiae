/**
 * Config holds functions related to configuration JSON, saving to SPIFFS, and
 * reading from SPIFFS.
 * 
{
  "delaySeconds": 3600,
  "hydrometerName": "01234567890123456789012345678901234567890123456789",
  "fullVoltage": 4.20000000000001,
  "tempCompensationBase": 68.5,
  "tempCompensationFactor": 0.000935,
  "wifiNetwork": "01234567890123456789012345678901234567890123456789",
  "wifiPassword": "01234567890123456789012345678901234567890123456789",
  "apiKey": "01234567890123456789012345678901234567890123456789",
  "apiRoot": "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789",
  "apiPath": "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789",

  "bootToHotspot": false,
  "outputMode" 1,
}
 */

void printConfig() {
  Serial.print("Hydrometer name: "); Serial.println(hydrometerName);
  Serial.print("Delay seconds: "); Serial.println(delaySeconds);
  Serial.print("Full voltage: "); Serial.println(fullVoltage);
  Serial.print("Wifi network: "); Serial.println(wifiNetwork);
  Serial.print("Wifi password: "); Serial.println(wifiPassword);
  Serial.print("API root: "); Serial.println(apiRoot);
  Serial.print("API path: "); Serial.println(apiPath);
  Serial.print("API port: "); Serial.println(apiPort);
  Serial.print("API key: "); Serial.println(apiKey);
  Serial.print("Hotspot boot: "); Serial.println(bootToHotspot);
  Serial.print("Output mode: "); Serial.println(outputMode);
  Serial.print("Temp compensation base: "); Serial.println(tempCompensationBase);
  Serial.print("Temp compensation factor: "); Serial.println(tempCompensationFactor, 6);
  Serial.print("Tare offset: "); Serial.println(tareOffset, 2);
  Serial.print("Scale factor: "); Serial.println(scaleFactor, 4);
  Serial.print("Equipment weight: "); Serial.println(equipmentWeight, 1);
  Serial.print("Starting mass: "); Serial.println(startingWortMass, 1);
  Serial.print("Starting SG: "); Serial.println(startingWortGravity, 3);
}

void getConfigJSON(char* buf, int lim) {
  const size_t bufferSize = JSON_ARRAY_SIZE(3) + JSON_OBJECT_SIZE(11) + 800;
  DynamicJsonBuffer jsonBuffer(bufferSize);
  
  JsonObject& root = jsonBuffer.createObject();
  root["delaySeconds"] = delaySeconds;
  root["hydrometerName"] = hydrometerName;
  root["fullVoltage"] = fullVoltage;
  root["wifiNetwork"] = wifiNetwork;
  root["wifiPassword"] = wifiPassword;

  root["bootToHotspot"] = bootToHotspot;
  root["outputMode"] = outputMode;

  root["tempCompensationBase"] = tempCompensationBase;
  root["tempCompensationFactor"] = tempCompensationFactor;
  root["tareOffset"] = tareOffset;
  root["scaleFactor"] = scaleFactor;
  root["equipmentWeight"] = equipmentWeight;
  root["startingWortMass"] = startingWortMass;
  root["startingWortGravity"] = startingWortGravity;
  root["boardTempAddr"] = boardTempAddr;
  root["wortTempAddr"] = wortTempAddr;

  root["apiPath"] = apiPath;
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

  char configJSON[1536];
  getConfigJSON(configJSON, 1536);
  f.print(configJSON);
  f.close();

  return true;
}

// loads config from config.json in FS
boolean loadConfig() {
  // ensure null-termination; the 51st element is always 0 in arrays where only
  // 50 elements are copied.
  hydrometerName[50] = wifiNetwork[50] = wifiPassword[50] = apiKey[50] = apiRoot[150] = apiPath[150] = 0;
  
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
  const size_t bufferSize = JSON_ARRAY_SIZE(3) + JSON_OBJECT_SIZE(11) + 800;
  DynamicJsonBuffer jsonBuffer(bufferSize);  
  JsonObject& root = jsonBuffer.parseObject(json);

  if(strlen(root["hydrometerName"]) > 50 || strlen(root["hydrometerName"]) == 0) return false;
  if(strlen(root["wifiNetwork"]) > 50) return false;
  if(strlen(root["wifiPassword"]) > 50) return false;
  if(strlen(root["apiKey"]) > 50) return false;
  if(strlen(root["apiRoot"]) > 150) return false;
  if(strlen(root["apiPath"]) > 150) return false;

  if(root["delaySeconds"] > 4200 || root["delaySeconds"] < 0) return false;
  if(root["fullVoltage"] < 3.2) return false;
  
  delaySeconds = root["delaySeconds"];
  strncpy(hydrometerName, root["hydrometerName"], 50);
  strncpy(wifiNetwork, root["wifiNetwork"], 50);
  strncpy(wifiPassword, root["wifiPassword"], 50);
  strncpy(apiKey, root["apiKey"], 50);
  strncpy(apiRoot, root["apiRoot"], 150);
  strncpy(apiPath, root["apiPath"], 150);
  apiPort = root["apiPort"];

  bootToHotspot = root["bootToHotspot"];
  outputMode = root["outputMode"];
  fullVoltage = root["fullVoltage"];
  tempCompensationBase = root["tempCompensationBase"];
  tempCompensationFactor = root["tempCompensationFactor"];
  tareOffset = root["tareOffset"];
  scaleFactor = root["scaleFactor"];
  equipmentWeight = root["equipmentWeight"];
  startingWortMass = root["startingWortMass"];
  startingWortGravity = root["startingWortGravity"];
  boardTempAddr = root["boardTempAddr"];
  wortTempAddr = root["wortTempAddr"];

  return true;
}

/* encoding

 */
