/*
 * Lini Mestar 
 * Matt Remick for Taylor Series & Cordic method Functions
 * Calculator Mathematical Association of America Spring 2013
 * Version 1.0c
 * THIS VERSION  + - * / Tsin Tcos Tsin Csin Ccos Ctan log10 sqrt
 * FIXED: COMPUTES PI BY PRESSING THE (*) BUTTON
     - KNOWN BUG: DOESN'T WORK WITH TANGENT
 * FIXED: TAKE MORE THAN 4 DIGITS (MAX IS 10)
 * FIXED: NO MORE "JUMP" FOR USER
 * FIXED: CHECKS FOR VALID INPUT( NO INPUT)
 * FIXED: AFTER #, DOES NOT BLINK UNTIL NEW OPERATION
 * FIXED: DEBOUNCING KEYS
 * FIXED: DOES NOT OUTPUT (-) VALUES
 * FIXED: PRECISION lcd.print(1.23456, 4) gives "1.2346"
 * FIXED: DOES NOT SHOW TIME TOOK TO COMPLETE
 * FIXED: DOES NOT USE EXTRA PINS
 * FIXED: THIS VERSION DOES NOT WORKING WITH A,B,C & D
 * FIXED: BUTTON BOUNCING
 * FIXED: SHOWING 122 INSTEAD 12
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
#define QHOLD 2000
#define LCDIGITS 13
#define DEFPREC 50

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
  opCsin=false, opCcos=false, opCtan=false,
  opTsin=false, opTcos=false, opTtan=false,
  opNLog=false, opLogBTen=false, opSQRT=false, opE=false;
  
boolean piee = false;

//Time Setup
unsigned long T0, T1;
unsigned long tT0, tT1;

//Calculator constants
const double pi = 3.14159265358979323846;
const double e  = 2.718281828459045;
int counter = 0;
int keepTrack = 0;

//Numbers Inputed
int long num1=0, num2=0;
int long num3=0;

//Initialize buttons 10x2
Bounce bouncer  = Bounce( BUTTON0 , 25 );
Bounce bouncer1 = Bounce( BUTTON1 , 25 );
Bounce bouncer2 = Bounce( BUTTON2 , 25 );
Bounce bouncer3 = Bounce( BUTTON3 , 25 );
Bounce bouncer4 = Bounce( BUTTON4 , 25 );
Bounce bouncer5 = Bounce( BUTTON5 , 25 );
Bounce bouncer6 = Bounce( BUTTON6 , 25 );
Bounce bouncer7 = Bounce( BUTTON7 , 25 );
Bounce bouncer8 = Bounce( BUTTON8 , 25 );
Bounce bouncer9 = Bounce( BUTTON9 , 25 );

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
byte disLike[8] = {
  B00000,
  B11111,
  B11001,
  B11001,
  B11011,
  B00100,
  B00100,
  B00000
};
byte squared[8] = {
  B01100,
  B00010,
  B00100,
  B01000,
  B01110,
  B00000,
  B00000,
};
byte baseTen[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B10010,
  B10101,
  B10101,
  B10010
};
byte squareRoot[8] = {
  B00111,
  B00100,
  B00100,
  B00100,
  B00100,
  B10100,
  B01100,
  B00100
};
byte pipi[8] = {
  B00000,
  B11111,
  B01010,
  B01010,
  B01010,
  B01010,
  B01010,
  B00000
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

double angles[] =  {  //len = 28 //arctangents
             0.78539816339745,   0.46364760900081,
             0.24497866312686,   0.12435499454676,
             0.06241880999596,   0.03123983343027,
             0.01562372862048,   0.00781234106010,
             0.00390623013197,   0.00195312251648,
             0.00097656218956,   0.00048828121119,
             0.00024414062015,   0.00012207031189,
             0.00006103515617,   0.00003051757812,
             0.00001525878906,   0.00000762939453,
             0.00000381469727,   0.00000190734863,
             0.00000095367432,   0.00000047683716,
             0.00000023841858,   0.00000011920929,
             0.00000005960464,   0.00000002980232,
             0.00000001490116,   0.00000000745058   };
  
double Kvalues[] = {  //len = 24  //k values
             0.70710678118655,   0.63245553203368,
             0.61357199107790,   0.60883391251775,
             0.60764825625617,   0.60735177014130,
             0.60727764409353,   0.60725911229889,
             0.60725447933256,   0.60725332108988,
             0.60725303152913,   0.60725295913894,
             0.60725294104140,   0.60725293651701,
             0.60725293538591,   0.60725293510314,
             0.60725293503245,   0.60725293501477,
             0.60725293501035,   0.60725293500925,
             0.60725293500897,   0.60725293500890,
             0.60725293500889,   0.60725293500888   };
                                      

void setup(){
  Serial.begin(9600);
  keypad.setDebounceTime(150);
  decChar();
  initialButtons();
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Welcome to");
  lcd.setCursor(0,1);
  lcd.print("   Calculator");
  lcd.setCursor(13,1);
  lcd.write(6);
  delay(QHOLD);
  lcd.clear();
  start();
  lcd.setCursor(0,0);
  lcd.blink();
}  //setup

void decChar(){
  //Setup LCD Special Characters
  lcd.createChar(0, p20);
  lcd.createChar(1, p40);
  lcd.createChar(2, p60);
  lcd.createChar(3, p80);
  lcd.createChar(4, p100);
  lcd.createChar(5, like);
  lcd.createChar(6, squared);
  lcd.createChar(7, baseTen);
  lcd.createChar(8,squareRoot);
  lcd.createChar(9,pipi);
  lcd.createChar(10,disLike);
}  //decChar

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
  delay(QHOLD);
  lcd.clear();
  options();
  lcd.clear();
}  //start

void options(){
  lcd.setCursor(1,0);
  lcd.print("  A)ADD  C)MULTIPY  B1)Tsin");
  lcd.setCursor(1,1);
  lcd.print("  B)SUB. D)DIVIDE   B6)Csin");
  scroll();
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("  B2)Tcos  B3)Ttan  B4)Log(  B5)");
  lcd.write(8);
  lcd.print("(");
  lcd.setCursor(1,1);
  lcd.print("  B7)Ccos  B8)Ctan    *B=BUTTON*");
  scroll();
}  //options

void scroll(){
  for( int pos = 0; pos<26 ; pos++){
  lcd.scrollDisplayLeft();
  delay(225);
  }
}  //scroll

void progBar(){
 lcd.setCursor(0,1);
 lcd.print("                ");
 for (int i = 0; i<16; i++){
   for (int j=0; j<5; j++){
      lcd.setCursor(i, 1);   
      lcd.write(j);
      delay(50);
   }
 }
}  //progBar

// CHECKING IF BUTTONS PRESSED
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
   /******************************
   * KEYPAD READING W/ DEBOUNCING
   *******************************/
   if(key != NO_KEY){
     if((key !='*')&&(key !='#')&&(key !='A')
         &&(key !='B')&&(key !='C')&&(key !='D'))
       {
       if(!beenHere){
          num1 = (num1*10) + int(key-'0');
          lcd.setCursor(0,0);
          lcd.print(num1);
          counter++;
        }else if(beenHere && opLogBTen){
          lcd.setCursor(5,0);
          num2 = (num2*10) + int(key-'0');
          lcd.print(num2);
          keepTrack++;
        }else if(beenHere && opSQRT){
          lcd.setCursor(2,0);
          num2 = (num2*10) + int(key-'0');
          lcd.print(num2);
          keepTrack++;
        }else if( (beenHere && opNLog)
              ||  (beenHere && opE)  )
             {
               lcd.setCursor(3,0);
               num2 = (num2*10) + int(key-'0');
               lcd.print(num2);
               keepTrack++;
        }else if( (beenHere && opTsin)
                || (beenHere && opTcos) 
                || (beenHere && opCtan)
                || (beenHere && opCcos)
                || (beenHere && opCsin)
                || (beenHere && opTtan) )
                {
                  lcd.setCursor(counter+5,0);
                  num3 = (num3*10) + int(key-'0');
                  lcd.print(num3);
                  keepTrack++;
        }else if(beenHere){
          num2 = (num2*10) + int(key-'0');
          lcd.setCursor(counter+1,0);
          lcd.print(num2);
          keepTrack++;
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
         lcd.write(9);
         piee=true;
         if( (beenHere && opTsin)
            || (beenHere && opTcos) 
            || (beenHere && opCtan)
            || (beenHere && opCcos)
            || (beenHere && opCsin)
            || (beenHere && opTtan) )
            {
              num3*=pi;
            }else if( 
                  (beenHere && opNLog)
              ||  (beenHere && opE)
              ||  (beenHere) 
              ||  (beenHere && opSQRT)
              ||  (beenHere && opLogBTen) )
             {
               num2*=pi;
             }
       }
       else if(key=='#'){
         if(keepTrack == 0){
           lcd.noBlink();
           lcd.setCursor(0,1);
           lcd.print(" bad input ");
           lcd.write(10);
           delay(QHOLD);
           goto endThis;
         }else{
           lcd.noBlink();
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
             }else if(opCsin){
               if(num1==0){
                 if(piee==true){
                   double x=C_SIN(double(num3), DEFPREC);
                   Serial.println(x);
                   if(x<0){
                    x=ceil(x); 
                   }else{
                    x=floor(x);  
                   }
                   lcd.print(x,0);
                   delay(DELAY);
                   showTime();
                 }else{
                   lcd.print(C_SIN(double(num3), DEFPREC),LCDIGITS);
                   delay(DELAY);
                   showTime();
                 }
               }else{
                 if(piee==true){
                   double x=C_SIN(double(num3), DEFPREC);
                   if(x<0){
                    x=ceil(x); 
                   }else{
                    x=floor(x);  
                   }
                   lcd.print(x,0);
                   delay(DELAY);
                   showTime();
                 }else{
                   lcd.print(C_SIN(double(num3), num1),LCDIGITS);
                   delay(DELAY);
                   showTime();
                 }
               }
             }else if(opCcos){
               if(num1==0){
                 if(piee==true){
                   double x=C_COS(double(num3), DEFPREC);
                   lcd.print(x,0);
                   delay(DELAY);
                   showTime();
                 }else{
                   double x=C_COS(double(num3), DEFPREC);
                   //x=floor(x);
                   lcd.print(x,LCDIGITS);
                   delay(DELAY);
                   showTime();
                 }
               }else{
                 if(piee==true){
                   lcd.print(C_COS(double(num3), num1),0);
                   delay(DELAY);
                   showTime();
                 }else{
                   lcd.print(C_COS(double(num3), num1),LCDIGITS);
                   delay(DELAY);
                   showTime();
                 }
               }
             }else if(opTtan){
               if(num1==0){
                   lcd.print(T_TAN(double(num3), DEFPREC),LCDIGITS);
                   delay(DELAY);
                   lcd.clear();
                   lcd.setCursor(0,0);
                   lcd.print("Time:");
                   lcd.setCursor(0,1);
                   lcd.print(tT1-tT0);
                   lcd.print(" Milli Sec.");
                   delay(DELAY);
                 }else{
                   lcd.print(T_TAN(double(num3), num1),LCDIGITS);
                   delay(DELAY);
                   lcd.clear();
                   lcd.setCursor(0,0);
                   lcd.print("Time:");
                   lcd.setCursor(0,1);
                   lcd.print(tT1-tT0);
                   lcd.print(" Milli Sec.");
                   delay(DELAY);
                 }
             }else if(opTsin){
               if(num1==0){
                 if(piee==true){
                   double x=T_SIN(double(num3), DEFPREC);
                   if(x<0){
                    x=ceil(x); 
                   }else{
                    x=floor(x);  
                   }
                   lcd.print(x,0);
                   delay(DELAY);
                   showTime();
                 }else{
                   lcd.print(T_SIN(double(num3), DEFPREC),LCDIGITS);
                   delay(DELAY);
                   showTime();
                 }
               }else{
                 if(piee==true){
                   double x=T_SIN(double(num3), num1);
                   if(x<0){
                    x=ceil(x); 
                   }else{
                    x=floor(x);  
                   }
                   lcd.print(x,0);
                   delay(DELAY);
                   showTime();
                 }else{
                   lcd.print(T_SIN(double(num3), num1),LCDIGITS);
                   delay(DELAY);
                   showTime();
                 }
               }
             }else if(opTcos){
               if(num1==0){
                 if(piee==true){
                   double x=T_COS(double(num3), DEFPREC);
                   x=floor(x);
                   lcd.print(x,0);
                   delay(DELAY);
                   showTime();
                 }else{
                   lcd.print(T_COS(double(num3), DEFPREC),LCDIGITS);
                   delay(DELAY);
                   showTime();
                 }
               }else{
                 if(piee==true){
                   double x=T_COS(double(num3), num1);
                   x=floor(x);
                   lcd.print(x,0);
                   delay(DELAY);
                   showTime();
                 }else{
                   lcd.print(T_COS(double(num3), num1),LCDIGITS);
                   delay(DELAY);
                   showTime();
                 }
               }
             }else if(opCtan){
               if(num1==0){
                   lcd.print(C_TAN(double(num3), DEFPREC),LCDIGITS);
                   delay(DELAY);
                   lcd.clear();
                   lcd.setCursor(0,0);
                   lcd.print("Time:");
                   lcd.setCursor(0,1);
                   lcd.print(tT1-tT0);
                   lcd.print(" Milli Sec.");
                   delay(DELAY);
                 }else{
                   lcd.print(C_TAN(double(num3), num1),LCDIGITS);
                   delay(DELAY);
                   lcd.clear();
                   lcd.setCursor(0,0);
                   lcd.print("Time:");
                   lcd.setCursor(0,1);
                   lcd.print(tT1-tT0);
                   lcd.print(" Milli Sec.");
                   delay(DELAY);
                 }
             }else if( opLogBTen ){
               lcd.print(log(double(num2))/log(10),LCDIGITS);
               delay(DELAY);
             }else if( opNLog ){
               lcd.print(log(double(num2)),LCDIGITS);
               delay(DELAY);
             }else if( opSQRT ){
               lcd.print(sqrt(double(num2)),LCDIGITS);
               delay(DELAY);
             }else if( opE ){
               lcd.print(pow(e,double(num2)),LCDIGITS);
               delay(DELAY);
             }
             endThis:
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.blink();
            num1= num2= num3= 0;
            beenHere=false;
            opAddition= opSubtract= false;
            opMultiply=opCsin= false;
            opDivide=opCcos=false;
            opTtan=opTsin=opTcos=opCtan= false;
            opNLog=opLogBTen=opSQRT=opE=false;
            piee=false;counter=0;keepTrack=0;
       }  //blahere
       }
   /***************************************
   * EXTERNAL BUTTON READING W/ DEBOUNCING
   ****************************************/
   }else if ( bouncer.read() ){
     delay(250);
     lcd.print("Tsin(");
     beenHere=true;
     opTsin=true;
   }else if ( bouncer1.read() ){
     delay(250);
     lcd.print("Tcos(");
     beenHere=true;
     opTcos=true;
   }else if ( bouncer2.read() ){
     delay(250);
     lcd.print("Ttan(");
     beenHere=true;
     opTtan=true;
   }else if ( bouncer3.read() ){
     delay(250);
     lcd.print("log");
     lcd.setCursor(3,0);
     lcd.write(7);
     lcd.setCursor(4,0);
     lcd.print("(");
     beenHere=true;
     opLogBTen=true;
   }else if ( bouncer5.read() ){
     delay(250);
     lcd.print("Csin(");
     beenHere=true;
     opCsin=true;
   }else if ( bouncer6.read() ){
     delay(250);
     lcd.print("Ccos(");
     beenHere=true;
     opCcos=true;
   }else if ( bouncer7.read() ){
     delay(250);
     lcd.print("Ctan(");
     beenHere=true;
     opCtan=true;
   }else if ( bouncer4.read() ){
     delay(250);
     lcd.setCursor(0,0);
     lcd.write(8);
     lcd.setCursor(1,0);
     lcd.print("(");
     beenHere=true;
     opSQRT=true;
   }
}  //loop

void sum(){
  T0 = millis();
  double sum=num1+num2;
  T1 = millis();
  lcd.print(sum,0);
  delay(DELAY);
}  //sum

void subtract(){
 T0 = millis();
 double dif=num1-num2;
 T1 = millis();
 lcd.print(dif,0);
 delay(DELAY);
}  //subtract

void multiply(){
  T0 = millis();
  double prod=num1*num2;
  T1 = millis();
  lcd.print(prod,0);
  delay(DELAY);
}  //multiply

void divide(){
  T0 = millis();
  float blah=double(num1)/double(num2);
  T1 = millis();
  lcd.print(blah,4);
  delay(DELAY);
}  //divide

//taylor Series to calculate cosine
double T_COS(double x,int degree){
  T0 = millis();
  int i = 0;
    double accumulation = 0;
    int quadrant = 0;
    int k = 0;
    double pi = 3.14159;

    int cosInputArray[4] = {1,0,-1,0};
     if (x > 1.57079) {
         k = floor(x/(pi/2));
         quadrant = 1+(k % 4);
     }
     else quadrant = 1;
     if (x > 1.57079) {
         x = referenceAngle(x);
     }

    while (i < degree) {
        int input = cosInputArray[i%4];
        accumulation += input*((pow(x, i))/factorial(i));
        i++;
    }
     if (quadrant == 2 || quadrant == 3) {
         accumulation *= -1;
     }
    T1 = millis();
    return accumulation;
}  //T_COS

//taylor Series to calculate sine
double T_SIN(double x, int degree){
  T0 = millis();
  int i = 0;
    double accumulation = 0;
    int quadrant = 0;
    int k = 0;
    int sinInputArray[4] = {0,1,0,-1};
    if (x > 1.57079) {
     k = floor(x/(pi/2));
     quadrant = 1+(k % 4);
    }
    else quadrant = 1;
    if (x > 1.57079) {
     x = referenceAngle(x);
    }
    while (i < degree) {
    int input = sinInputArray[i%4];
    accumulation += input*((pow(x, i))/factorial(i));
    i++;
    }
    if (quadrant == 3 || quadrant == 4) {
     accumulation *= -1;
    }
    T1 = millis();
    return accumulation;
}  //T_SIN
//taylor Series to calculate tangent
double T_TAN(double x, int degree){
    tT0 = millis();
    double tangent = 0;

    tangent = (T_SIN(x, degree)/T_COS(x, degree));
    tT1 = millis();
    return tangent;
}
//cordic to calculate cosine
double C_COS(double input, int degree){
  T0 = millis();
  double kn;
  double v[] = {1,0};
  double powerOfTwo;
  double angle;
  int i = 0;
  int sigma;
  double factor;
  double temp_v0;
  int quadrant;
  int k;
  
  if (input > 1.57079) {
      k = floor(input/(pi/2));
      quadrant = 1+(k % 4);
  }
  
  else quadrant = 1;
  
  if (input > 1.57) {
      input = referenceAngle(input);
  }
  
  if (degree > 24) {
      kn = Kvalues[23];
  }
  
  else kn = Kvalues[degree];
      
  angle = angles[0];
  powerOfTwo = 1;
  
  while (i < degree) {
      
      if (input < 0) {
          sigma = -1;
      }
      
      else {
          sigma = 1;
      }
  
  factor = sigma * powerOfTwo;
              
  temp_v0 = v[0];
  v[0] = (1*v[0]) + ((-1)*(factor*v[1]));
  
  v[1] = (factor*temp_v0) + (1*v[1]);
  
  input -= sigma * angle;
      
  powerOfTwo = powerOfTwo / 2.0;
  
  if (i+2 > 27) {
      angle = angle / 2.0;
  }
  
  else angle = angles[i+1];
  
  i++;
  }
  
  v[0] *= kn;
  
  if (quadrant == 2 || quadrant == 3) {
      v[0] *= -1;
  }
  T1 = millis();
  return v[0];
}  //C_COS

//cordic to calculate sine
double C_SIN(double input, int degree){
  T0 = millis();
  double kn;
  double v[] = {1,0};
  double powerOfTwo;
  double angle;
  int i = 0;
  int sigma;
  double factor;
  double temp_v0;
  int quadrant;
  int k;
  
  if (input > 1.57079) {
      k = floor(input/(pi/2));
      quadrant = 1+(k % 4);
  }
  
  else quadrant = 1;
  
  if (input > 1.57) {
      input = referenceAngle(input);
  }
  if (degree > 24) {
      kn = Kvalues[23];
  }
  
  else kn = Kvalues[degree];
  
  angle = angles[0];
  powerOfTwo = 1;
  
  while (i < degree) {
      
      if (input < 0) {
          sigma = -1;
      }
      
      else {
          sigma = 1;
      }

      factor = sigma * powerOfTwo;
      
      temp_v0 = v[0];
      
      v[0] = (1*v[0]) + ((-1)*(factor*v[1]));
      
      v[1] = (factor*temp_v0) + (1*v[1]);
      
      input -= sigma * angle;
      
      powerOfTwo = powerOfTwo / 2.0;
      
      if (i+2 > 27) {
          angle = angle / 2.0;
      }
      
      else angle = angles[i+1];
      
      i++;
  }
  
  v[1] *= kn;
  
  if (quadrant == 3 || quadrant == 4) {
      v[1] *= -1;
  }  
  T1 = millis();
  return v[1];
}  //C_SIN

//cordic to calculate tangent
double C_TAN(double input, int degree){
    tT0 = millis();
    double tangent;

    tangent = C_SIN(input, degree) / C_COS(input, degree);
    tT1 = millis();
    return tangent;
    
}

double factorial(int input){
  double output = 1;
  for( double i = 2; i <= input; ++ i ) {
      output *= i;
  }return output;
}  //factorial

double referenceAngle(double x){
  int k,quadrant = 0;
  double referenceAngle = 0.0;
  k = floor(x/(pi/2));
  quadrant = k % 4;
  if (quadrant == 0 || quadrant == 2){
    referenceAngle = x - ((pi/2)*k);
  }else{referenceAngle = (pi/2) - (x - ((pi/2)*k));}
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
