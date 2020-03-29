
/**
 * Hydrometer mode
 */

#include <Arduino.h>
#include <pgmspace.h>
#include "libra-cervisiae.h"
#include "config.h"
#include "hotspot.h"
#include "hydrometer.h"
#include "sensors.h"
#include "temperature.h"
#include "scale.h"
#include "output.h"

// gram of sugar lost
const double alcoholPerGramLost = 0.48391;
const double co2PerGramLost = 0.46286;
const double yeastPerGramLost = 0.05323;

void hydrometerSetup() {
  bool result = tryConnect();

  if(!result) {
    Serial.println(F("Going back to sleep"));
    sleep();
    return;
  }
  
  if(DEBUG_TIMINGS) Serial.print(F("Wifi finished: ")); Serial.println(millis() - bootMillis);

  startSensors();

  if(DEBUG_TIMINGS) Serial.print(F("Sensors finished: ")); Serial.println(millis() - bootMillis);

  yield();

  double boardTemp, wortTemp;
  readBoardTemp(&boardTemp);
  readWortTemp(&wortTemp);

  if(DEBUG_TIMINGS) Serial.print(F("Temperature read: ")); Serial.println(millis() - bootMillis);

  yield();
  
  double weight;
  averageCalibratedWeight(&weight, 25);
  temperatureCorrectCalibrated(boardTemp, &weight);

  if(DEBUG_TIMINGS) Serial.print(F("Weight read: ")); Serial.println(millis() - bootMillis);

  yield();

  double wortWeight = weight - equipmentWeight;
  double abw = getBatchABW(wortWeight);
  double abv = calculateABV(abw);
  double gravity = calculateGravity(startingWortGravity, abv);

  if(DEBUG_TIMINGS) Serial.print(F("Calculations finished: ")); Serial.println(millis() - bootMillis);

  Serial.print(F("BTmp: ")); Serial.println(boardTemp, 2);
  Serial.print(F("WTmp: ")); Serial.println(wortTemp, 2);
  Serial.print(F("Wght: ")); Serial.println(weight);
  Serial.print(F("CorG: ")); Serial.println(gravity, 3);

  yield();

  handleOutput(gravity, abw, abv, wortTemp, weight, startingWortMass - wortWeight);

  if(DEBUG_TIMINGS) Serial.print(F("Output finished: ")); Serial.println(millis() - bootMillis);

  Serial.println(F("Finished waking"));
  sleep();
}

void sleep() {
  stopSensors();
  Serial.print(F("Going to sleep for ")); Serial.print(delaySeconds); Serial.println(F(" seconds"));
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
