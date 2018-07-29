#ifdef WEMOS
#define HX711_POWER_PIN 14
#define HX711_DATA_PIN 5
#define HX711_CLOCK_PIN 4

#elif defined PCB
#define HX711_POWER_PIN 14
#define HX711_DATA_PIN 5
#define HX711_CLOCK_PIN 4

#elif defined NODEMCU
#define HX711_POWER_PIN 14
#define HX711_DATA_PIN 5
#define HX711_CLOCK_PIN 4

#endif

HX711 scale;
long tareStart = 0;
long tareLength = 0;

int tareSteps = 0;

void initScale() {
  scale.begin(HX711_DATA_PIN, HX711_CLOCK_PIN);   
  scale.set_offset(tareOffset);
  scale.set_scale(scaleFactor);
}

void scaleSetup() {
  //HX711
  scale.power_up();

  // time to stabilize
  delay(500);
}

void scaleShutdown() {
  scale.power_down();
}

void averageRawReading(int* total, int count) {
  int t = 0;
  for(int i = 0; i < count; i++) {
    readRaw(total);
    t += *total;

    // 10Hz
    delay(100);
  }

  *total = (t / count);
}

// returns uncalibrated value
void readRaw(int* weight) {
  *weight = scale.read();
}


void averageWeight(int* total, int count) {
  int t = 0;
  for(int i = 0; i < count; i++) {
    readWeight(total);
    t += *total;

    // 10Hz
    delay(100);
  }

  *total = (t / count);
}

// returns uncalibrated value
void readWeight(int* weight) {
  *weight = scale.get_value();
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

void readCalibratedWeight(double* weight) {
  *weight = scale.get_units();
}

void tareScale(int tareMillis) {
  Serial.println("Starting tare");
  tareStart = millis();
  tareLength = tareMillis;

  if(DEBUG_TIMINGS) Serial.print("Tare start: "); Serial.println(tareStart);
  if(DEBUG_TIMINGS) Serial.print("Tare length: "); Serial.println(tareLength);

  tareSteps = 0;
  tareOffset = 0;
  
  tareInProgress = true;
}

void tareLoop() {
  int weight = 0;
  readRaw(&weight);

  double runningTotal = tareOffset * tareSteps;
  runningTotal += weight;
  tareSteps++;
  tareOffset = runningTotal / tareSteps;

  if(millis() > (tareStart + tareLength)) {
    Serial.print("Calculated tare value: "); Serial.println(tareOffset);
    
    scale.set_offset((long) tareOffset);
    tareInProgress = false;

    tempShutdown();
    scaleShutdown();

    saveConfig();
    return;
  }
  else {
    //Serial.print("Tare step "); Serial.println(tareSteps);
  }

  delay(100);
}

void calibrateScale(double knownGrams) {
  int weight;
  averageWeight(&weight, 10);

  double dWeight = weight;
  scaleFactor = dWeight / knownGrams;

  scale.set_scale(scaleFactor);
}

