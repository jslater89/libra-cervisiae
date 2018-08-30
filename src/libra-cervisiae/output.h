#ifndef OUTPUT_H
#define OUTPUT_H

void handleOutput(double gravity, double abw, double abv, double temperature, double weight, double weightDelta);
void sendToGraviton(double gravity, double abw, double abv, double temperature, double weight, double weightDelta);
void sendToGoogleDrive(double gravity, double abw, double abv, double temperature, double weight, double weightDelta);

#endif
