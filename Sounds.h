/*
  Class containing basic functions for a buzzer.
  Created 10-06-2021 by Tim Ruterink.
  For study purposes.

  Dependencies: Pitches.h
  (Available at: 
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody). 
*/

#ifndef SOUNDS_H
#define SOUNDS_H

#include <Arduino.h>
#include "Pitches.h"

class Sounds {
  private:
    byte _pin;
    unsigned long timeStamp;
    byte state;
    unsigned int currentTone;
    unsigned int currentDuration;
    
    bool sequencePlaying;
    unsigned int fourTonePitches[4];
    unsigned int fourToneDurations[4];
    unsigned long sequenceTimeStamp;
    byte sequenceCurrentTone;
    bool timeStampSet;
  
  public:
    Sounds();
    void init(byte pin);
    void sequenceCheck();
    void loop();
    void playTone(int pitch, int duration);
    void playFourToneSequence(int pitches[], int durations[], int arrayLength);
    void playSequenceCustom(int pitches[], int durations[], int silences[], int arrayLength);
};

#endif