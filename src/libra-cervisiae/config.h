#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <stdint.h>

void printConfig();
void getConfigJSON(char* buf, int lim);
bool saveConfig();
bool loadConfig();
bool decodeJSON(String json, bool decodeCoefficients);

/****** Configuration options *******/
// How long between readings in hydrometer mode?
extern int delaySeconds; // half an hour

// What is the name of this hydrometer? Also used
// as the SSID for hotspot mode.
extern char hydrometerName[51];

// What is fully-charged battery voltage for this hydrometer?
extern float fullVoltage;

// What wifi network should this hydrometer connect
// to in hydrometer mode?
extern char wifiNetwork[41];

// What password should it use?
extern char wifiPassword[41];

// API root, path, port
extern char apiRoot[101];
extern char apiPath[101];
extern int apiPort;

// API key for Graviton
extern char apiKey[51];

// Should this hydrometer boot into hotspot mode?
extern bool bootToHotspot;

// How should this hydrometer do output?
// 0: no output
// 1: Graviton output
// 2: Google Drive output
extern int outputMode;

// How should we adjust for the load cell's temperature response?
// rawOutput += (observed - base) * factor
// calibratedOutput += (observed - base) * factor / scaleFactor
// A negative compensation factor means that the scale reads higher
// at lower temperatures. A positive compensation factor means that
// the scale reads higher at higher temperatures.
extern double tempCompensationBase; // F
extern double tempCompensationFactor;

// The tare offset is the difference between the HX711 ADC
// output and 0.
extern double tareOffset;

// The scale factor is the divisor to apply to the HX711 ADC
// output to get the weight in grams.
extern double scaleFactor;

// The weight of the non-wort equipment going on the scale,
// in grams.
extern double equipmentWeight;

// The starting mass for the batch, not including equipment weight,
// in grams.
extern double startingWortMass;

// The starting gravity of the batch, in SG@68F.
extern double startingWortGravity;

// The list of DS18B20s connected; filled in at boot
extern uint8_t tempSensors[2][8];

// The DS18B20 address to use for load cell
// temperature compensation.
extern uint8_t boardTempAddr[8];

// The DS18B20 address to use for wort temperature
// reporting.
extern uint8_t wortTempAddr[8];
/****** End configuration *******/

#endif
