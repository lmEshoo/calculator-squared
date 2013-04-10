/*
 * Lini Mestar
 * Calculator Mathematical Association of America Spring 2013
 * Version 1.0b
 *
 * FIXED: this version does not working with A,B,C, and D
 * FIXED: debouncing keys
 * FIXED: THIS VERSION DOES NOT WORK WITH (-) VALUES
 * FIXED: PRECISION lcd.print(1.23456, 4) gives "1.2346"
 * FIXED: THIS VERSION DOES NOT USE EXTRA PINS
 * FIXED: SINE BUTTON DEBOUNCING
 * FIXED: SHOWING 122 INSTEAD 12
 * FIXED: THIS VERSION DOES NOT SHOW TOTAL TIME
 * * == )
 * THIS VERSION CAN DOES + - * / sin cos tan Tsin Tcos
*/

//Libraries
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Bounce.h>

//LCD Hookups
#define RS 10
#define EN 11
#define D4 2
#define D5 3
#define D6 4
#define D7 5

//External Selection Buttons
#define BUTTON0  A5
#define BUTTON1  A4
#define BUTTON2  A3
#define BUTTON3  A2
#define BUTTON4  A1
#define BUTTON5  A0
#define BUTTON6  12
#define BUTTON7  13
#define BUTTON8  SDA
#define BUTTON9  SCL
#define BUTTON10 1

//delay op showing
#define DELAY 3000

//LCD Setup
LiquidCrystal lcd(EN, RS, D7, D6, D5, D4);

//4x4 matrix Keypad
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

//Keypad Pin Setup
byte rowPins[ROWS] = {2,3,4,5};
byte colPins[COLS] = {6,7,8,9};

//initialize the Keypad library
Keypad keypad = Keypad( makeKeymap(keys), 
                  rowPins, colPins, ROWS, COLS );

boolean beenHere=false,
  opAddition=false, opSubtract=false, 
  opMultiply=false, opDivide=false,
  opSine=false, opCosine=false, opTan=false,
  opTsin=false, opTcos=false, opTtan=false;

//Time Setup
unsigned long T0, T1;
unsigned long tT0, tT1;

const double pi = 3.14159265358979323846;
//const int backlight =  13;

//Numbers Inputed
int num1=0, num2=0;
unsigned int num3=0;

Bounce bouncer  = Bounce( BUTTON0 , 15 );
Bounce bouncer1 = Bounce( BUTTON1 , 15 );
Bounce bouncer2 = Bounce( BUTTON2 , 15 );
Bounce bouncer3 = Bounce( BUTTON3 , 15 );
Bounce bouncer4 = Bounce( BUTTON4 , 15 );
Bounce bouncer5 = Bounce( BUTTON5 , 15 );
Bounce bouncer6 = Bounce( BUTTON6 , 15 );
Bounce bouncer7 = Bounce( BUTTON7 , 15 );
Bounce bouncer8 = Bounce( BUTTON8 , 15 );
Bounce bouncer9 = Bounce( BUTTON9 , 15 );

// LCD Special Characters
byte like[8] = {
  B00000,
  B00100,
  B00100,
  B11011,
  B11001,
  B11001,
  B11111,
};
byte squared[8] = {
 B11000,
 B00100,
 B01000,
 B10000,
 B11100,
 B00000,
 B00000,
};
byte p20[8] = {
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
};
byte p40[8] = {
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
};
byte p60[8] = {
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
};
byte p80[8] = {
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
};
byte p100[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

void setup(){
  Serial.begin(9600);
  keypad.setDebounceTime(150);
  decChar();
  initialButtons();
  lcd.begin(16, 2);
  lcd.print("   Welcome to..");
  for( int pos = 0; pos<9 ; pos++){
    lcd.scrollDisplayLeft();
    delay(200);
  }
  lcd.clear();
  for( int i = 0; i < 10 ; i++ ){
    if( i == 10 ) delay(2000);
    introName(i);
  }
  delay(2000);
  lcd.clear();
  start();
  lcd.setCursor(0,0);
  lcd.blink();
}  //setup
void introName(int i){
  unsigned counter = 0;
  int num;
  counter++;
  num=i+1;
  Serial.print(counter);
    if( num % 2 == 0 ){
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("   Calculator");
      lcd.setCursor(13,1);
      lcd.write(6);
      delay(250);
    }else
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("   Calculator");
      lcd.setCursor(13,0);
      lcd.write(6);
      delay(250);
      //lcd.clear();
}
