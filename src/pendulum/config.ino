
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

// What are the coefficients for the tilt->gravity and
// temperature->gravity offset polynomials?
double gravityCoefficients[3];
double temperatureCoefficients[3];
