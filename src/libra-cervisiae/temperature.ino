

void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

void initTemp() {
  pinMode(DS18B20_POWER_PIN, OUTPUT);
  digitalWrite(DS18B20_POWER_PIN, HIGH);
}

void tempStart() {
  sensors.begin();
  sensors.setResolution(12);

  int sensorCount = sensors.getDS18Count();

  if(sensorCount > 2) {
    Serial.println(F("Warning: more than 2 DS18xxx sensors connected"));
    sensorCount = 2;
  }
  if(DEBUG_DS18XXX) {
    Serial.print(F("Located ")); Serial.print(sensorCount); Serial.println(F(" DS18xxx sensors"));
  }
  

  for(int i = 0; i < sensorCount; i++) {
    boolean result = sensors.getAddress(tempSensors[i], i);

    if(result) {
      if(DEBUG_DS18XXX) {
        Serial.print(F("Address: "));
        printAddress(tempSensors[i]);
        Serial.println();
      }
    }
  }
}

// Get temperature from wort sensor
// returns Fahrenheit temperature
void readWortTemp(double* t) {
  sensors.requestTemperaturesByAddress(wortTempAddr);

  // 12-bit temperature takes 750ms. Delay so the ESP can do its thing
  // while we wait.
  delay(750);
  *t = sensors.getTempF(wortTempAddr);
}

// Get temperature from board sensor
// returns Fahrenheit temperature
void readBoardTemp(double* t) {
  sensors.requestTemperaturesByAddress(boardTempAddr);

  // 12-bit temperature takes 750ms. Delay so the ESP can do its thing
  // while we wait.
  delay(750);
  *t = sensors.getTempF(boardTempAddr);
}

void readTempByAddress(DeviceAddress a, double* t) {
  sensors.requestTemperaturesByAddress(a);

  delay(750);
  *t = sensors.getTempF(a);
}

