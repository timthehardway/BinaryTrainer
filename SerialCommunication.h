/*
  SerialCommunication.h - Class containing communication protocols for
  serial communication between the serial monitor and Binary Trainer.
  Created 17-06-2021 by Tim Ruterink.
  For study purposes.
*/

#include <Arduino.h>

class SerialCommunication
{
  private:
    String showScore; // requestedCommand 1.
    String showByte; // requestedCommand 2.
    String soundTest; // requestedCommand 3.
    String displayTest; // requestedCommand 4.
    String visualByteTest; // requestedCommand 5.
    String switchMode; // requestedCommand 6.
    // no waiting requests: requestedCommand 0.

    char startingChar;
    char endingChar;
    bool messageStarted;
    String currentMessage;

    byte requestedCommand;

    int requestedByte;
    byte requestedMode;

    int getNumberFromString(String message);

  public:
    SerialCommunication();
    void init();
    void read();
    void handleMessage();
    bool requestWaiting();
    byte getRequestedCommand();
    int getRequestedByte();
    byte getRequestedMode();
    void resetRequestedCommand();
    byte requestReceived();
};
