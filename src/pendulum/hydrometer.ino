
// Hydrometer loop
void hydrometerLoop() {

  // Sleep as configured
  ESP.deepSleep(delaySeconds * 1000 * 1000);
}

double getGravity(double acX, double acY, double acZ, double temp) {
  return compensateTemperature(calculateGravity(calculateTilt(acX, acY, acZ)), temp);
}

double calculateTilt(double acX, double acY, double acZ) {
  return atan(-1 * acX / sqrt(pow(acY, 2) + pow(acZ, 2))) * 180 / PI;
}

double calculateGravity(double tilt) {
  double c1, c2, c3;
  c1 = gravityCoefficients[0];
  c2 = gravityCoefficients[1];
  c3 = gravityCoefficients[2];
  return c1 * tilt * tilt + c2 * tilt + c3;
}

double compensateTemperature(double gravity, double temp) {
  double c1, c2, c3;
  c1 = temperatureCoefficients[0];
  c2 = temperatureCoefficients[1];
  c3 = temperatureCoefficients[2];
  return gravity + c1 * temp * temp + c2 * temp + c3;
}

