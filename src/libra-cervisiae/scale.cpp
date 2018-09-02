
#include <Arduino.h>
#include <HX711.h>
#include <pgmspace.h>
#include <DallasTemperature.h>
#include "libra-cervisiae.h"
#include "sensors.h"
#include "temperature.h"
#include "config.h"
#include "scale.h"

HX711 scale;

long averageStart = 0;
long averageLength = 0;
int averageSteps = 0;

long tempTare = 0;

double calibrationMass = 1;
double calibrationReading = 0;

void initScale() {
  if(DEBUG_HX711) {
    Serial.println("Scale init starting");
  }
  
  scale.begin(HX711_DATA_PIN, HX711_CLOCK_PIN);

  if(DEBUG_HX711) {
    Serial.println("Scale begun");
  }
  
  scale.set_offset(tareOffset);

  if(scaleFactor == 0) scaleFactor = 1;
  
  scale.set_scale(scaleFactor);
}

void scaleStart() {
  //HX711
  scale.power_up();
}

void scaleStop() {
  scale.power_down();
}


// returns entirely uncalibrated value
void readRaw(long* weight) {
  *weight = scale.read();
}

void averageRawReading(long* total, int count) {
  int t = 0;
  for(int i = 0; i < count; i++) {
    readRaw(total);
    t += *total;

    // 10Hz
    delay(100);
  }

  *total = (t / count);
}

// returns tared but uncalibrated value
void readWeight(long* weight) {
  *weight = scale.get_value();
}

void averageWeight(long* total, int count) {
  int t = 0;
  for(int i = 0; i < count; i++) {
    readWeight(total);
    t += *total;

    // 10Hz
    delay(100);
  }

  *total = (t / count);
}

void readCalibratedWeight(double* weight) {
  *weight = scale.get_units();
}

void averageCalibratedWeight(double* total, int count) {
  double t = 0;
  for(int i = 0; i < count; i++) {
    readCalibratedWeight(total);
    t += *total;

    // 10Hz
    delay(100);
  }

  *total = (t / count);
}

// Correct load cells for temperature effects.
// Note that the correction is the inverse of the temperature difference,
// because I always forget and flip a term around.
void temperatureCorrectCalibrated(double temperature, double *weight) {
  double correction = (tempCompensationBase - temperature) * tempCompensationFactor / scaleFactor;
  *weight += correction;
}

void tareScale(int tareMillis) {
  Serial.println(F("Starting tare"));
  averageStart = millis();
  averageLength = tareMillis;
  averageSteps = 0;

  if(DEBUG_TIMINGS) Serial.print(F("Tare start: ")); Serial.println(averageStart);
  if(DEBUG_TIMINGS) Serial.print(F("Tare length: ")); Serial.println(averageLength);

  tempTare = 0;
  
  tareInProgress = true;
}

void tareLoop() {
  long weight = 0;
  readRaw(&weight);

  double runningTotal = tempTare * averageSteps;
  runningTotal += weight;
  averageSteps++;
  tempTare = runningTotal / averageSteps;

  if(millis() > (averageStart + averageLength)) {
    Serial.print(F("Calculated tare value: ")); Serial.println(tempTare);

    tareOffset = tempTare;
    
    scale.set_offset((long) tareOffset);
    tareInProgress = false;

    stopSensors();
    
    saveConfig();
    return;
  }
  else if(DEBUG_HX711) {
    Serial.print(F("Tare step ")); Serial.println(averageSteps);
    Serial.print(F("Current offset ")); Serial.println(tempTare);
    Serial.print(F("Current weight ")); Serial.println(weight);
    Serial.println();
  }

  delay(100);
}

void calibrateScale(double knownGrams, int calibrateMillis) {
  Serial.println(F("Starting calibration"));
  averageStart = millis();
  averageLength = calibrateMillis;
  averageSteps = 0;
  
  calibrationMass = knownGrams;

  if(DEBUG_TIMINGS) Serial.print(F("Calibration start: ")); Serial.println(averageStart);
  if(DEBUG_TIMINGS) Serial.print(F("Calibration length: ")); Serial.println(averageLength);

  calibrationInProgress = true;
}


void calibrateLoop() {
  long weight = 0;
  readWeight(&weight);

  double runningTotal = calibrationReading * averageSteps;
  runningTotal += weight;
  averageSteps++;
  calibrationReading = runningTotal / averageSteps;

  if(millis() > (averageStart + averageLength)) {
    scaleFactor = calibrationReading / calibrationMass;
    Serial.print(F("Calculated calibration value: ")); Serial.println(scaleFactor);

    double temperature = 0;
    readBoardTemp(&temperature);
    if(temperature != DEVICE_DISCONNECTED_F) {
      tempCompensationBase = temperature;
    }
    
    scale.set_scale(scaleFactor);
    calibrationInProgress = false;

    stopSensors();

    saveConfig();
    return;
  }
  else if(DEBUG_HX711) {
    Serial.print(F("Calibrate step ")); Serial.println(averageSteps);
  }

  delay(100);
}
