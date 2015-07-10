#include <Arduino.h>
#include <RTClib.h>

#include "time.h"

Time::Time(int hour, int minute) : hour(hour), minute(minute)
{
}

bool Time::isTime(DateTime datetime)
{
  return true;
  if (hour != datetime.hour()) {
    return false;
  } else if (minute != datetime.minute()) {
    return false;
  }

  return true;
}
