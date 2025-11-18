#include <SPI.h>
#include <LoRa.h>
#include "gpio.h"
#include "loraCom.h"
#include "mqtt.h"
#include "ntp.h"




void setup() {
  Serial.begin(115200);
  delay(1000);

  loraInit();
   // Initialize MQTT
  mqtt_init();
  mqtt_connect();
  setupNTP();  // Initialize NTP
  
  
}



void loop() {

  // Check if MQTT client is connected, if not, reconnect
  if (!client.connected()) {
    mqtt_connect();
  }
  
  mqtt_loop();  // Maintain MQTT connection

  receivedData();

}



