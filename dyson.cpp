#include <Arduino.h>
#include "dyson.h"

DysonRemote::DysonRemote(int IRPin)
{
  IR_pin = IRPin;
  pinMode(IR_pin, OUTPUT);
}

void DysonRemote::power()
{
  int code = getCode();

  for (int i = 0; i < 5; i++) {
    header();

    if (1 == code) {
      phase(1540, 760);
      pause(1);
      phase(5324, 2200);
      pause(1);
      phase(1560, 760);
      pause(2);
      phase(1540, 740);
      pause(9);
      phase(1540, 740);
      pause(1);
    } else {
      pause(2);
      phase(6064, 2200);
      pause(1);
      phase(1560, 740);
      pause(2);
      phase(1560, 760);
      pause(11);
    }
  
    digitalWrite(IR_pin, LOW);
    delay(40);
  }
}

void DysonRemote::header()
{
  phase(0, 2200);
  pause(1);
  phase(1580, 740);
  pause(2);
  phase(1540, 760);
  pause(9);
}

void DysonRemote::phase(int lowTime, int highTime)
{
  digitalWrite(IR_pin, LOW);
  delayMicroseconds(lowTime);

  digitalWrite(IR_pin, HIGH);
  delayMicroseconds(highTime);
}

void DysonRemote::pause(int repeat)
{
  for (int i = 0; i < repeat; i++) {
    phase(800, 740);
  }
}

// The remote use 3 codes for each button
// You cannot use a same code twice
int DysonRemote::getCode()
{
  if (lastCodeUsed == 2) {
    return lastCodeUsed = 1;
  }

  return lastCodeUsed = 2;
}
