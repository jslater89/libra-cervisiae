
// one-time sensor init
void initSensors() {
  initScale();
  initTemp();
}

// start sensors after shutdown
void startSensors() {
  sensorsPreDelay();
  delay(500);
  sensorsPostDelay();  
}

void sensorsPreDelay() {
  scaleStart();
}

void sensorsPostDelay() {
  tempStart();
}

// shutdown sensors after startup
void stopSensors() {
  scaleStop();
}

