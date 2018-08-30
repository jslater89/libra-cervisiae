#ifndef SCALE_H
#define SCALE_H

void initScale();
void scaleStart();
void scaleStop();
void averageRawReading(int* total, int count);
void averageWeight(int* total, int count);
void readWeight(int* weight);
void averageCalibratedWeight(double* total, int count);
void readCalibratedWeight(double* weight);
void tareScale(int tareMillis);
void tareLoop();
void calibrateScale(double knownGrams, int calibrateMillis);
void calibrateLoop();
void temperatureCorrectCalibrated(double temperature, double *weight);

#endif
