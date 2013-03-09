// Example 42.2 - Six-digit keypad switch
// http://tronixstuff.wordpress.com/tutorials > chapter 42

#include "Keypad.h"

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] =
{{'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}};
byte rowPins[ROWS] = {
  5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {
  8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

char PIN[6]={'1','2','3','4','5','6'}; // our secret (!) number
char attempt[6]={
  0,0,0,0,0,0}; // used for comparison
int z=0;

void setup()
{
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  incorrectPIN();
}

void correctPIN() // do this if correct PIN entered
{
  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
}

void incorrectPIN() // do this if incorrect PIN entered
{
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
}

void getNum(){
  for (int q=0; q<2; q++)
  {
    if (attempt[q]==PIN[q])
    {
      correct++;
    }
  }
  if (correct==6)
  {
    correctPIN();
  } else
  {
    incorrectPIN();
  }
}

void readKeypad()
{
  char key = keypad.getKey();
  if (key != NO_KEY)
  {
    switch(key)
    {
    case '*':
      z=0;
      break;
    case '#':
      delay(100); // for extra debounce
      checkPIN();
        break;
    default:
      attempt[z]=key;
      z++;
    }
  }
}

void loop()
{
  readKeypad();
}
