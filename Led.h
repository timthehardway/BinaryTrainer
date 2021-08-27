/*
  Led.h - Library containing basic led functionality.
  Created 04-06-2021 by Tim Ruterink.
  For study purposes.
*/

#ifndef LED_H
#define LED_H

#include <Arduino.h>

class Led
{
  private:
    byte pin;
    byte state;

  public:
    Led();
    void init(byte pin);
    void on();
    void off();
    void flip();
    byte getState();
};

#endif