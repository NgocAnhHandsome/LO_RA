#include <Arduino.h>
#include "simA76xx.h"

int cnt = 0;

void setup() {
  // put your setup code here, to run once:
  Sim_A76xx_config();
}

void loop() {
//  put your main code here, to run repeatedly:
  Sim_A76xx_pub("ngocanh", "Hello" + String(cnt));
  delay(1000);
  cnt ++;
}
