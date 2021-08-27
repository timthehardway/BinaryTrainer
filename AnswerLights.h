/*
  Class containing answer lights for the binary counter.
  Created 14-06-2021 by Tim Ruterink.
  For study purposes.

  Dependencies: Led.h
*/

#ifndef ANSWERLIGHTS_H
#define ANSWERLIGHTS_H

#include <Arduino.h>

class AnswerLights
{
  private:
    byte _pinGreenLed;
    byte _pinRedLed;
    byte _greenState;
    byte _redState;
    unsigned long timeStamp;

    void updateTimestamp();

  public:
    AnswerLights();
    void init(byte pinGreenLed, byte pinRedLed);
    void loop();
    void rightAnswer();
    void wrongAnswer();
    void off();
};

#endif