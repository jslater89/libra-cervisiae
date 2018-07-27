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

// returns raw accelerometer values
void readWeight(int* weight) {
  *weight = scale.read();
}

void tare(int tareMillis) {
  long tareStart = millis();
  long tareLength = tareMillis();

  tareSteps = 0;
  tareValue = 0;
  
  tareInProgress = true;
}

void tareLoop() {
  int weight = 0;
  readWeight(weight);

  double runningTotal = tareValue * tareSteps;
  runningTotal += weight;
  tareSteps++;
  tareValue = runningTotal / tareSteps;

  if(millis() > (tareStart + tareLength)) {
    Serial.print("Calculated tare value: "); Serial.println(tareValue);
    
    scale.set_offset((long) tareValue);
    tareInProgress = false;
    return;
  }

  delay(100);
}

