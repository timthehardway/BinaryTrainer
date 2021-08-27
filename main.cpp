// Official libraries
#include <Arduino.h>
#include <Keypad.h>

// Custom libraries
#include "../include/Pitches.h"
#include "../include/VisualByte.h"
#include "../include/Sounds.h"
#include "../include/AnswerLights.h"
#include "../include/Display.h"
#include "../include/GameData.h"
#include "../include/RandomGenerator.h"
#include "../include/Validator.h"
#include "../include/SerialCommunication.h"
#include "../include/Timer.h"
#include "../include/Led.h"

// FUNCTION DECLERATIONS
void keypadCommand(char);
void goodAnswer();
void wrongAnswer();
void clearQuestion();
void newQuestion();
void checkSerialMessages();
void checkKeypadInput();
void showByte();
void checkAnswer();
void timeUp();

// PINS
byte visualByteDataPin = 2;
byte visualByteClockPin = 3;
byte visualByteLatchPin = 4;

byte segDisplayDataPin = 8;
byte segDisplayClockPin = 9;
byte segDisplayDigitPin1 = 10;
byte segDisplayDigitPin2 = 11;
byte segDisplayDigitPin3 = 12;
byte segDisplayDigitPin4 = 13;

byte keyPadRowPins[] = { 30, 32, 34, 36 };
byte keyPadColumnPins[] = { 40, 42, 44, 46 };

byte buzzerPin = 5;
byte potPin = A0;
byte ledPinRed = 6;
byte ledPinGreen = 7;

byte timerLedPin = 22;

// KEYPAD
const byte keyPadRows = 4;
const byte keyPadColumns = 4;
char keyPadKeys[keyPadRows][keyPadColumns] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
char validGameChars[10] = { '0', '1', '2', '3', '4', '5', '6', 
    '7', '8', '9' };
char validControlChars[2] = { '*', '#' };

// SOUND VARIABLES
const int rightLength = 4;
int rightMelody[rightLength] = { NOTE_C4, NOTE_G4, NOTE_E5, NOTE_C5 };
int rightDurations[rightLength] = { 100, 100, 100, 500 };

const int wrongLength = 4;
int wrongMelody[wrongLength] = { NOTE_GS3, NOTE_C3, NOTE_C4, NOTE_C3 };
int wrongDurations[wrongLength] = { 100, 500, 50, 50 };

int errorTone = NOTE_G4;
int errorDuration = 300;

int inputTone = NOTE_C5;
int inputDuration = 50;

// CREATE OBJECTS
VisualByte visualByte;
Keypad keypad = Keypad( makeKeymap(keyPadKeys), keyPadRowPins, 
    keyPadColumnPins, keyPadRows, keyPadColumns);
Sounds sounds;
AnswerLights answerLights;
Display display;
GameData gameData;
Validator validator;
RandomGenerator randomGenerator;
SerialCommunication serialCommunication;
Timer timer;
Led timerLed;

// GLOBAL VARIABLES
String currentInput;
unsigned int answeringTime = 10000;

void setup() {
  // Object initialisation.
  visualByte.init(visualByteDataPin, visualByteClockPin, visualByteLatchPin);
  sounds.init(buzzerPin);
  answerLights.init(ledPinGreen, ledPinRed);
  display.init(segDisplayDataPin, segDisplayClockPin, segDisplayDigitPin1, 
      segDisplayDigitPin2, segDisplayDigitPin3, segDisplayDigitPin4);
  validator.init(validGameChars, validControlChars);
  randomGenerator.init(potPin);
  gameData.init();
  serialCommunication.init();
  timer.init();
  timerLed.init(timerLedPin);

  // Setup first question.
  gameData.setByte(randomGenerator.generateByte());
  visualByte.setByte(gameData.getByte());
  timer.set(answeringTime);

  // Activate serial communication.
  // Serial.begin(9600); 
  // Should be done by SerialCommunication class.
}

void loop() {
  // update currentMillis at the start of the loop, for use by time dependant functions.

  // methods with object specific loop functions.
  visualByte.loop(); 
  display.loop();
  sounds.sequenceCheck();
  sounds.loop();
  answerLights.loop();
  serialCommunication.read();
  timer.update();

  if (timer.secondHasPassed())
  {
    timerLed.on();
  }
  else{
    timerLed.off();
  }

  // check for commands from the serial interface and if any, handle them.
  checkSerialMessages();

  // check for keypad input and if any, handle it.
  checkKeypadInput();

  // go to next question and deduct one point if the timer runs out.
  if (timer.hasStopped())
  {
    timeUp();
  }
}

// CUSTOM FUNCTIONS

void checkSerialMessages()
{
  if (serialCommunication.requestWaiting())
  {
    byte command = serialCommunication.getRequestedCommand();

    switch (command)
    {
      case 1: // show score on the serial monitor.
        Serial.println("show score.");
        Serial.print("Your score is: ");Serial.println(gameData.getScore());
        display.showInt(gameData.getScore());
        break;
      case 2: // show byte. Uses delay.
      {
        Serial.println("Serial command received: show byte.");
        showByte();
        break;
      }
      case 3: // sound test.
        Serial.println("Serial command received: sound test.");
        sounds.playTone(NOTE_G5, 3000);
        break;
      case 4: // display test.
        Serial.println("Serial command received: display test.");
        display.testProgram();
        break;
      case 5: // visual byte test.
        Serial.println("Serial command received: visual byte test.");
        visualByte.testProgram();
        break;
      case 6: // switch mode.
        Serial.println("Serial command received: switch mode.");
        Serial.println("This function is not implemented yet.");
        break;
      default:
        serialCommunication.resetRequestedCommand();
        Serial.println("error!");
        break;
    }
    // command is handled, reset requested command.
    serialCommunication.resetRequestedCommand();
  }
}

void checkKeypadInput()
{
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
    // check the key type.
    char keyType = validator.validateCharacter(key);
    
    switch (keyType) {   
      case 'g': 
        // valid game input (numbers).
        gameData.addToCurrentAnswer(key);
        currentInput = gameData.getCurrentAnswer();
        Serial.print("Keypad input: ");Serial.println(currentInput);
        sounds.playTone(inputTone, inputDuration);
        display.showString(currentInput);
        break;

      case 'c': 
        // control commands.
        keypadCommand(key);
        break;

      case 'e': 
      default:
        // error, invalid character.
        Serial.println("Error! Invalid character.");
        sounds.playTone(errorTone, errorDuration);
        display.showError();
    }
  }
}

void keypadCommand(char command) {
  // executes control commands entered on the keypad.
  
  if (command == '*') // user wants to clear current input.
  {
    sounds.playTone(inputTone, inputDuration);
    gameData.clearCurrentAnswer();
    display.clearCurrentValue();
  }
  else if (command == '#') // user submits answer.
  {
    checkAnswer();
  }
  else {
    Serial.print("Error, command unknown: ");Serial.println(command);
  }
}

void showByte()
{
  int requestedByte = serialCommunication.getRequestedByte();
  Serial.print("requested byte: ");
  Serial.println(requestedByte);
  if (requestedByte >= 0 && requestedByte <= 255)
  {
    visualByte.show(requestedByte, 3000);
  }
  else
  {
    Serial.println("error: only values between 0 and 255 are accepted.");
  }
}

void checkAnswer()
{
  String answer = gameData.getCurrentAnswer();

  // check if answer is an int and fits into a byte.
  if (validator.isAnInt(answer) && validator.fitsIntoByte(answer))
  {
    Serial.print("Your answer is: ");
    Serial.println(answer);
    int answerInt = answer.toInt();
    byte solution = gameData.getByte();

    if (answerInt == solution)
    {
      goodAnswer();
      clearQuestion();
      newQuestion();
    }
    else
    {
      wrongAnswer();
    }
  }
  else // answer can not be converted to an int or is too small or large.
  {
    Serial.println("Error, your number is probably zero or too high.");
    sounds.playTone(errorTone, errorDuration);
    display.clearCurrentValue();
    gameData.clearCurrentAnswer();
    display.showError();
  }
}

void goodAnswer() 
{
  answerLights.rightAnswer();
  sounds.playFourToneSequence(rightMelody, rightDurations, rightLength);
  gameData.addPointToScore();
  Serial.print("Your score is: ");Serial.println(gameData.getScore());
}

void wrongAnswer() 
{
  answerLights.wrongAnswer();
  sounds.playFourToneSequence(wrongMelody, wrongDurations, wrongLength);
  gameData.clearCurrentAnswer();
  display.clearCurrentValue();
  Serial.println(gameData.getByte()); // spiekbriefje.
}

void clearQuestion() 
{
  gameData.clearCurrentAnswer();
  visualByte.clear();
  display.clearCurrentValue();
}

void newQuestion() 
{
  gameData.setByte(randomGenerator.generateByte());
  visualByte.setByte(gameData.getByte());
  timer.set(answeringTime);
}

void timeUp()
{
  Serial.println("Time is up!");
  answerLights.wrongAnswer();
  sounds.playTone(errorTone, errorDuration);
  gameData.deductPointFromScore();
  clearQuestion();
  newQuestion();
}