#include <Arduino.h>
#include "../include/Display.h"
#include "../include/BinaryNumbers.h"

BinaryNumbers binaryNumbers;

Display::Display()
{
  // Default values are set in init() function, this is more reliable with Arduino.
}

void Display::init(byte dataPin, byte clockPin, byte digitPin1,
  byte digitPin2, byte digitPin3, byte digitPin4)
{
  _dataPin = dataPin;
  _clockPin = clockPin;
  _digitPin1 = digitPin1;
  _digitPin2 = digitPin2;
  _digitPin3 = digitPin3;
  _digitPin4 = digitPin4;

  pinMode(_dataPin, OUTPUT);
  pinMode(_clockPin, OUTPUT);
  pinMode(_digitPin1, OUTPUT);
  pinMode(_digitPin2, OUTPUT);
  pinMode(_digitPin3, OUTPUT);
  pinMode(_digitPin4, OUTPUT);

  timeStamp = 0;
  currentDigit = 1;

  errorShown = false;
  errorTimeStamp = 0;
  
  currentValue[0] = binaryNumbers.zero;
  currentValue[1] = binaryNumbers.zero;
  currentValue[2] = binaryNumbers.zero;
  currentValue[3] = binaryNumbers.zero;

  previousValue[0] = binaryNumbers.zero;
  previousValue[1] = binaryNumbers.zero;
  previousValue[2] = binaryNumbers.zero;
  previousValue[3] = binaryNumbers.zero;
}

void Display::loop()
{
  if (millis() - timeStamp >= 4)
  {
    currentDigit++;
    switch(currentDigit)
    {
      case 1:
        digitalWrite(_digitPin4, 0);
        digitalWrite(_digitPin1, 1);
        shiftOut(_dataPin, _clockPin, LSBFIRST, currentValue[0]);
        timeStamp = millis();
        break;
      case 2:
        digitalWrite(_digitPin1, 0);
        digitalWrite(_digitPin2, 1);
        shiftOut(_dataPin, _clockPin, LSBFIRST, currentValue[1]);
        timeStamp = millis();
        break;
      case 3:
        digitalWrite(_digitPin2, 0);
        digitalWrite(_digitPin3, 1);
        shiftOut(_dataPin, _clockPin, LSBFIRST, currentValue[2]);
        timeStamp = millis();
        break;
      case 4:
        digitalWrite(_digitPin3, 0);
        digitalWrite(_digitPin4, 1);
        shiftOut(_dataPin, _clockPin, LSBFIRST, currentValue[3]);
        timeStamp = millis();
        currentDigit = 0;
        break;
      default:
        Serial.println("error: default case triggered in displayLoop().");
        break;
    }
  }

  if (errorShown)
  {
    if (millis() - errorTimeStamp > 3000)
    {
      removeError();
    }
  }
}

void Display::showError()
// Uses previousValue[] to store currentValue[], then temporarily switches to 'Err' and back.
{
  errorTimeStamp = millis();

  for (int i = 0; i < numOfDigits; i++)
  {
    previousValue[i] = currentValue[i];
  }

  currentValue[0] = binaryNumbers.err[0];
  currentValue[1] = binaryNumbers.err[1];
  currentValue[2] = binaryNumbers.err[2];
  currentValue[3] = binaryNumbers.blank;

  errorShown = true;
}

void Display::removeError()
// restores currentValue[] to the previous shown value.
{
  for (int i = 0; i < numOfDigits; i++)
  {
    currentValue[i] = previousValue[i];
  }

  errorShown = false;
}

void Display::updateCurrentValue(char chars[], int arrayLength)
// This function actually converts to a byte array and calls a showBytesWithDelay function.
//
// Returning a byte array would be a better solution I think, but I do not know
// how to do this yet. (Return a struct instead?)
{
  // byte bytes[arrayLength];

  for (int i = 0; i < arrayLength; i++)
  {
    // bytes[i] = binaryNumbers.convertChar(chars[i]);
    currentValue[i] = binaryNumbers.convertChar(chars[i]);
  }

  // showBytesWithDelay(bytes);
}

void Display::showString(String input)
{
  // Check length of string (minimum 0, maximum 4)
  input.trim();
  int stringLength = input.length();

  int minimumLength = 4;
  char characters[minimumLength];
  
  // Validation of only digits as input is handled in the validator for now.
  // If there are less than 4 characters, add zeroes (to the left).
  if (stringLength <= minimumLength)
  { 
    switch(stringLength) {
      case 0:
        characters[0] = '-';
        characters[1] = '-';
        characters[2] = '-';
        characters[3] = '-';
        break;
      case 1:
        characters[0] = '-';
        characters[1] = '-';
        characters[2] = '-';
        characters[3] = input.charAt(0);
        break;
      case 2:
        characters[0] = '-';
        characters[1] = '-';
        characters[2] = input.charAt(0);
        characters[3] = input.charAt(1);
        break;
      case 3:
        characters[0] = '-';
        characters[1] = input.charAt(0);
        characters[2] = input.charAt(1);
        characters[3] = input.charAt(2);
        break;
      case 4:
        characters[0] = input.charAt(0);
        characters[1] = input.charAt(1);
        characters[2] = input.charAt(2);
        characters[3] = input.charAt(3);
        break;
      default:
        characters[0] = '-';
        characters[1] = '-';
        characters[2] = '-';
        characters[3] = '-';
        break;
    }
    updateCurrentValue(characters, minimumLength);
  }
  else
  {
    Serial.println("Display showString error.");
  }

  // Convert characters to a byte array using binaryNumbers class.
  // Send byte array to showCharacters function.
}

void Display::showInt(int input)
{
  if (input >= 0 && input <= 9999)
  {
    String number = String(input);
    showString(number);
  }
  else
  {
    Serial.println("error in Display::showInt. Number too small or large.");
  }
}

void Display::clearCurrentValue()
{
  currentValue[0] = binaryNumbers.blank;
  currentValue[1] = binaryNumbers.blank;
  currentValue[2] = binaryNumbers.blank;
  currentValue[3] = binaryNumbers.blank;
}

void Display::testProgram()
{
  for (int i = 100; i > 0; i--) {
    digitalWrite(_digitPin1, 1);
    shiftOut(_dataPin, _clockPin, LSBFIRST, binaryNumbers.zero);
    delay(4);
    digitalWrite(_digitPin1, 0);
    digitalWrite(_digitPin2, 1);
    shiftOut(_dataPin, _clockPin, LSBFIRST, binaryNumbers.one);
    delay(4);
    digitalWrite(_digitPin2, 0);
    digitalWrite(_digitPin3, 1);
    shiftOut(_dataPin, _clockPin, LSBFIRST, binaryNumbers.two);
    delay(4);
    digitalWrite(_digitPin3, 0);
    digitalWrite(_digitPin4, 1);
    shiftOut(_dataPin, _clockPin, LSBFIRST, binaryNumbers.three);
    delay(4);
    digitalWrite(_digitPin4, 0);
  }

  for (int i = 100; i > 0; i--) {
    digitalWrite(_digitPin1, 1);
    shiftOut(_dataPin, _clockPin, LSBFIRST, binaryNumbers.four);
    delay(4);
    digitalWrite(_digitPin1, 0);
    digitalWrite(_digitPin2, 1);
    shiftOut(_dataPin, _clockPin, LSBFIRST, binaryNumbers.five);
    delay(4);
    digitalWrite(_digitPin2, 0);
    digitalWrite(_digitPin3, 1);
    shiftOut(_dataPin, _clockPin, LSBFIRST, binaryNumbers.six);
    delay(4);
    digitalWrite(_digitPin3, 0);
    digitalWrite(_digitPin4, 1);
    shiftOut(_dataPin, _clockPin, LSBFIRST, binaryNumbers.seven);
    delay(4);
    digitalWrite(_digitPin4, 0);
  }

  for (int i = 100; i > 0; i--) {
    digitalWrite(_digitPin1, 1);
    shiftOut(_dataPin, _clockPin, LSBFIRST, binaryNumbers.eight);
    delay(4);
    digitalWrite(_digitPin1, 0);
    digitalWrite(_digitPin2, 1);
    shiftOut(_dataPin, _clockPin, LSBFIRST, binaryNumbers.nine);
    delay(4);
    digitalWrite(_digitPin2, 0);
    digitalWrite(_digitPin3, 1);
    shiftOut(_dataPin, _clockPin, LSBFIRST, binaryNumbers.one);
    delay(4);
    digitalWrite(_digitPin3, 0);
    digitalWrite(_digitPin4, 1);
    shiftOut(_dataPin, _clockPin, LSBFIRST, binaryNumbers.blank);
    delay(4);
    digitalWrite(_digitPin4, 0);
  }

  for (int i = 100; i > 0; i--) {
    digitalWrite(_digitPin1, 1);
    shiftOut(_dataPin, _clockPin, LSBFIRST, binaryNumbers.err[0]);
    delay(4);
    digitalWrite(_digitPin1, 0);
    digitalWrite(_digitPin2, 1);
    shiftOut(_dataPin, _clockPin, LSBFIRST, binaryNumbers.err[1]);
    delay(4);
    digitalWrite(_digitPin2, 0);
    digitalWrite(_digitPin3, 1);
    shiftOut(_dataPin, _clockPin, LSBFIRST, binaryNumbers.err[2]);
    delay(4);
    digitalWrite(_digitPin3, 0);
    digitalWrite(_digitPin4, 1);
    shiftOut(_dataPin, _clockPin, LSBFIRST, binaryNumbers.blank);
    delay(4);
    digitalWrite(_digitPin4, 0);
  }  
}