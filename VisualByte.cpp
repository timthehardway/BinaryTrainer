#include <Arduino.h>
#include "../include/VisualByte.h"

VisualByte::VisualByte()
{
  // Default values are set in init() function, this is more reliable with Arduino.
}

void VisualByte::init(byte dataPin, byte clockPin, byte latchPin)
{
  _dataPin = dataPin;
  _clockPin = clockPin;
  _latchPin = latchPin;
  pinMode(_dataPin, OUTPUT);
  pinMode(_clockPin, OUTPUT);
  pinMode(_latchPin, OUTPUT);
  currentByte = 0b00000000;
  state = 0;
}

void VisualByte::loop()
{
  if (state == 0)
  // check state, so each pattern is written once instead of every loop.
  {
    digitalWrite(_latchPin, LOW);
    shiftOut(_dataPin, _clockPin, LSBFIRST, currentByte);
    digitalWrite(_latchPin, HIGH);

    state = 1;
  }
}

void VisualByte::show(byte input, int milliseconds)
// show one byte value for a specified time, blocking other actions with a delay.
{
  digitalWrite(_latchPin, LOW);
  shiftOut(_dataPin, _clockPin, LSBFIRST, input);
  digitalWrite(_latchPin, HIGH);
  delay(milliseconds);

  clear();
}

void VisualByte::setByte(byte newByte)
{
  currentByte = newByte;
}

void VisualByte::testProgram()
// This program tests each led separately. Delays are used on
// purpose to temporarily block all other actions.
{
  byte testByte = 1;
  for(int i = 0; i < 8; i++)
  {
    digitalWrite(_latchPin, LOW);
    shiftOut(_dataPin, _clockPin, LSBFIRST, testByte);
    digitalWrite(_latchPin, HIGH);
    testByte *= 2;
    delay(500);
  }
  clear();
  delay(500);
}

void VisualByte::clear()
{
  digitalWrite(_latchPin, LOW);
  shiftOut(_dataPin, _clockPin, LSBFIRST, 0x00);
  digitalWrite(_latchPin, HIGH);

  state = 0;
}