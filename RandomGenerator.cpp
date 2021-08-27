#include <Arduino.h>
#include "../include/RandomGenerator.h"

RandomGenerator::RandomGenerator() {
  // all initialisation is done with the init() method.
}

void RandomGenerator::init(byte potentiometerPin)
{
  _potentiometerPin = potentiometerPin;
  pinMode(_potentiometerPin, INPUT);
  randomSeed(analogRead(_potentiometerPin));
}

byte RandomGenerator::generateByte()
{
  return random(1, 255);
}