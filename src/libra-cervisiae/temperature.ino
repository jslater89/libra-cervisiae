
#ifdef WEMOS
#define DS18B20_POWER_PIN 12
#define DS18B20_DATA_PIN 13

#elif defined PCB
#define DS18B20_POWER_PIN 12
#define DS18B20_DATA_PIN 13

#elif defined NODEMCU
#define DS18B20_POWER_PIN 12
#define DS18B20_DATA_PIN 13

#endif

OneWire oneWire(DS18B20_DATA_PIN);
DallasTemperature sensors(&oneWire);

void tempSetup() {
  //DS18B20
  pinMode(DS18B20_POWER_PIN, OUTPUT);
  digitalWrite(DS18B20_POWER_PIN, HIGH);
  
  sensors.begin();
  sensors.setResolution(12);
}

void tempShutdown() {
  digitalWrite(DS18B20_POWER_PIN, LOW);
}

// Get temperature from wort sensor
// returns Fahrenheit temperature
void readWortTemp(double* t) {
  sensors.requestTemperaturesByAddress(&wortTempAddr);

  // 12-bit temperature takes 750ms. Delay so the ESP can do its thing
  // while we wait.
  delay(750);
  *t = sensors.getTempF(&wortTempAddr);
}

// Get temperature from board sensor
// returns Fahrenheit temperature
void readBoardTemp(double* t) {
  sensors.requestTemperaturesByAddress(&boardTempAddr);

  // 12-bit temperature takes 750ms. Delay so the ESP can do its thing
  // while we wait.
  delay(750);
  *t = sensors.getTempF(&boardTempAddr);
}

