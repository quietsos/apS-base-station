#ifndef MQTT_H
#define MQTT_H

#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// WiFi credentials
extern const char* ssid;
extern const char* password;

// MQTT Broker Settings
extern const char* mqtt_server;
extern const int mqtt_port;
extern const char* mqtt_user;
extern const char* mqtt_pass;
extern const char* mqtt_topic;

// MQTT Client
extern WiFiClient espClient;
extern PubSubClient client;

// Function Prototypes
void mqtt_init();
void mqtt_connect();
void mqtt_publish(String payload);
void mqtt_loop();
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void setup_wifi();

#endif  // MQTT_H
