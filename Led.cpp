#include <Arduino.h>
#include "../include/Led.h"

Led::Led()
{
  // Default values are set in init() function, this is more reliable with Arduino.
}

void Led::init(byte pin)
{
  this->pin = pin;
  state = 0;
  pinMode(pin, OUTPUT);
  off();
}

void Led::on()
{
  digitalWrite(pin, HIGH);
  state = 1;
}

void Led::off()
{
  digitalWrite(pin, LOW);
  state = 0;
}


void Led::flip()
{
  state = !state;
  digitalWrite(pin, state);
}

byte Led::getState()
{
  return state;
}