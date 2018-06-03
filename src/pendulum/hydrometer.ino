

void hydrometerSetup() {
  WiFi.begin(wifiNetwork, wifiPassword);

  Serial.print("Connecting to ");
  Serial.print(wifiNetwork); Serial.print(" ");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(500);
    Serial.print(".");

    if(i > 20) {
      Serial.println();
      Serial.print("Connection timed out; going back to sleep");
      sleep();
      return;
    }
  }

  Serial.println();
  Serial.println("Connected!");

  sensorSetup();

  double temp;
  averageTemp(&temp, 25, 20);
  
  int x, y, z;
  averageAccel(&x, &y, &z, 25, 20);

  double tilt = calculateTilt(x, y, z);
  double gravity = calculateGravity(tilt);
  double compensatedGravity = compensateTemperature(gravity, temp);

  Serial.print("Temp: "); Serial.println(temp, 2);
  Serial.print("Tilt: "); Serial.println(tilt, 2);
  Serial.print("RawG: "); Serial.println(gravity, 3);
  Serial.print("CorG: "); Serial.println(compensatedGravity, 3);

  sleep();
}

void sleep() {
  drd.stop();
  sensorShutdown();
  Serial.print("Going to sleep for "); Serial.print(delaySeconds); Serial.println(" seconds");
  // Sleep as configured
  ESP.deepSleep(delaySeconds * 1000 * 1000);
}

// Hydrometer loop
void hydrometerLoop() {
  // no-op
}

// Get the compensated gravity readings.
double getGravity(double acX, double acY, double acZ, double temp) {
  return compensateTemperature(calculateGravity(calculateTilt(acX, acY, acZ)), temp);
}

// Calculate tilt from raw accelerometer readings.
double calculateTilt(int x, int y, int z) {
  double pitch = (atan2(y, sqrt(x * x + z * z))) * 180.0 / PI;
  double roll = (atan2(x, sqrt(y * y + z * z))) * 180.0 / PI;

  // 0 tilt is a vertical hydrometer, which means the GPS Z-axis
  // is pointing due sideways. 90 tilt is a horizontal hydrometer,
  // which means the GPS Z-axis is pointing due up.
  double tilt =  90 - sqrt(pitch * pitch + roll * roll);

  return tilt;
}

// Calculate gravity from tilt, using the calibrated polynomial.
double calculateGravity(double tilt) {
  double c1, c2, c3;
  c1 = gravityCoefficients[0];
  c2 = gravityCoefficients[1];
  c3 = gravityCoefficients[2];
  return c1 * tilt * tilt + c2 * tilt + c3;
}

// Compensate for temperature, using the calibrated polynomial.
double compensateTemperature(double gravity, double temp) {
  double c1, c2, c3;
  c1 = temperatureCoefficients[0];
  c2 = temperatureCoefficients[1];
  c3 = temperatureCoefficients[2];
  return gravity + c1 * temp * temp + c2 * temp + c3;
}

