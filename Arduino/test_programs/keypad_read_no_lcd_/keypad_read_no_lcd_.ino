//Lini Mestar
//Calculator Mathematical Association of America Spring 2013

//Libraries
#include <Keypad.h>
#include <EEPROM.h>  //need to work on
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

//Keypad Setup
byte rowPins[ROWS] = {2,3,4,5};
byte colPins[COLS] = {6,7,8,9};

//LED Setup
byte ledPin = 13;
//Time Setup
unsigned long T0, T1;

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

//initialize the Keypad library
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

byte a[3]={'x','x','x'};
byte Num2[2]={0,0};

void setup(){
  Serial.begin(9600);
  decChar();
  lcd.begin(16, 2);
  keypad.setDebounceTime(20);  //debounce
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
  digitalWrite(ledPin, HIGH);   // sets the LED on
  start();
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
  lcd.setCursor(0,1);
  lcd.print(">");
  lcd.blink();
  READ_KEYPAD();
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
  lcd.print("  A) ADD  C) DIVIDE ");
  lcd.setCursor(1,1);
  lcd.print("  B) SUB. D) MULTIPY ");
  for( int pos = 0; pos<22 ; pos++){
    lcd.scrollDisplayLeft();
    delay(550);
  }
}  //options

void progBar(){
 lcd.setCursor(0,1);
 lcd.print("                ");   
 
 for (int i = 0; i<16; i++)
 {
   for (int j=0; j<5; j++)
   {
      lcd.setCursor(i, 1);   
      lcd.write(j);
      delay(80);
   }
 }
}  //progBar

void READ_KEYPAD(){
  Serial.println("read from keypad");
  char key = keypad.getKey();
  keypad.waitForKey();
  if (key != NO_KEY){
    switch(key){
      delay(70);
      case 'A':
        key = NO_KEY;
        delay(50);
        getNum();
          //if
          Serial.println("BEFORE BREAK");
          //break;
        }  //switch
    }
    Serial.println("read from keypa23d");
    //Serial.print(key);
}  //READ_KEYPAD

void getNum(){
  char pkey = NO_KEY;
  pkey = keypad.getKey();
  lcd.clear();
  lcd.print("En%ter Num1:");
  for( unsigned i = 0 ; i<3 ; i++){
    if (pkey != NO_KEY){
      Serial.println(pkey);
      if(pkey == 'A' || pkey == 'B' || pkey == 'C' ||
          pkey == 'D' || pkey == '*' || pkey == '#' ){
            lcd.setCursor(0,1);
            lcd.print("*GET SERIOUS*");
            delay(500);
            lcd.clear();
            lcd.print("Enter Num1:");
          }else{
            Serial.println(pkey);
            delay(30);
            Serial.print("KEY!!");
            //lcd.print(key);
            //a[i]=key;
          }
          Serial.print("outside of if");
      }
    }
    Serial.print("outside of");
}
void Clear(){
 lcd.setCursor(1,0);
 lcd.write("                ");
 lcd.setCursor(1,0);
 lcd.setCursor(0,1);
 lcd.write("                ");
 lcd.setCursor(0,1); 
}  //Clear LCD

void loop(){
  T0=millis();
  //Serial.println("loop");
  
  T1=millis();
  //Serial.print(T1-T0);
}  //loop
