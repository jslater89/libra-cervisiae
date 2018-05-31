/**
{
  "delaySeconds": 100,
  "hydrometerName": "01234567890123456789012345678901234567890123456789",
  "fullVoltage": 4.20000000000001,
  "wifiNetwork": "01234567890123456789012345678901234567890123456789",
  "wifiPassword": "01234567890123456789012345678901234567890123456789",
  "gravityCoefficients": [1.000000000001, 1.000000000001, 1.000000000001],
  "apiKey": "01234567890123456789012345678901234567890123456789"
}
 */

// How long between readings in hydrometer mode?
int delaySeconds = 1800; // half an hour

// What is the name of this hydrometer? Also used
// as the SSID for hotspot mode.
String hydrometerName = "pendulum";

// What is fully-charged battery voltage for this hydrometer?
float fullVoltage = 4.2;

// What wifi network should this hydrometer connect
// to in hydrometer mode?
String wifiNetwork;

// What password should it use?
String wifiPassword;

// What are the coefficients for the tilt->gravity
// polynomial?
double gravityCoefficients[3];

// What are the coefficients for correcting for temperature?
// 
const double temperatureCoefficients[3] = {0.00000154854, -0.000102756, -0.000167605}

// returns -1 for hydrometer name too long, -2 for wifi network name too long,
// -3 for wifi password too long, -4 for delay out of range.
int saveConfig() {
  if(hydrometerName.length() > 50) {
    return -1;
  }
  if(wifiNetwork.length() > 50) {
    return -2;
  }
  if(wifiPassword.length() > 50) {
    return -3;
  }
  if(delaySeconds > 4200) {
    return -4;
  }

  // get string, save file
}

int loadConfig() {

  // load file, get string, put into variables
}

/* decoding
const size_t bufferSize = 2*JSON_ARRAY_SIZE(3) + JSON_OBJECT_SIZE(7) + 650;
DynamicJsonBuffer jsonBuffer(bufferSize);

const char* json = "{\"delaySeconds\":100,\"hydrometerName\":\"01234567890123456789012345678901234567890123456789\",\"fullVoltage\":4.20000000000001,\"wifiNetwork\":\"01234567890123456789012345678901234567890123456789\",\"wifiPassword\":\"01234567890123456789012345678901234567890123456789\",\"gravityCoefficient\":[1.000000000001,1.000000000001,1.000000000001]}";

JsonObject& root = jsonBuffer.parseObject(json);

int delaySeconds = root["delaySeconds"]; // 100
const char* hydrometerName = root["hydrometerName"]; // "01234567890123456789012345678901234567890123456789"
float fullVoltage = root["fullVoltage"]; // 4.20000000000001
const char* wifiNetwork = root["wifiNetwork"]; // "01234567890123456789012345678901234567890123456789"
const char* wifiPassword = root["wifiPassword"]; // "01234567890123456789012345678901234567890123456789"

JsonArray& gravityCoefficient = root["gravityCoefficient"];
float gravityCoefficient0 = gravityCoefficient[0]; // 1.000000000001
float gravityCoefficient1 = gravityCoefficient[1]; // 1.000000000001
float gravityCoefficient2 = gravityCoefficient[2]; // 1.000000000001

const char* apiKey = root["apiKey"]; // "01234567890123456789012345678901234567890123456789"
*/

/* encoding
const size_t bufferSize = 2*JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(8);
DynamicJsonBuffer jsonBuffer(bufferSize);

JsonObject& root = jsonBuffer.createObject();
root["delaySeconds"] = 100;
root["hydrometerName"] = "01234567890123456789012345678901234567890123456789";
root["fullVoltage"] = 4.20000000000001;
root["wifiNetwork"] = "01234567890123456789012345678901234567890123456789";
root["wifiPassword"] = "01234567890123456789012345678901234567890123456789";

JsonArray& gravityCoefficient = root.createNestedArray("gravityCoefficient");
gravityCoefficient.add(1.000000000001);
gravityCoefficient.add(1.000000000001);
gravityCoefficient.add(1.000000000001);

root["apiKey"] = "01234567890123456789012345678901234567890123456789";

root.printTo(Serial);
 */
