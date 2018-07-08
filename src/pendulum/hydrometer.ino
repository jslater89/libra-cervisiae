
/**
 * Hydrometer mode
 */

void hydrometerSetup() {
  WiFi.begin(wifiNetwork, wifiPassword);

  Serial.print("Connecting to ");
  Serial.print(wifiNetwork); Serial.print(" ");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(500);
    Serial.print(".");

    if(i++ > 20) {
      Serial.println();
      Serial.println("Connection timed out; going back to sleep");
      sleep();
      return;
    }
  }

  Serial.println();
  Serial.println("Connected!");
  
  if(DEBUG_TIMINGS) Serial.print("Wifi finished: "); Serial.println(millis() - bootMillis);

  sensorSetup();

  if(DEBUG_TIMINGS) Serial.print("Sensors finished: "); Serial.println(millis() - bootMillis);

  yield();
  drd.stop();

  double temp;
  readTemp(&temp);

  if(DEBUG_TIMINGS) Serial.print("Temperature read: "); Serial.println(millis() - bootMillis);

  yield();
  
  int weight;
  averageWeight(&weight, 50);

  if(DEBUG_TIMINGS) Serial.print("Weight read: "); Serial.println(millis() - bootMillis);

  yield();

  double gravity = calculateGravity(weight / 1000.0);
  double compensatedGravity = compensateTemperature(gravity, temp);
  double voltage = readVoltage();

  if(DEBUG_TIMINGS) Serial.print("Calculations finished: "); Serial.println(millis() - bootMillis);

  Serial.print("Temp: "); Serial.println(temp, 2);
  Serial.print("Wght: "); Serial.println(weight);
  Serial.print("RawG: "); Serial.println(gravity, 3);
  Serial.print("CorG: "); Serial.println(compensatedGravity, 3);
  Serial.print("BatV: "); Serial.println(voltage, 3);

  yield();

  sendToGraviton(compensatedGravity, temp, voltage);

  if(DEBUG_TIMINGS) Serial.print("Output finished: "); Serial.println(millis() - bootMillis);

  Serial.println("Finished waking");
  sleep();
}

void sleep() {
  drd.stop();
  sensorShutdown();
  Serial.print("Going to sleep for "); Serial.print(delaySeconds); Serial.println(" seconds");
  ESP.deepSleep(delaySeconds * 1000 * 1000);
}

// Hydrometer loop
void hydrometerLoop() {
  // no-op
}

// Get the compensated gravity readings.
double getGravity(double weight, double temp) {
  return compensateTemperature(calculateGravity(weight), temp);
}

// Calculate gravity from weight, using the calibrated polynomial.
double calculateGravity(double weight) {
  double c1, c2, c3;
  c1 = gravityCoefficients[0];
  c2 = gravityCoefficients[1];
  c3 = gravityCoefficients[2];
  return c1 * weight * weight + c2 * weight + c3;
}

// Compensate for temperature, using the calibrated polynomial.
double compensateTemperature(double gravity, double temp) {
  double c1, c2, c3;
  c1 = temperatureCoefficients[0];
  c2 = temperatureCoefficients[1];
  c3 = temperatureCoefficients[2];
  return gravity + c1 * temp * temp + c2 * temp + c3;
}

