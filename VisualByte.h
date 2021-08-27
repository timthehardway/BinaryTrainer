/*
  VisualByte.h - Library containing functions for displaying
  byte patterns on an array of 8 leds connected to a 
  SN74HC595 bit shift register.

  Created 04-06-2021 by Tim Ruterink.
  For study purposes.
*/

#ifndef VISUALBYTE_H
#define VISUALBYTE_H

#include <Arduino.h>

class VisualByte 
{
  private:
    byte _dataPin;
    byte _clockPin;
    byte _latchPin;
    byte currentByte;
    byte state;
    
  public:
    VisualByte();
    void init(byte dataPin, byte clockPin, byte latchPin);
    void setByte(byte newByte);
    void loop();
    void show(byte input, int milliseconds);
    void testProgram();
    void clear();
};

#endif