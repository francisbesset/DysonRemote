#include <Wire.h>
#include <L3G4200D.h>
#include <RTClib.h>

#include "dyson.h"
#include "time.h"


#define DEBUG

// PIN with IR LED
#define IR_LED_PIN 3

// Set the hour to start the Dyson
#define START_HOUR 6  // 6 AM
//#define START_HOUR 20 // 8 PM

// Set the minute to start the Dyson
#define START_MINUTE 0

// Set the time to wait for each loop to check if the Dyson has started
#define TIME_FOR_LOOP 10 * 1000 // 10 secondes

// Set max loop number to check if the Dyson has started
#define MAX_LOOP 5


L3G4200D gyro;
RTC_DS1307 rtc;

void debug(String message) {
  #ifdef DEBUG
    Serial.println(message);
  #endif
}


void setup() {
  Serial.begin(9600);

  // Initialize L3G4200D
  while(!gyro.begin()) {
    Serial.println("Could not find L3G4200D, check wiring!");
    Serial.println("The L3G4200D, is needed to check temp.");
    Serial.println("You can use an other trick to detect if the Dyson started.");

    delay(500);
  }

  Wire.begin();
  while(!rtc.isrunning()) {
    Serial.println("Could not find a valid DS1307 RTC, check wiring!");

    delay(500);
  }

  // Set current DateTime on DS1307
  //rtc.adjust(DateTime(__DATE__, __TIME__));
}


DysonRemote remote (IR_LED_PIN);
Time time (START_HOUR, START_MINUTE);

bool dysonStarted = false, timeReached = false;
int initialTemp = -1, targetTemp = -1, currentTemp;
int nbLoop = 0;

void loop() {
  // Step 1: Check time
  if (false == timeReached) {
    DateTime now = rtc.now();
    debug(String("Current time: ") + now.hour() + ":" + now.minute());

    if (true == time.isTime(now)) {
      debug("Time reached!");
      timeReached = true;
    } else {
      delay(1000);

      return;
    }
  }

  // Step 2: Start Dyson
  if (false == dysonStarted) {
    debug("Send power signal");
    remote.power();
    dysonStarted = true;

    if (targetTemp != -1) {
        debug("Wait...");
        delay(TIME_FOR_LOOP); // wait
    }

    return;
  }

  // Step 3: Check temp
  if (-1 == initialTemp) {
    // read the current temp
    initialTemp = gyro.readTemperature();
    debug(String("Initial temp: ") + initialTemp);

    // target temp needed to detect if the dyson has been started
    targetTemp = initialTemp - 4;
    debug(String("Target temp: ") + targetTemp);

    debug("Wait...");
    delay(TIME_FOR_LOOP); // wait
  } else {
    nbLoop++;
    debug(String("Current loop: ") + nbLoop);

    currentTemp = gyro.readTemperature();
    debug(String("Current temp: ") + currentTemp);

    if (targetTemp < currentTemp) {
      if (MAX_LOOP == nbLoop) {
        // reset to start the Dyson
        nbLoop = 0;
        dysonStarted = false;
      } else {
        debug("Wait...");
        delay(TIME_FOR_LOOP); // wait
      }
    } else {
      debug("Finished!");
      delay(10000);
    }
  }
}
