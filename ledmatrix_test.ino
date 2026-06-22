#include <MD_MAX72xx.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1

#define DATA_PIN 23
#define CLK_PIN 18
#define CS_PIN 5

MD_MAX72XX mx(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

void setup() {

  mx.begin();

  for(int i=0;i<8;i++){

    mx.setRow(i,255);

  }

  mx.update();
}

void loop(){}