
/**
 * Hydrometer mode
 */

void hydrometerSetup() {
  boolean result = tryConnect();

  if(!result) {
    Serial.println("Going back to sleep");
    sleep();
    return;
  }
  
  if(DEBUG_TIMINGS) Serial.print("Wifi finished: "); Serial.println(millis() - bootMillis);

  startSensors();

  if(DEBUG_TIMINGS) Serial.print("Sensors finished: "); Serial.println(millis() - bootMillis);

  yield();
  drd.stop();

  double boardTemp, wortTemp;
  readBoardTemp(&boardTemp);
  readWortTemp(&wortTemp);

  if(DEBUG_TIMINGS) Serial.print("Temperature read: "); Serial.println(millis() - bootMillis);

  yield();
  
  double weight;
  averageCalibratedWeight(&weight, 25);

  if(DEBUG_TIMINGS) Serial.print("Weight read: "); Serial.println(millis() - bootMillis);

  yield();

  double gravity = calculateGravity(weight);
  double compensatedGravity = compensateTemperature(gravity, boardTemp);

  if(DEBUG_TIMINGS) Serial.print("Calculations finished: "); Serial.println(millis() - bootMillis);

  Serial.print("BTmp: "); Serial.println(boardTemp, 2);
  Serial.print("WTmp: "); Serial.println(wortTemp, 2);
  Serial.print("Wght: "); Serial.println(weight);
  Serial.print("RawG: "); Serial.println(gravity, 3);
  Serial.print("CorG: "); Serial.println(compensatedGravity, 3);

  yield();

  handleOutput(compensatedGravity, wortTemp, weight);

  if(DEBUG_TIMINGS) Serial.print("Output finished: "); Serial.println(millis() - bootMillis);

  Serial.println("Finished waking");
  sleep();
}

void sleep() {
  drd.stop();
  stopSensors();
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

// Calculate gravity from weight, using the stored starting mass
// and Ballings' numbers
double calculateGravity(double weight) {
  return 0;
}

// Compensate for temperature, using the calibrated polynomial.
double compensateTemperature(double gravity, double temp) {
  // Adjust for load cell temperature effects by applying tempCompensationFactor
  // times the difference from calibration temperature.
  double loadCellAdjustment = (tempCompensationBase - temp) * tempCompensationFactor;
  gravity = gravity + loadCellAdjustment;

  return gravity;
}

