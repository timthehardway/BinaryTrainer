/*
  Buttons.h - Library containing switching and latching buttons.
  Created 28-05-2021 by Tim Ruterink.
  For study purposes.
*/

#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button // Built for use with INPUT_PULLUP resistor. 
{
  private:
    byte pin;
    byte state;
    byte lastReading;
    unsigned long lastDebounceTime;
    unsigned long debounceDelay;

    void update();

  public:
    Button();
    void init(byte pin);
    byte getState();
    bool isPressed();
};

class LatchButton // Built for use with pull-down resistor. 
{
  private:
    byte pin;
    byte state;
    byte lastReading;
    byte lastState;
    bool isPressed;
    bool isReleased;
    unsigned long lastDebounceTime;
    unsigned long debounceDelay;

    void update();
    void set_bools();

  public:
    LatchButton();
    void init(byte pin);
    bool is_pressed();
    bool is_released();
};

#endif