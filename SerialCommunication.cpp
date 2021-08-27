#include <Arduino.h>
#include "../include/SerialCommunication.h"

SerialCommunication::SerialCommunication()
{
  // all initialisation is done with init() method.
}

void SerialCommunication::init()
{
  showScore = "SHOW_SCORE"; // request 1.
  showByte = "SHOW_BYTE:"; // request 2.
  soundTest = "SOUND_TEST"; // request 3.
  displayTest = "DISPLAY_TEST"; // request 4.
  visualByteTest = "VISUAL_BYTE_TEST"; // request 5.
  switchMode = "SWITCH_MODE:"; // request 6.

  startingChar = '#';
  endingChar = '%';
  messageStarted = false;
  currentMessage = "";

  requestedByte = 0;
  requestedMode = 0;

  Serial.begin(9600);
}

void SerialCommunication::read()
{
  if (Serial.available() > 0)
  {
    char readByte = Serial.read();
    if (readByte == startingChar)
    // start a new message.
    {
      currentMessage = "";
      messageStarted = true;
    }
    else if (messageStarted)
    {
      if (readByte == endingChar)
      // message ended, send to handleMessage() method.
      {
        messageStarted = false;
        handleMessage();
      }
      else if (readByte != '\n')
      // add to current message, ignore newline characters.
      {
        currentMessage += readByte;
      }
    }
  }
}

void SerialCommunication::handleMessage()
// compare messages to commands from the protocol.
// set requestedCommand accordingly.
{
  // convert all letters to uppercase.
  currentMessage.toUpperCase();

  if (currentMessage.equals(showScore))
  {
    requestedCommand = 1;
  }
  else if (currentMessage.startsWith(showByte))
  {
    requestedCommand = 2;
    requestedByte = getNumberFromString(currentMessage);
  }
  else if (currentMessage.equals(soundTest))
  {
    requestedCommand = 3;
  }
  else if (currentMessage.equals(displayTest))
  {
    requestedCommand = 4;
  }
  else if (currentMessage.equals(visualByteTest))
  {
    requestedCommand = 5;
  }
  else if (currentMessage.startsWith(switchMode))
  {
    requestedCommand = 6;
    requestedMode = getNumberFromString(currentMessage);
  }
  else
  {
    Serial.print("Unknown command: ");Serial.println(currentMessage);
  }
}

byte SerialCommunication::getRequestedCommand()
// this makes the requested command accessible for the main program.
{
  return requestedCommand;
}

int SerialCommunication::getRequestedByte()
{
  return requestedByte;
}

byte SerialCommunication::getRequestedMode()
{
  return requestedMode;
}

bool SerialCommunication::requestWaiting()
{
  return (requestedCommand != 0);
}

int SerialCommunication::getNumberFromString(String message)
// used within the class to separate a integer value from a text command.
{
  byte index = currentMessage.indexOf(':');
  String number = currentMessage.substring(index + 1);
  number.trim();
  return number.toInt();
}

void SerialCommunication::resetRequestedCommand()
// used by the main program to reset the requested command after handling it.
{
  requestedCommand = 0;
}