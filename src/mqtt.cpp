#include "mqtt.h"

// WiFi credentials
const char* ssid = "APS_OFFICE";
const char* password = "WelcomeTo@APS#22";

// MQTT Broker Settings
const char* mqtt_server = "152.42.179.228";  // Replace with your MQTT broker address
const int mqtt_port = 1885;                    // MQTT port (1883 for non-secure connection)
const char* mqtt_user = "apsIoT";            // MQTT username
const char* mqtt_pass = "apsIoT25";            // MQTT password
const char* mqtt_topic = "apS/Basestation/Data";           // Topic for publishing data

// WiFi and MQTT Client
WiFiClient espClient;
PubSubClient client(espClient);

void mqtt_init() {
  // Set the MQTT server and callback
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqtt_callback);

  // Connect to WiFi
  setup_wifi();
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void mqtt_connect() {
  // Loop until we're connected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("LoRaClient", mqtt_user, mqtt_pass)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}




void mqtt_publish(String payload) {
  if (client.publish(mqtt_topic, payload.c_str())) {
    Serial.println("Data published to MQTT broker");
  } else {
    Serial.println("Failed to publish data");
  }
}

void mqtt_loop() {
  // Call this in the main loop to maintain the MQTT connection and check for incoming messages
  client.loop();
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  // Handle incoming messages from the broker (optional)
  Serial.print("Message received on topic: ");
  Serial.println(topic);
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
