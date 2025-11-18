#ifndef NTP_H
#define NTP_H

#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// NTP setup constants
extern const char* ntpServer;              // NTP Server (e.g., "pool.ntp.org")
extern const long utcOffsetInSeconds;      // Time zone offset (e.g., 3600 for UTC+1)

// NTP client object
extern WiFiUDP udp;
extern NTPClient timeClient;

// Function declarations
void setupNTP();
unsigned long getEpochTime();

#endif  // NTP_H
