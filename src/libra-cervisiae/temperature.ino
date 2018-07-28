
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

  int sensorCount = sensors.getDS18Count();

  if(sensorCount > 2) {
    Serial.println("Warning: more than 2 DS18xxx sensors connected");
    sensorCount = 2;
  }

  for(int i = 0; i < sensorCount; i++) {
    uint8_t address = 0;
    boolean result = sensors.getAddress(&address, i);

    if(result) {
      tempSensors[i] = address;
    }
    else {
      tempSensors[i] = 0;
    }
  }

  bool foundWortSensor = false;
  bool foundBoardSensor = false;
  for(int i = 0; i < 2; i++) {
    if(tempSensors[i] == wortTempAddr) foundWortSensor = true;
    if(tempSensors[i] == boardTempAddr) foundBoardSensor = true;
  }

  if(!foundWortSensor) Serial.println("Warning: could not find wort sensor");
  if(!foundBoardSensor) Serial.println("Warning: could not find board sensor");
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

