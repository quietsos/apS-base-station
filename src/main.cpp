#include <SPI.h>
#include <LoRa.h>
#include "gpio.h"
#include "loraCom.h"
#include "mqtt.h"
#include "ntp.h"
#include "wdt.h"




void setup() {
  Serial.begin(115200);
  delay(1000);
   // Initialize the watchdog with the desired timeout
  initWatchdog(watchdogTimeout);

  loraInit();        // Initialize LoRa
  mqtt_init();       // Initialize MQTT
  mqtt_connect();    // Connect to MQTT broker
  setupNTP();        // Initialize NTP

  
}



void loop() {

  // Check if MQTT client is connected, if not, reconnect
  if (!client.connected()) {
    mqtt_connect();
  }
  
  mqtt_loop();  // Maintain MQTT connection

  receivedData();  // read LoRa data, process, and publish to MQTT

  // Kick the watchdog periodically to prevent reset
  feedWatchdog();

}



