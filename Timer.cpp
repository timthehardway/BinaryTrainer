#include <Arduino.h>
#include "../include/Timer.h"

Timer::Timer()
{
  // all initialisation is done in init() method.
}

void Timer::init()
{
  _millisOnStart = 0;
  _duration = 0;
  _running = false;
}

void Timer::update()
{
  if (_running)
  {
    if (millis() - _millisOnStart > _duration)
    {
      stop();
    }
  }
}

bool Timer::secondHasPassed()
{
  unsigned long timePassed = (millis() - _millisOnStart);

  if (timePassed % 1000 == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void Timer::set(unsigned int duration)
{
  _millisOnStart = millis();
  _duration = duration;
  _running = true;
}

void Timer::stop()
{
  _running = false;
}

bool Timer::hasStopped()
{
  return !_running;
}