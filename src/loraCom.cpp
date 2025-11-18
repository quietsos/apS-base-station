#include "loraCom.h"
#include "mqtt.h"

void loraInit() {
    
  Serial.println("\n=== LoRa Receiver (STM32 Compatible) ===\n");

  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  if (!LoRa.begin(LORA_FREQ)) {
    Serial.println("LoRa init failed!");
    while (1);
  }

  LoRa.setSignalBandwidth(LORA_BANDWIDTH);   // 500 kHz
  LoRa.setSpreadingFactor(LORA_SPREADING);   // SF9
  LoRa.setCodingRate4(LORA_CODING_RATE);     // 4/5

  // FIXED → IQ inversion disabled (matches STM32)
  LoRa.disableInvertIQ();

  Serial.println("Receiver Ready.\n");
}




void receivedData() {
  int packetSize = LoRa.parsePacket();

  if (packetSize) {
    Serial.println("Packet Received:");

    String receivedMessage = "";  // To store the received LoRa data
    // Get current time in epoch format
    unsigned long epochTime = getEpochTime();
    Serial.print("Current time (epoch): ");
    Serial.println(epochTime);

    // Read the available data from the LoRa packet
    while (LoRa.available()) {
      receivedMessage += (char)LoRa.read();
    }
    Serial.println("Received LoRa message: ");
    Serial.println(receivedMessage);  // Print the received message

    // Create a StaticJsonDocument to hold and manipulate the received message
    StaticJsonDocument<1024> doc;  // Adjust size as per the expected message size
    DeserializationError error = deserializeJson(doc, receivedMessage);

    if (error) {
      Serial.print("JSON Deserialization failed: ");
      Serial.println(error.f_str());
      return;  // If deserialization fails, exit the function
    }

    // Add the extra field `base:1234` directly to the JSON document
    doc["time"] = epochTime;

    // Print the deserialized JSON (for debugging)
    Serial.println("Deserialized and Updated JSON:");
    serializeJsonPretty(doc, Serial);  // This will print the updated JSON with base:1234
    Serial.println();

    // Serialize the updated JSON object back to a string (payload)
    String payload;
    serializeJson(doc, payload);  // Convert the JSON document back to a string

    // Publish the data to the MQTT broker with QoS 1
    mqtt_publish(payload);  // Ensure you have a function to publish to MQTT with QoS 1

    // Print RSSI and SNR values (for debugging)
    Serial.print("RSSI: ");
    Serial.println(LoRa.packetRssi());

    Serial.print("SNR: ");
    Serial.println(LoRa.packetSnr());

    Serial.println("-----------------------------------\n");
  }
}

