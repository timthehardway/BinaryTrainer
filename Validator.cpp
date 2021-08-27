#include <Arduino.h>
#include "../include/Validator.h"

Validator::Validator() {
  // Initialisation is done in init() method.
}

void Validator::init(char validChars[10], char controlChars[2]) {
  for (int i = _arrayGameChars-1; i >= 0; i--) {
    _validGameChars[i] = validChars[i];
  }
  for (int i = _arrayControlChars-1; i >= 0; i--) {
    _validControlChars[i] = controlChars[i];
  }
}

char Validator::validateCharacter(char input) {
  for (int i = _arrayGameChars-1; i >= 0; i--) {
    if (input == _validGameChars[i]) {
      return 'g'; // game char.
    }
  }
  for (int i = _arrayControlChars-1; i >= 0; i--) {
    if (input == _validControlChars[i]) {
      return 'c'; // control char.
    }
  }
  return 'e'; // error char.
}

bool Validator::isAnInt(String input) 
{
  int value = input.toInt();
  // if the String object can not be converted to an int, a value
  // of '0' will be returned. This means we can not distinguish
  // incompatible input (letters) from an actual '0' as input.
  //
  // For this reason, zero is not allowed as answer or solution
  // in the program.
  if (value != 0) 
  {
    return true;
  }
  else 
  {
    return false;
  }
}

bool Validator::fitsIntoByte(String input)
{
  int value = input.toInt();
  if (value >= 0 && value <= 255)
  {
    return true;
  }
  else
  {
    return false;
  }
}