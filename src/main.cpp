#include <SPI.h>
#include <LoRa.h>
#include "gpio.h"
#include "loraCom.h"




void setup() {
  Serial.begin(115200);
  delay(1000);

  loraInit();
}



void loop() {
  receivedData();
  
}



