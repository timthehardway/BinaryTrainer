#include <Arduino.h>
#include "../include/GameData.h"

GameData::GameData() {
  // initialisation is done with init() method.
}

String GameData::getCurrentAnswer() {
  return currentAnswer;
}

void GameData::init() {
  currentAnswer = "";
  score = 0;
}

void GameData::addToCurrentAnswer(char keychar)
{
  currentAnswer.concat(keychar);
}

void GameData::clearCurrentAnswer()
{
  currentAnswer = "";
}

void GameData::addPointToScore()
{
  score++;
}

void GameData::deductPointFromScore()
{
  score--;
}

void GameData::setByte(byte newByte)
{
  currentByte = newByte;
}

byte GameData::getByte()
{
  return currentByte;
}

int GameData::getScore()
{
  return score;
}
