#include <Keypad.h>
#include <LiquidCrystal.h>
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
void setup(){
   keypad.setDebounceTime(200);  //keypad debounce
   lcd.begin(16, 2); 
}
void loop()
{
   delay(5);
   char key = keypad.getKey();
   if(key != NO_KEY){
      lcd.print(key);
   }
}
