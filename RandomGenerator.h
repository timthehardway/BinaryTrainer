/*
  GameEngine.h - Class containing a simple method of generating
  random numbers, by feeding a value of a analogRead() to the
  randomSeed function and thus avoiding the appearance of the
  same random numbers every time the program starts.

  A sensor with analog output should be connected to the
  analog pin of the Arduino. This example works with a
  potentiometer. Every time the potentiometer is turned,
  the randomSeed input is changed.

  Created 17-06-2021 by Tim Ruterink.
  For study purposes.
*/

#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <Arduino.h>

class RandomGenerator {
  private:
    byte _potentiometerPin; // or some other analog sensor.

  public:
    RandomGenerator();
    void init(byte pin);
    byte generateByte();
};

#endif