
#ifdef WEMOS
#define HX711_POWER_PIN 14
#define HX711_DATA_PIN 5
#define HX711_CLOCK_PIN 4
#define DS18B20_POWER_PIN 12
#define DS18B20_DATA_PIN 13

#elif defined PCB
#define HX711_POWER_PIN 14
#define HX711_DATA_PIN 5
#define HX711_CLOCK_PIN 4
#define DS18B20_POWER_PIN 12
#define DS18B20_DATA_PIN 13

#elif defined NODEMCU
#define HX711_POWER_PIN 14
#define HX711_DATA_PIN 5
#define HX711_CLOCK_PIN 4
#define DS18B20_POWER_PIN 12
#define DS18B20_DATA_PIN 13

#endif

#ifdef PCB
#define VOLTAGE_MOD 1.012
#else
#define VOLTAGE_MOD 1.0
#endif


HX711 scale;
OneWire oneWire(DS18B20_DATA_PIN);
DallasTemperature sensors(&oneWire);

void sensorSetup() {
  //HX711
  pinMode(HX711_POWER_PIN, OUTPUT);
  digitalWrite(HX711_POWER_PIN, HIGH);

  //DS18B20
  pinMode(DS18B20_POWER_PIN, OUTPUT);
  digitalWrite(DS18B20_POWER_PIN, HIGH);
  
  scale.begin(HX711_DATA_PIN, HX711_CLOCK_PIN);   
  sensors.begin();

  sensors.setResolution(12);

  delay(500);
}

void sensorShutdown() {
  digitalWrite(HX711_POWER_PIN, LOW);
  digitalWrite(DS18B20_POWER_PIN, LOW);
}

double readVoltage() {
  pinMode(A0, INPUT);
  int raw = analogRead(A0);
  double voltage = raw/1023.0 * VOLTAGE_MOD;
  voltage = voltage*4.2;

  return voltage;
}

void averageWeight(int* total, int count) {
  int t = 0;
  for(int i = 0; i < count; i++) {
    readWeight(total);
    t += *total;

    // 10Hz
    delay(100);
  }

  *total = (t / count);
}

// returns raw accelerometer values
void readWeight(int* weight) {
  *weight = scale.read();
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

