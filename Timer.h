/*
  Timer.h - Class containing timekeeping functions for
  the Binary Trainer.
  Created 20-06-2021 by Tim Ruterink.
  For study purposes.
*/
#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

class Timer
{
  private:
    unsigned long _millisOnStart;
    unsigned int _duration;
    bool _running;

    void stop();

  public:
    Timer();
    void init();
    void update();
    void set(unsigned int milliseconds);
    bool hasStopped();
    bool secondHasPassed();
};

#endif