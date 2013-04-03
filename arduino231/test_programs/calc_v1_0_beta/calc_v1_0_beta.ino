/*
 * Lini Mestar
 * Calculator Mathematical Association of America Spring 2013
 * Version 1.0
 * this version adds subtracts multiplys and divides numbers
 * this version does not working with A,B,C, and D need FIX
 * need: time, pins
*/

//Libraries
#include <Keypad.h>
#include <LiquidCrystal.h>

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
boolean readNrsha=false,
  opAddition=false, opSubtract=false, 
  opMultiply=false, opDivide=false;
  
//LED Setup
byte ledPin = 13;
//Time Setup
unsigned long T0, T1;
unsigned int num1=0, num2=0;
/*
const int butonblah1=16;	//Decrease
const int butonblah2=17;        //Multiplication
const int butonblah3=18;	//Division
const int butonblah4=19;	//Radical
*/

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
  decChar();
  lcd.begin(16, 2);
  start();
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
  }  //for
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
   char key = keypad.getKey();
   if(key){
   if((key !='*')&&(key !='#')){   
     if(!readNrsha){
        num1=(num1*10)+int(key-'0');
        lcd.setCursor(0,1);
        lcd.print(num1);
      }else if(readNrsha){
       num2=(num2*10)+int(key-'0');
        //lcd.setCursor(8,1);
        lcd.print(num2);
      }
   }
    else if(key=='*'){
       lcd.print("+");
       readNrsha=true;
       opAddition=true;
     }
     else if(key=='#'){
         lcd.print("=");
           if(opAddition){
                 double sum=num1+num2;
                 lcd.print(sum);
                 delay(70000);
               }else if(opSubtract){
                  double dif=num1-num2;
                   lcd.print(dif);
                    delay(70000);
               }else if(opMultiply){
                   double prod=num1*num2;
                   lcd.print(prod);
                    delay(70000);
               }else if(opDivide){
                   double blah=num1/num2;
                   lcd.print(blah);
                   delay(70000);
               }
          lcd.setCursor(0,1);
          lcd.print("                ");
           num1=num2=0;
           readNrsha=false;
           opAddition=opSubtract=opMultiply=opDivide=false;
           } 
    }//if  */ should take out to before loop\*
   else if (key=='B'){  //not working
       lcd.print("-");
       readNrsha=true;
       opSubtract=true;
  }else if (key=='C'){  //not working
       lcd.print("*");
       readNrsha=true;
       opMultiply=true;
  }else if (key=='D'){  //not working
       lcd.print("/");
       readNrsha=true;
       opDivide=true;
       }
}  //loop

