/*
  BinaryNumbers.h - Library containing byte characters created
  for a common anode (bit 1 means led off) segment led display.
  Created 04-06-2021 by Tim Ruterink.
  For study purposes.
*/

#ifndef BINARYNUMBERS_H
#define BINARYNUMBERS_H

#include <Arduino.h>

class BinaryNumbers {
  public:
    BinaryNumbers();

    const byte blank = 0b11111111;
    const byte zero = 0b10000001;
    const byte one = 0b11111001;
    const byte two = 0b00100101;
    const byte three = 0b00101001;
    const byte four = 0b01011001;
    const byte five = 0b00001011;
    const byte six = 0b00000011;
    const byte seven = 0b10111001;
    const byte eight = 0b00000001;
    const byte nine = 0b00001001;

    const byte err[3] = { 0b00000111, 0b01110111, 0b01110111 };

    byte convertChar(char input);
};

#endif
