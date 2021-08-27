#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <Arduino.h>

class Validator {
  private:
    char _validGameChars[10]; // can I define the length with a call to init()?
    int _arrayGameChars = 10;
    char _validControlChars[2];
    int _arrayControlChars = 2;

  public:
    Validator();
    void init(char validInputChars[10], char validControlChars[2]);
    char validateCharacter(char input);
    bool isAnInt(String input);
    bool fitsIntoByte(String input);
};

#endif