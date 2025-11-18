#include "ntp.h"

// NTP server and UTC offset
const char* ntpServer = "pool.ntp.org";      // Default NTP server
const long utcOffsetInSeconds = 6 * 3600;    // UTC offset for Bangladesh (6 hours in seconds)

// NTP client object
WiFiUDP udp;
NTPClient timeClient(udp, ntpServer, utcOffsetInSeconds);

void setupNTP() {
  // Start the NTP client
  timeClient.begin();

  // Wait for the time to synchronize
  Serial.println("Waiting for NTP synchronization...");
  while (!timeClient.update()) {
    timeClient.forceUpdate();  // Force an update if no time is available
    delay(1000);  // Wait for 1 second before retrying
  }
  Serial.println("NTP synchronized.");
}

unsigned long getEpochTime() {
  // Update time from NTP server
  timeClient.update();

  // Return the current time in epoch format (seconds since Jan 1, 1970)
  return timeClient.getEpochTime();
}
