
#include <pgmspace.h>
#include "libra-cervisiae.h"
#include "sensors.h"
#include "temperature.h"
#include "scale.h"

// one-time sensor init
void initSensors() {
  initScale();

  if(DEBUG_TIMINGS) {
    Serial.print(F("Scale init done: ")); Serial.println(millis() - bootMillis);
  }
  
  initTemp();

  if(DEBUG_TIMINGS) {
    Serial.print(F("Temp init done: ")); Serial.println(millis() - bootMillis);
  }
}

void sensorsPreDelay() {
  scaleStart();
}

void sensorsPostDelay() {
  tempStart();
}

// start sensors after shutdown
void startSensors() {
  sensorsPreDelay();

  if(DEBUG_TIMINGS) {
    Serial.print(F("Sensors pre-delay: ")); Serial.println(millis() - bootMillis);
  }
  
  delay(500);

  sensorsPostDelay();

  if(DEBUG_TIMINGS) {
    Serial.print(F("Sensors post-delay: ")); Serial.println(millis() - bootMillis);
  }
}

// shutdown sensors after startup
void stopSensors() {
  scaleStop();
}
