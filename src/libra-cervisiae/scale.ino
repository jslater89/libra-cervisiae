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

double tareValue = 0;
int tareSteps = 0;

void scaleSetup() {
  //HX711
  scale.begin(HX711_DATA_PIN, HX711_CLOCK_PIN);   
  scale.power_up();

  // time to stabilize
  delay(500);
}

void scaleShutdown() {
  scale.power_down();
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
  *weight = scale.read();
}

void averageCalibratedWeight(double* total, int count) {
  int t = 0;
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

void tare(int tareMillis) {
  Serial.println("Starting tare");
  scaleSetup();
  tempSetup();
  tareStart = millis();
  tareLength = tareMillis;

  if(DEBUG_TIMINGS) Serial.print("Tare start: "); Serial.println(tareStart);
  if(DEBUG_TIMINGS) Serial.print("Tare length: "); Serial.println(tareLength);

  tareSteps = 0;
  tareValue = 0;
  
  tareInProgress = true;
}

void tareLoop() {
  int weight = 0;
  readWeight(&weight);

  double runningTotal = tareValue * tareSteps;
  runningTotal += weight;
  tareSteps++;
  tareValue = runningTotal / tareSteps;

  if(millis() > (tareStart + tareLength)) {
    Serial.print("Calculated tare value: "); Serial.println(tareValue);
    
    scale.set_offset((long) tareValue);

    // TODO:remove, debugging
    scale.set_scale(215.23);
    
    tareInProgress = false;
    return;
  }
  else {
    //Serial.print("Tare step "); Serial.println(tareSteps);
  }

  delay(100);
}

