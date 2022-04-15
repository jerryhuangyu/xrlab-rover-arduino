#include "encoder.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Encoder_Init();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(",輪1:"); Serial.print(ENCODER_1.count);
  Serial.print(",輪2:"); Serial.print(ENCODER_2.count);
  Serial.print(",輪3:"); Serial.print(ENCODER_3.count);
  Serial.print(",輪4:"); Serial.print(ENCODER_4.count);
  Serial.println();
  delay(100);
}
