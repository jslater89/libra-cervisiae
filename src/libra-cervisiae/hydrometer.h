#ifndef HYDROMETER_H
#define HYDROMETER_H

void hydrometerSetup();
void hydrometerLoop();
void sleep();
double getBatchABW(double currentNoEquipmentMass);
double getAlcoholMass(double weightDelta);
double getYeastMass(double weightDelta);
double getCO2Mass(double weightDelta);
double getABW(double alcoholMass, double beerMass);
double calculateABV(double abw);
double calculateGravity(double originalGravity, double abv);

#endif
