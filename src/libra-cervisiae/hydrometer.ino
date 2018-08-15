
/**
 * Hydrometer mode
 */

// gram of sugar lost
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
  temperatureCorrectCalibrated(boardTemp, &weight);

  if(DEBUG_TIMINGS) Serial.print("Weight read: "); Serial.println(millis() - bootMillis);

  yield();

  double wortWeight = weight - equipmentWeight;
  double abw = getBatchABW(wortWeight);
  double abv = calculateABV(abw);
  double gravity = calculateGravity(startingWortGravity, abv);

  if(DEBUG_TIMINGS) Serial.print("Calculations finished: "); Serial.println(millis() - bootMillis);

  Serial.print("BTmp: "); Serial.println(boardTemp, 2);
  Serial.print("WTmp: "); Serial.println(wortTemp, 2);
  Serial.print("Wght: "); Serial.println(weight);
  Serial.print("CorG: "); Serial.println(gravity, 3);

  yield();

  handleOutput(gravity, abw, abv, wortTemp, weight, startingWortMass - wortWeight);

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

double getBatchABW(double currentNoEquipmentMass) {
  double weightDelta = startingWortMass - currentNoEquipmentMass;
  double alcoholMass = getAlcoholMass(weightDelta);
  double yeastMass = getYeastMass(weightDelta);
  return getABW(alcoholMass, currentNoEquipmentMass - yeastMass);
}

// CO2 is what's actually leaving the fermentation vessel. When (co2PerGramLost) grams
// weight delta shows up, that means we've fermented one gram of sugar.
double getAlcoholMass(double weightDelta) {
  return weightDelta * (alcoholPerGramLost / co2PerGramLost);
}

double getYeastMass(double weightDelta) {
  return weightDelta * (yeastPerGramLost / co2PerGramLost);
}

double getCO2Mass(double weightDelta) {
  return weightDelta;
}

double getABW(double alcoholMass, double beerMass) {
  // alcohol mass is calculated. Beer mass is the mass of the
  // beer minus equipment mass and yeast biomass.

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
