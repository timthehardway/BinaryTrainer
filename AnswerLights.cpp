#include <Arduino.h>
#include "../include/AnswerLights.h"

AnswerLights::AnswerLights()
{
  // initialisation is done in init() method.
}

void AnswerLights::init(byte pinGreenLed, byte pinLedRed)
{
  _pinGreenLed = pinGreenLed;
  _pinRedLed = pinLedRed;
  pinMode(_pinGreenLed, OUTPUT);
  pinMode(_pinRedLed, OUTPUT);
  _greenState = 0;
  _redState = 0;
  timeStamp = 0;
  off();
}

void AnswerLights::loop()
{
  digitalWrite(_pinRedLed, _redState);
  digitalWrite(_pinGreenLed, _greenState);

  if (millis() - timeStamp > 2000)
  // after 2 seconds, turn leds off.
  {
    off();
  }
  
}

void AnswerLights::updateTimestamp()
{
  timeStamp = millis();
}

void AnswerLights::rightAnswer()
{
  _greenState = 1;
  _redState = 0;
  updateTimestamp();
}

void AnswerLights::wrongAnswer()
{
  _greenState = 0;
  _redState = 1;
  updateTimestamp();
}

void AnswerLights::off()
{
  _greenState = 0;
  _redState = 0;
}