/*
 * Lini Mestar
 * Calculator Mathematical Association of America Spring 2013
 * Version 1.0a
 * FIXED: this version does not working with A,B,C, and D
 * FIXED: debouncing keys
 * FIXED: THIS VERSION DOES NOT WORK WITH (-) VALUES
 * FIXED: PRECISION lcd.print(1.23456, 4) gives "1.2346"
 * THIS VERSION DOES NOT INPUT (.)
 * THIS VERSION DOES NOT USE THE 'SHIFT' KEY
 * THIS VERSION DOES NOT SHOW TIME TOOK TO COMPLETE
 * THIS VERSION DOES NOT USE EXTRA PINS
 * FIXED: SINE BUTTON DEBOUNCING
 */

//Libraries
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Bounce.h>

//LCD Setup
LiquidCrystal lcd(11, 10, 5, 4, 3, 2);

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
//nr1read	add	sub multiply divide
boolean beenHere=false,
  opAddition=false, opSubtract=false, 
  opMultiply=false, opDivide=false, opSine=false;

//External Keys
#define BUTTON0  1
#define BUTTON1  12
#define BUTTON2  13
#define BUTTON3  SDA
#define BUTTON3  SCL
#define BUTTON4  A0
#define BUTTON5  A1
#define BUTTON6  A2
#define BUTTON7  A3
#define BUTTON9  A4
#define BUTTON10 A5

//delay op showing
#define DELAY 3000

//Time Setup
unsigned long T0, T1;

const int ledPin =  12;

//Numbers Inputed
int num1=0, num2=0;
int num3=0;

Bounce bouncer = Bounce( BUTTON2 , 5 );

// LCD Special Characters
byte like[8]= {
  B00000,
  B00100,
  B00100,
  B11011,
  B11001,
  B11001,
  B11111,
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
  pinMode(BUTTON2,INPUT);
  pinMode(ledPin, OUTPUT);
  keypad.setDebounceTime(25);  //keypad debounce
  decChar();
  lcd.begin(16, 2);
  //start();
  lcd.print("   Calculator");
  lcd.setCursor(0,1);
  lcd.blink();
}  //setup

void start(){
  lcd.print(" PIERCE MATH ");
  lcd.write(5);
  progBar();  
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("   SELECT AN  ");
  lcd.setCursor(1,1);
  lcd.print("    OPTION ");
  delay(2000);
  lcd.clear();
  options();
  lcd.clear();
}  //start

void decChar(){
  //Setup LCD Special Characters
  lcd.createChar(0, p20);
  lcd.createChar(1, p40);
  lcd.createChar(2, p60);
  lcd.createChar(3, p80);
  lcd.createChar(4, p100);
  lcd.createChar(5, like);
}  //decChar

void options(){
  lcd.setCursor(1,0);
  lcd.print("  A) ADD  C) MULTIPY ");
  lcd.setCursor(1,1);
  lcd.print("  B) SUB. D) DIVIDE ");
  for( int pos = 0; pos<22 ; pos++){
    lcd.scrollDisplayLeft();
    delay(550);
  }
}  //options

void progBar(){
 lcd.setCursor(0,1);
 lcd.print("                ");
 for (int i = 0; i<16; i++){
   for (int j=0; j<5; j++){
      lcd.setCursor(i, 1);   
      lcd.write(j);
      delay(80);
   }
 }
}  //progBar

void loop(){
   bouncer.update();
   
   char key = keypad.getKey();
   if(key){
     if((key !='*')&&(key !='#')&&(key !='A')
         &&(key !='B')&&(key !='C')&&(key !='D'))
       {
       if(!beenHere){
          num1 = (num1*10) + int(key-'0');
          lcd.setCursor(0,1);
          lcd.print(num1);
        }else if(beenHere && opDivide){
          num3 = (num3*10) + int(key-'0');
          lcd.print(num3);
        }else if(beenHere){
          num2 = (num2*10) + int(key-'0');
          lcd.print(num2);
        }
      }
      else if(key=='A'){
         lcd.print("+");
         beenHere=true;
         opAddition=true;
       }else if (key=='B'){
         lcd.print("-");
         beenHere=true;
         opSubtract=true;
       }else if (key=='C'){
         lcd.print("*");
         beenHere=true;
         opMultiply=true;
       }else if (key=='D'){
         lcd.print("/");
         beenHere=true;
         opDivide=true;
       }
       else if(key=='#'){
           lcd.print("=");
             if(opAddition){
               sum();
             }else if(opSubtract){
               subtract();
             }else if(opMultiply){
               multiply();         
             }else if(opDivide){
               divide();
             }else if(opSine){
               sine();
             }
            lcd.setCursor(0,1);
            lcd.print("                ");
            lcd.blink();
            num1= num2= num3= 0;
            beenHere=false;
            opAddition= opSubtract= opMultiply=opSine= false;
            opDivide= false;
       }  //else if

   }else if ( bouncer.read() ){
     delay(150);
     lcd.print("sin(");
     beenHere=true;
     opSine=true;
   }

//*/ put buttons here\*
}  //loop

void sum(){
  double sum=num1+num2;
  lcd.print(sum,0);
  delay(DELAY);
}
void subtract(){
 double dif=num1-num2;
 lcd.print(dif,0);
 delay(DELAY); 
}
void multiply(){
 double prod=num1*num2;
 lcd.print(prod,0);
 delay(DELAY);  
}
void divide(){
 float blah=double(num1)/double(num3);
 lcd.print(blah,4);
 delay(DELAY); 
}
void sine(){
  double eh = sin(num3);
  lcd.print(eh,4);
  delay(DELAY);
}
