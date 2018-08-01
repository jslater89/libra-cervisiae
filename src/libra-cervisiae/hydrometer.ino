
/**
 * Hydrometer mode
 */

const double alcoholPerGramLost = 0.48391;
const double co2PerGramLost = 0.46286;
const double yeastPerGramLost = 0.05323;

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

  double abw = getBatchABW(weight);
  double abv = calculateABV(abw);
  double gravity = calculateGravity(startingWortGravity, abv);

  if(DEBUG_TIMINGS) Serial.print("Calculations finished: "); Serial.println(millis() - bootMillis);

  Serial.print("BTmp: "); Serial.println(boardTemp, 2);
  Serial.print("WTmp: "); Serial.println(wortTemp, 2);
  Serial.print("Wght: "); Serial.println(weight);
  Serial.print("CorG: "); Serial.println(gravity, 3);

  yield();

  handleOutput(gravity, wortTemp, weight);

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

double getBatchABW(double currentMass) {
  double weightDelta = startingWortMass - currentMass;
  double alcoholMass = getAlcoholMass(weightDelta);
  return getABW(alcoholMass, currentMass);
}

double getAlcoholMass(double weightDelta) {
  return weightDelta * alcoholPerGramLost;
}

double getYeastMass(double weightDelta) {
  return weightDelta * yeastPerGramLost;
}

double getCO2Mass(double weightDelta) {
  return weightDelta * co2PerGramLost;
}

double getABW(double alcoholMass, double beerMass) {
  // alcohol mass is calculated, beer mass is the total
  // mass on the scale, so it's pretty simple

  return alcoholMass / beerMass * 100;
}

double calculateABV(double abw) {
  // Per OmniCalc
  abw = abw / 100; // pct to decimal
  return (abw / (0.789 + 0.211 * abw)) * 100;
}

double calculateGravity(double originalGravity, double abv) {
  // not a great estimate, but that's life
  double numerator = (abv - 131.25 * originalGravity);
  return numerator / -131.25;
}
