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

#define LONG_STRING_SIZE 65

char wortAddrStr[65];
char boardAddrStr[65];

void printConfig() {
  Serial.print(F("Hydrometer name: ")); Serial.println(hydrometerName);
  Serial.print(F("Delay seconds: ")); Serial.println(delaySeconds);
  Serial.print(F("Full voltage: ")); Serial.println(fullVoltage);
  Serial.print(F("Wifi network: ")); Serial.println(wifiNetwork);
  Serial.print(F("Wifi password: ")); Serial.println(wifiPassword);
  Serial.print(F("API root: ")); Serial.println(apiRoot);
  Serial.print(F("API path: ")); Serial.println(apiPath);
  Serial.print(F("API port: ")); Serial.println(apiPort);
  Serial.print(F("API key: ")); Serial.println(apiKey);
  Serial.print(F("Hotspot boot: ")); Serial.println(bootToHotspot);
  Serial.print(F("Output mode: ")); Serial.println(outputMode);
  Serial.print(F("Temp compensation base: ")); Serial.println(tempCompensationBase);
  Serial.print(F("Temp compensation factor: ")); Serial.println(tempCompensationFactor, 6);
  Serial.print(F("Tare offset: ")); Serial.println(tareOffset, 2);
  Serial.print(F("Scale factor: ")); Serial.println(scaleFactor, 4);
  Serial.print(F("Equipment weight: ")); Serial.println(equipmentWeight, 1);
  Serial.print(F("Starting mass: ")); Serial.println(startingWortMass, 1);
  Serial.print(F("Starting SG: ")); Serial.println(startingWortGravity, 3);
  Serial.print(F("Wort address: ")); printAddress(wortTempAddr); Serial.println();
  Serial.print(F("Board address: ")); printAddress(boardTempAddr); Serial.println();
  
}

void getConfigJSON(char* buf, int lim) {
  const size_t bufferSize = JSON_ARRAY_SIZE(3) + JSON_OBJECT_SIZE(11) + 800;
  DynamicJsonBuffer jsonBuffer(bufferSize);
  
  JsonObject& root = jsonBuffer.createObject();
  root[F("delaySeconds")] = delaySeconds;
  root[F("hydrometerName")] = hydrometerName;
  root[F("fullVoltage")] = fullVoltage;
  root[F("wifiNetwork")] = wifiNetwork;
  root[F("wifiPassword")] = wifiPassword;

  root[F("bootToHotspot")] = bootToHotspot;
  root[F("outputMode")] = outputMode;

  root[F("tempCompensationBase")] = tempCompensationBase;
  root[F("tempCompensationFactor")] = tempCompensationFactor;
  root[F("tareOffset")] = tareOffset;
  root[F("scaleFactor")] = scaleFactor;
  root[F("equipmentWeight")] = equipmentWeight;
  root[F("startingWortMass")] = startingWortMass;
  root[F("startingWortGravity")] = startingWortGravity;

  convertUint8ToChar(boardTempAddr, boardAddrStr, 8);
  convertUint8ToChar(wortTempAddr, wortAddrStr, 8);
  
  root[F("boardTempAddr")] = boardAddrStr;
  root[F("wortTempAddr")] = wortAddrStr;

  root[F("apiPath")] = apiPath;
  root[F("apiRoot")] = apiRoot;
  root[F("apiKey")] = apiKey;
  root[F("apiPort")] = apiPort;
  root.prettyPrintTo(buf, lim);
}

// saves config to config.json in FS
boolean saveConfig() {
  // ArduinoJSON will happily set number values to
  // Infinity or probably NaN, sans quotes; those
  // values aren't valid JSON.
  if(isinf(scaleFactor)) scaleFactor = 0;
  
  File f = SPIFFS.open(F("/config.json"), "w");
  if(!f) {
    Serial.println(F("Unable to open config file"));
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
  
  File f = SPIFFS.open(F("/config.json"), "r");
  if(!f) {
    Serial.println(F("Unable to load config file"));
    return false;
  }

  String contents = f.readString();
  f.close();
  boolean result = decodeJSON(contents, true);

  if(!result) {
    Serial.println(F("Unable to decode JSON"));
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

  if(strlen(root[F("hydrometerName")]) > 50 || strlen(root[F("hydrometerName")]) == 0) return false;
  if(strlen(root[F("wifiNetwork")]) > 50) return false;
  if(strlen(root[F("wifiPassword")]) > 50) return false;
  if(strlen(root[F("apiKey")]) > 50) return false;
  if(strlen(root[F("apiRoot")]) > 150) return false;
  if(strlen(root[F("apiPath")]) > 150) return false;

  if(root[F("delaySeconds")] > 4200 || root[F("delaySeconds")] < 0) return false;
  if(root[F("fullVoltage")] < 3.2) return false;
  
  delaySeconds = root[F("delaySeconds")];
  strncpy(hydrometerName, root[F("hydrometerName")], 50);
  strncpy(wifiNetwork, root[F("wifiNetwork")], 50);
  strncpy(wifiPassword, root[F("wifiPassword")], 50);
  strncpy(apiKey, root[F("apiKey")], 50);
  strncpy(apiRoot, root[F("apiRoot")], 150);
  strncpy(apiPath, root[F("apiPath")], 150);
  apiPort = root[F("apiPort")];

  bootToHotspot = root[F("bootToHotspot")];
  outputMode = root[F("outputMode")];
  fullVoltage = root[F("fullVoltage")];
  tempCompensationBase = root[F("tempCompensationBase")];
  tempCompensationFactor = root[F("tempCompensationFactor")];
  tareOffset = root[F("tareOffset")];
  scaleFactor = root[F("scaleFactor")];
  equipmentWeight = root[F("equipmentWeight")];
  startingWortMass = root[F("startingWortMass")];
  startingWortGravity = root[F("startingWortGravity")];

  strncpy(wortAddrStr, root[F("wortTempAddr")], 65);
  strncpy(boardAddrStr, root[F("boardTempAddr")], 65);
  
  convertCharToUint8(boardAddrStr, boardTempAddr, 8);
  convertCharToUint8(wortAddrStr, wortTempAddr, 8);

  return true;
}

/* encoding

 */
