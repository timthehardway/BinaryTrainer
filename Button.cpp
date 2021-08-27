# include "../include/Button.h"
# include <Arduino.h>

//
// Button class
//

Button::Button()
{
  // Default values are set in init() function, this is more reliable with Arduino.
}

void Button::init(byte pin) 
{
  this->pin = pin;
  lastReading = HIGH; // using INPUT_PULLUP so HIGH equals not pressed.
  state = 0;
  lastDebounceTime = 0;
  debounceDelay = 50;
  pinMode(pin, INPUT_PULLUP);
  update();
}

void Button::update() 
{
  byte newReading = digitalRead(pin);

  if (newReading != lastReading) {
    lastDebounceTime = millis();
  }    

  if (millis() - lastDebounceTime > debounceDelay) {
    state = newReading;
  }

  lastReading = newReading;
}

byte Button::getState()
{
  update();
  return state;
}

bool Button::isPressed() 
{
  return (getState() == LOW);
}

//
// LatchButton class
//

LatchButton::LatchButton() 
{
  // Default values are set in init() function, this is more reliable with Arduino.
}

void LatchButton::init(byte pin) {
  this->pin = pin;
  state = 0;
  lastReading = LOW; // Using an external pull-down resistor so LOW equals not pressed.
  lastState = LOW;
  isPressed = 0;
  isReleased = 0;
  lastDebounceTime = 0;
  debounceDelay = 50;
  pinMode(pin, INPUT);
  update();
}

void LatchButton::update() {
  byte reading = digitalRead(pin);

  // Filter out debounce readings.

  // 1. Update lastDebounceTime when a change in state is detected.
  if (reading != lastReading)
  {
    lastDebounceTime = millis();
  }

  // 2. If more than 50ms. passed since last state change, set state to reading.
  if (millis() - lastDebounceTime > debounceDelay)
  {
    state = reading;
  }

  set_bools();

  lastReading = reading;
  lastState = state;
}

void LatchButton::set_bools() {
  if (state == 1 && lastState == 0) {
    // button state changed from released to pressed.
    isPressed = 1;
  } else if (state == 0 && lastState == 1) {
    // button state changed from pressed to released.
    isReleased = 1;
  }
}

bool LatchButton::is_pressed() {
  update();
  if (isPressed) {
    isPressed = !isPressed;
    return 1;
  }
  else {
    return 0;
  }
}

bool LatchButton::is_released() {
  if (isReleased) {
    isReleased = !isReleased;
    return 1;
  } else {
    return 0;
  }
}
