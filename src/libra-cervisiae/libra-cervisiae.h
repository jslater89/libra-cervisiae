#ifndef LIBRA_CERVISIAE_H
#define LIBRA_CERVISIAE_H

// Debug options
#define DEBUG_TIMINGS false
#define DEBUG_DS18XXX false
#define DEBUG_HX711 false
#define LOG_REQUESTS false

// Build types
#define WEMOS false
#define PCB true
#define NODEMCU false

#if WEMOS
#define DS18B20_POWER_PIN 12
#define DS18B20_DATA_PIN 13
#define HX711_DATA_PIN 5
#define HX711_CLOCK_PIN 4

#elif PCB
#define DS18B20_POWER_PIN 14
#define DS18B20_DATA_PIN 12
#define HX711_DATA_PIN 4
#define HX711_CLOCK_PIN 5

#elif NODEMCU
#define DS18B20_POWER_PIN 12
#define DS18B20_DATA_PIN 13
#define HX711_DATA_PIN 5
#define HX711_CLOCK_PIN 4

#else // Fill in your pin numbers here
#define DS18B20_POWER_PIN 12
#define DS18B20_DATA_PIN 13
#define HX711_DATA_PIN 5
#define HX711_CLOCK_PIN 4
#endif

extern long bootMillis;

// Tare in progress
extern bool tareInProgress;

// Calibration in progress
extern bool calibrationInProgress;

#endif
