/*
  GameData.h - Class containing binary trainer game data
  and properties.
  Created 15-06-2021 by Tim Ruterink.
  For study purposes.
*/

#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <Arduino.h>

class GameData {
  private:
    String currentAnswer;
    byte currentByte;
    int score;

  public:
    GameData();
    String getCurrentAnswer();
    void init();
    void addToCurrentAnswer(char keychar);
    void clearCurrentAnswer();
    void addPointToScore();
    void deductPointFromScore();
    byte getByte();
    void setByte(byte newByte);;
    int getScore();
};

#endif