#include <SPI.h>
#include <LoRa.h>

// -------------------- LoRa Pin Configuration --------------------
#define LORA_SS     10
#define LORA_RST    9
#define LORA_DIO0   2
// ----------------------------------------------------------------

#define LORA_FREQ           434E6
#define LORA_BANDWIDTH      500E3
#define LORA_SPREADING      9
#define LORA_CODING_RATE    5

void setup() {
  Serial.begin(115200);
  delay(1000);

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

void loop() {
  int packetSize = LoRa.parsePacket();

  if (packetSize) {
    Serial.println("📩 Packet Received:");

    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }
    Serial.println();

    Serial.print("RSSI: ");
    Serial.println(LoRa.packetRssi());

    Serial.print("SNR : ");
    Serial.println(LoRa.packetSnr());

    Serial.println("-----------------------------------\n");
  }
}
