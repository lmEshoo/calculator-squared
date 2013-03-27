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
 * THIS VERSION DOES NOT INPUT (.)
 * FIXED: SHOWING 122 INSTEAD 12
 * FIXED: THIS VERSION DOES NOT SHOW TOTAL TIME
 * * == )
 * THIS VERSION CAN DOES + - * / sin cos tan
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
  opSine=false, opCosine=false,
  opTan=false;

//Time Setup
unsigned long T0, T1;

const double pi = 3.14159265358979323846;
//const int ledPin =  12;

//Numbers Inputed
unsigned int num1=0, num2=0;
unsigned int num3=0;

Bounce bouncer  = Bounce( BUTTON0 , 5 );
Bounce bouncer1 = Bounce( BUTTON1 , 5 );
Bounce bouncer2 = Bounce( BUTTON2 , 5 );
Bounce bouncer3 = Bounce( BUTTON3 , 5 );
Bounce bouncer4 = Bounce( BUTTON4 , 5 );
Bounce bouncer5 = Bounce( BUTTON5 , 5 );
Bounce bouncer6 = Bounce( BUTTON6 , 5 );
Bounce bouncer7 = Bounce( BUTTON7 , 5 );
Bounce bouncer8 = Bounce( BUTTON8 , 5 );
Bounce bouncer9 = Bounce( BUTTON9 , 5 );

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
  keypad.setDebounceTime(150);  //keypad debounce
  decChar();
  initialButtons();
  lcd.begin(16, 2);
  //start();
  lcd.setCursor(0,0);
  lcd.blink();
}  //setup

void initialButtons(){
  pinMode(BUTTON0,INPUT);
  pinMode(BUTTON1,INPUT);
  pinMode(BUTTON2,INPUT);
  pinMode(BUTTON3,INPUT);
  pinMode(BUTTON4,INPUT);
  pinMode(BUTTON5,INPUT);
  pinMode(BUTTON6,INPUT);
  pinMode(BUTTON7,INPUT);
  pinMode(BUTTON8,INPUT);
  pinMode(BUTTON9,INPUT);
}  //initialButtons
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
/*******************************
* KEYS AND BUTTONS WHEN PRESSED
********************************/
void buttonUpdate(){
  bouncer.update();
  bouncer1.update();
  bouncer2.update();
  bouncer3.update();
  bouncer4.update();
  bouncer5.update();
  bouncer6.update();
  bouncer7.update();
  bouncer8.update();
  bouncer9.update();
}  //buttonUpdate
void loop()
{
   buttonUpdate();
   char key = keypad.getKey();
   /*************************************
   * KEYPAD BUTTON READING W/ DEBOUNCING
   **************************************/
   if(key != NO_KEY){
     if((key !='*')&&(key !='#')&&(key !='A')
         &&(key !='B')&&(key !='C')&&(key !='D'))
       {
       if(!beenHere){
          num1 = (num1*10) + int(key-'0');
          lcd.setCursor(0,0);
          lcd.print(num1);
        }else if(beenHere && opDivide){
          num2 = (num2*10) + int(key-'0');
          lcd.print(num2);
        }else if(opSine || opCosine || opTan){
          lcd.setCursor(4,0);
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
       }else if (key=='*'){
         lcd.print(")");
       }
       else if(key=='#'){
           lcd.print("=");
           lcd.setCursor(0,1);
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
             }else if(opCosine){
               cosine();
             }else if(opTan){
               tangent();
             }
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.blink();
            num1= num2= num3= 0;
            beenHere=false;
            opAddition= opSubtract= opMultiply=opSine= false;
            opDivide=opCosine=opTan =false;
       }
   /*************************************
   * EXTERNAL BUTTON READING W/ DEBOUNCING
   **************************************/
   }else if ( bouncer.read() ){
     delay(250);
     lcd.print("sin(");
     beenHere=true;
     opSine=true;
   }else if ( bouncer1.read() ){
     delay(250);
     lcd.print("cos(");
     beenHere=true;
     opCosine=true;
   }else if ( bouncer2.read() ){
     delay(250);
     lcd.print("tan(");
     beenHere=true;
     opTan=true;
   }
}  //loop
void sum(){
  T0 = millis();
  double sum=num1+num2;
  T1 = millis();
  lcd.print(sum,0);
  delay(DELAY);
  lcd.print("Time:");
  showTime();
}  //sum
void subtract(){
  T0 = millis();
 double dif=num1-num2;
 T1 = millis();
 lcd.print(dif,0);
 delay(DELAY);
 showTime();
}  //subtract
void multiply(){
  T0 = millis();
  double prod=num1*num2;
  T1 = millis();
  lcd.print(prod,0);
  delay(DELAY);
  showTime();
}  //multiply
void divide(){
  T0 = millis();
  float blah=double(num1)/double(num2);
  T1 = millis();
  lcd.print(blah,4);
  delay(DELAY);
  showTime();
}  //divide
void sine(){
  T0 = millis();
  lcd.print(sin(num3),4);
  T1 = millis();
  delay(DELAY);
  showTime();
}  //sine
void cosine(){
  T0 = millis();
  lcd.print(cos(num3),4);
  T1 = millis();
  delay(DELAY);
  showTime();
}  //cosine
void tangent(){
  T0 = millis();
  lcd.print(tan(num3),4);
  T1 = millis();
  delay(DELAY);
  showTime();
}  //tangent
double T_COS( double x,int degree){
  int i = 0;
  double accumulation = 0;
  int cosInputArray[4] = {1,0,-1,0};
  if (x > 1.57079) {
       x = referenceAngle(x);
  }
  while (i < degree){
    int input = cosInputArray[i%4];
    accumulation += input*((pow(x, i))/factorial(i)); 
    i++;
  }
  return accumulation;
}  //T_COS
double T_SIN( double x, int degree){
  int i = 0;
  double accumulation = 0;
  int sinInputArray[4] = {0,1,0,-1};
  if (x > 1.57079) {
     x = referenceAngle(x);
   }
  while (i < degree) {
    int input = sinInputArray[i%4];
    accumulation += input*((pow(x, i))/factorial(i));
    i++;
  }
  return accumulation;
}  //T_SIN
double factorial(int input ) {
  double output = 1;
  for( int i = 2; i <= input; ++ i ) {
      output *= i;
  }
  return output;
}  //factorial
double referenceAngle( double x){
  int k = 0;
  int quadrant = 0;
  double referenceAngle = 0.0;
  k = floor(x/(pi/2));
  quadrant = k % 4;
  if (quadrant == 1 || quadrant == 3) {
      referenceAngle = x - ((pi/2)*k);
  }else {
      referenceAngle = (pi/2) - (x - ((pi/2)*k));
  }
  return referenceAngle;
}  // referenceAngle
void showTime(){
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Time:");
 lcd.setCursor(0,1);
 lcd.print(T1-T0);
 lcd.print(" Milli Sec.");
 delay(DELAY);
}  //showTime
