#include "wdt.h"

// Initialize the watchdog timer with a specific timeout (in seconds)
void initWatchdog(int timeout) {
  // Initialize the watchdog timer with the specified timeout
  esp_task_wdt_init(timeout, true);  // Timeout in seconds, panic_on_fail = true
  esp_task_wdt_add(NULL);  // Add current task to the watchdog timer
  Serial.print("Watchdog initialized with timeout: ");
  Serial.println(timeout);
}

// Feed (reset) the watchdog timer to prevent a system reset
void feedWatchdog() {
  // Reset the watchdog timer
  esp_task_wdt_reset();
//   Serial.println("Watchdog fed.");
}

