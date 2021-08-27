#include <Arduino.h>
#include "../include/Pitches.h"
#include "../include/Sounds.h"

Sounds::Sounds() {
  // empty, initialisation is done in init() method.
}

void Sounds::init(byte pin) {
  _pin = pin;
  pinMode(_pin, OUTPUT);
  timeStamp = 0;
  state = 0;
  currentTone = NOTE_C4;
  currentDuration = 0;
  sequencePlaying = false;
  sequenceTimeStamp = 0;
  sequenceCurrentTone = 0;
  timeStampSet = false;
}

void Sounds::sequenceCheck()
// checks if there is a sequence of tones playing, updates tone, duration and state accordingly.
{
  if (sequencePlaying)
  {
    if (sequenceCurrentTone == 0 && timeStampSet == false)
    {
      playTone(fourTonePitches[0], fourToneDurations[0]);
      timeStampSet = true;
    }
    else if (sequenceCurrentTone == 0 && timeStampSet == true)
    {
      if (millis() - timeStamp > fourToneDurations[0])
      {
        sequenceCurrentTone++;
        timeStampSet = false;
      }
    }
    else if (sequenceCurrentTone == 1 && timeStampSet == false)
    {
      playTone(fourTonePitches[1], fourToneDurations[1]);
      timeStampSet = true;
    }
    else if (sequenceCurrentTone == 1 && timeStampSet == true)
    {
      if (millis() - timeStamp > fourToneDurations[1])
      {
        sequenceCurrentTone++;
        timeStampSet = false;
      }
    }
    else if (sequenceCurrentTone == 2 && timeStampSet == false)
    {
      playTone(fourTonePitches[2], fourToneDurations[2]);
      timeStampSet = true;
    }
    else if (sequenceCurrentTone == 2 && timeStampSet == true)
    {
      if (millis() - timeStamp > fourToneDurations[2])
      {
        sequenceCurrentTone++;
        timeStampSet = false;
      }
    }
    else if (sequenceCurrentTone == 3 && timeStampSet == false)
    {
      playTone(fourTonePitches[3], fourToneDurations[3]);
      timeStampSet = true;
    }
    else if (sequenceCurrentTone == 3 && timeStampSet == true)
    {
      if (millis() - timeStamp > fourToneDurations[3])
      {
        sequenceCurrentTone++;
        timeStampSet = false;
      }
    }
    else if (sequenceCurrentTone >= 4)
    {
      sequenceCurrentTone = 0;
      sequencePlaying = false;
    }
  }
}

void Sounds::loop()
{
  if (state == 1)
  {
    tone(_pin, currentTone);
  }
  else if (state == 0)
  {
    noTone(_pin);
  }
    
  if (millis() - timeStamp > currentDuration)
  {
    state = 0;
  }
}

void Sounds::playTone(int pitch, int duration)
// play a single tone with a specified duration, without using delay().
{
  currentTone = pitch;
  currentDuration = duration;
  state = 1;
  timeStamp = millis();
}

void Sounds::playFourToneSequence(int pitches[], int durations[], int arrayLength)
// Play sequence of four tones with custom durations without delay().
{
  for (int i = 0; i < arrayLength; i++)
  {
    fourTonePitches[i] = pitches[i];
    fourToneDurations[i] = durations[i];
  }
  sequencePlaying = true;
}

void Sounds::playSequenceCustom(int pitches[], int durations[], int silences[], int arrayLength) {
  // Play sequence of tones with custom durations and silences in between notes.
  // Warning: uses delay.
    
  for (int i = 0; i < arrayLength; i++) {
    tone(_pin, pitches[i], durations[i]);
    delay(durations[i] + silences[i]); // delay vervangen door iets beters!
  }

  // Check if three arrays have the same length?
  // What happens if the program tries to read outside the array?
}

/*

void Sounds::playSequenceBasic(int pitches[], int duration, int arrayLength)
// Play sequence of tones with the same duration.
{
  for (int i = 0; i < arrayLength; i++)
  {
    tone(_pin, pitches[i], duration);
    delay(duration);
  }
}

*/