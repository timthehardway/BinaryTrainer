/*
  Display.h - Library containing functions for controlling a four
  digit segment led display with a SN74HC164 bit shift register.
  Created 04-06-2021 by Tim Ruterink.
  For study purposes.
*/

#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

class Display {
  private:
    byte _dataPin;
    byte _clockPin;
    byte _digitPin1;
    byte _digitPin2;
    byte _digitPin3;
    byte _digitPin4;

    const byte numOfDigits = 4;

    void updateCurrentValue(char array[], int arrayLength);

    char currentValue[4];
    char previousValue[4];
    unsigned long timeStamp;
    unsigned long errorTimeStamp;
    bool errorShown;

    byte currentDigit;

    void removeError();

  public:
    Display();
    
    void init(byte dataPin, byte clockPin, byte digitPin1,
      byte digitPin2, byte digitPin3, byte digitPin4);
    void showString(String input);
    void showInt(int input);
    void loop();
    void showError();
    void clearCurrentValue();
    void testProgram();
};

#endif