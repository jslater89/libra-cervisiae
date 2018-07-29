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
long averageStart = 0;
long averageLength = 0;
int averageSteps = 0;

double calibrationMass = 1;
double calibrationReading = 0;

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
  averageStart = millis();
  averageLength = tareMillis;

  if(DEBUG_TIMINGS) Serial.print("Tare start: "); Serial.println(averageStart);
  if(DEBUG_TIMINGS) Serial.print("Tare length: "); Serial.println(averageLength);

  averageStart = 0;
  tareOffset = 0;
  
  tareInProgress = true;
}

void tareLoop() {
  int weight = 0;
  readRaw(&weight);

  double runningTotal = tareOffset * averageSteps;
  runningTotal += weight;
  averageSteps++;
  tareOffset = runningTotal / averageSteps;

  if(millis() > (averageStart + averageLength)) {
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

void calibrateScale(double knownGrams, int calibrateMillis) {
  Serial.println("Starting calibration");
  averageStart = millis();
  averageLength = calibrateMillis;
  
  calibrationMass = knownGrams;

  if(DEBUG_TIMINGS) Serial.print("Calibration start: "); Serial.println(averageStart);
  if(DEBUG_TIMINGS) Serial.print("Calibration length: "); Serial.println(averageLength);

  calibrationInProgress = true;
}


void calibrateLoop() {
  int weight = 0;
  readWeight(&weight);

  double runningTotal = calibrationReading * averageSteps;
  runningTotal += weight;
  averageSteps++;
  calibrationReading = runningTotal / averageSteps;

  if(millis() > (averageStart + averageLength)) {
    scaleFactor = calibrationReading / calibrationMass;
    Serial.print("Calculated calibration value: "); Serial.println(scaleFactor);

    double temperature = 0;
    readBoardTemp(&temperature);
    if(temperature != DEVICE_DISCONNECTED_F) {
      tempCompensationBase = temperature;
    }
    
    scale.set_scale(scaleFactor);
    calibrationInProgress = false;

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

