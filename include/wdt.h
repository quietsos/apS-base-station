#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <Arduino.h>
#include "esp_task_wdt.h"  // Include for task watchdog functionality
#include "esp_system.h"    // Include for system functionality



// Watchdog timeout (in seconds)
const int watchdogTimeout = 600;  // Set watchdog timeout for 10 seconds

// Function declarations
void initWatchdog(int timeout);    // Initialize the watchdog with a timeout (in seconds)
void feedWatchdog();               // Feed (reset) the watchdog to prevent system reset

#endif  // WATCHDOG_H
