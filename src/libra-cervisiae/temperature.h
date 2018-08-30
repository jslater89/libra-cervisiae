#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <DallasTemperature.h>
#include <OneWire.h>

void printAddress(DeviceAddress deviceAddress);
void initTemp();
void tempStart();
void readWortTemp(double *t);
void readBoardTemp(double *t);
void readTempByAddress(DeviceAddress a, double* t);

#endif
