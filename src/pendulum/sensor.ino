
void sensorSetup() {
  pinMode(14, OUTPUT);
  digitalWrite(14, HIGH);

  delay(20);
  
  Wire.begin(4,5);
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  int error = Wire.endTransmission(true);

  if(error > 0) {
    Serial.print("I2C communication to accelerometer failed! ");
    Serial.print(error);
    Serial.println();
  }
  else {
    Serial.println("Accelerometer active");
  }
}

void sensorShutdown() {
  digitalWrite(14, LOW);
}

double readVoltage() {
  pinMode(A0, INPUT);
  int raw = analogRead(A0);
  double voltage = raw/1023.0;
  voltage = voltage*4.2;

  return voltage;
}

void averageAccel(int* x, int* y, int* z, int count, int delayTime) {
  int totalX, totalY, totalZ;
  totalX = totalY = totalZ = 0;
  for(int i = 0; i < count; i++) {
    readAccel(x, y, z);
    totalX += *x;
    totalY += *y;
    totalZ += *z;

    delay(delayTime);
  }

  *x = (totalX / count);
  *y = (totalY / count);
  *z= (totalZ / count);
}

// returns raw accelerometer values
void readAccel(int* x, int* y, int* z) {
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDRESS,6,true);  // request a total of 14 registers
  int16_t acX = Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  int16_t acY = Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  int16_t acZ = Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

  *x = acX;
  *y = acY;
  *z = acZ;
}

void averageTemp(double* t, int count, int delayTime) {
  double totalTemp;
  for(int i = 0; i < count; i++) {
    readTemp(t);
    totalTemp += *t;
    delay(delayTime);
  }

  *t = (totalTemp / count);
}

// returns Fahrenheit temperature
void readTemp(double* t) {
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(0x41);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDRESS,2,true);  // request a total of 14 registers
  int16_t rawT = Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  
  *t = (9 * rawT / 1700.00 + 97.754); // from datasheet, converted to degrees F
}

