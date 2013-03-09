#include <PS2kybd.h>

// Simple test program for new PS2Keyboard library
// Connect a PS2 keyboard to pins 3 & 4 (CLK and DATA respectively) and supply 5V to the keyboard
// For examples, see here: http://www.arduino.cc/playground/ComponentLib/Ps2mouse
// or                here: http://www.beyondlogic.org/keyboard/keybrd.htm
// That second article is a great place to start if you want to understand whats going on
//
// When you've compiled the code and uploaded it to the board, start a serial monitor at
// 9600bd.  Then press keys on your PS2 keyboard (the one connected to Arduino, not the one
// connected to your computer!) Try using <shift>, <ctrl> and <alt> keys
// and check that the caps_lock key sets the caps_lock light.
// Pressing <esc> key should reset the keyboard and you should see all 3 lights go on briefly.

// DigitalPin3 CLK  Leonardo:3 SS_Breakout:10.D0 Davinci:4.PD0 
// DigitalPin2 DATA Leonardo:2 SS_Breakout:9.D1 Davinci:5.PD1
// D2				PD1		SDA			SDA/INT1
// D3#				PD0		PWM8/SCL	OC0B/SCL/INT0

#define KBD_CLK_PIN 2
#define KBD_DATA_PIN 3

PS2Keyboard kybd;

int i=0;
int b;

void setup() {
  kybd.begin(KBD_DATA_PIN);

  Serial.begin(9600);
  delay(1000);
  // kybd.led(0x07);
}

#define is_printable(c) (!(c&0x80))   // don't print if top bit is set

boolean  rel=0;
boolean  caps=0;
boolean  alt_r=0;
boolean  alt_l=0;
boolean  shift_r=0;
boolean  shift_l=0;
boolean  ctrl_r=0;
boolean  ctrl_l=0;
boolean  shift_release_press=false;
boolean  shift_press_release=false;
boolean  kanji=false;

byte  sendkey=0;


void loop() {

  if(b=kybd.available()) {

    byte       r = kybd.read_extra();
    // Serial.print(b);
    // Serial.print(" ");
    // Serial.print(r,HEX);
    // Serial.println("");

    byte      t;
    byte      m = kybd.modifier();
    byte      l = kybd.lock();
    // byte       c = kybd.rawread();

    word       c = kybd.readext();
    // word       c = kybd.readuid();
    // byte      c = kybd.rawread();
    // delay(100);
    // kybd.led(l);
    i++;

    rel = c&0x8000?true:false;
    caps = c&0x4000?true:false;
    alt_r = c&0x2000?true:false;
    alt_l = c&0x1000?true:false;
    shift_r = c&0x0800?true:false;
    shift_l = c&0x0400?true:false;
    ctrl_r = c&0x0200?true:false;
    ctrl_l = c&0x0100?true:false;

    sendkey=0x00ff&c;
    shift_release_press=false;
    shift_press_release=false;
    kanji = false;
    if(shift_r|shift_l) {  // [SHIFT] pressed
      switch(sendkey) {
        case 0x60: { // [`~] -> [^~]
          kanji=true;
          sendkey=0x3d; break;
        }
        case 0x32: { // [2@] -> [@`]
          sendkey=0x5b; shift_release_press=true; break;
        }
        case 0x36: { // [6^] -> [^~]
          sendkey=0x3d; shift_release_press=true; break;
        }
        case 0x37: { // [7&] -> [6&]
          sendkey=0x36; break;
        }
        case 0x38: { // [8*] -> [:*]
          sendkey=0x27; break;
        }
        case 0x39: { // [9(] -> [8(]
          sendkey=0x38; break;
        }
        case 0x30: { // [0)] -> [9)]
          sendkey=0x39; break;
        }
        case 0x5b: { // [[{] -> [[{]
          sendkey=0x5d; break;
        }
        case 0x5d: { // []}] -> []}]
          sendkey=0x5c; break;
        }
        case 0x3b: { // [;:] -> [:*]
          sendkey=0x27; shift_release_press=true; break;
        }
        case 0x27: { // ['"] -> [2"]
          sendkey=0x32; break;
        }
        case 0x3d: { // [=+] -> [;+]
          sendkey=0x3b; break;
        }
        case 0x2d: { // [-_] -> [¥_]
          sendkey=0x2d; break;
        }
        default: {
        }
      }
    } else {  // [SHIFT] no pressed
      switch(sendkey) {
        case 0x60: { // [`~] -> [@`]
          kanji=true;
          sendkey=0x5b; shift_press_release=true; break;
        }
        case 0x3d: { // [=+] -> [-=]
          sendkey=0x2d; shift_press_release=true; break;
        }
        case 0x27: { // ['"] -> [7']
          sendkey=0x37; shift_press_release=true; break;
        }
        case 0x5b: { // [[{] -> [[{]
          sendkey=0x5d; break;
        }
        case 0x5d: { // []}] -> []}]
          sendkey=0x5c; break;
        }
        default: {
        }
      }
    }


// send usb keycode



    if (sendkey) {
      if (kanji && (alt_l|alt_r)) { // ALT+' or ALT+~ -> toggle Kanji
        sendkey=c;
      }
      if (shift_release_press) {
        if (shift_r) Keyboard.release(KEY_RIGHT_SHIFT);
        if (shift_l) Keyboard.release(KEY_LEFT_SHIFT);
      }
      if (shift_press_release) {
        Keyboard.press(KEY_RIGHT_SHIFT);
      }
      if (rel) {
        Keyboard.release(sendkey);
      } else {
        Keyboard.press(sendkey);
      }
      if (shift_press_release) {
        Keyboard.release(KEY_RIGHT_SHIFT);
      }
      if (shift_release_press) {
        if (shift_r) Keyboard.press(KEY_RIGHT_SHIFT);
        if (shift_l) Keyboard.press(KEY_LEFT_SHIFT);
      }
    }



    Serial.print(i);
    Serial.print(" L:");
    Serial.print(l,HEX);
    Serial.print(" M:");
    Serial.print(m,HEX);
    Serial.print("  ");
    if (caps) Serial.print("[CAPS]");
    if (alt_r||alt_l) Serial.print("[ALT]");
    if (shift_r||shift_l) Serial.print("[SHIFT]");
    if (ctrl_r||ctrl_l) Serial.print("[CTRL]");
    if (shift_release_press) Serial.print("[SHIFT-REL-PRESS]");
    if (shift_press_release) Serial.print("[SHIFT-PRESS-RELEASE]");
    Serial.print(sendkey,HEX);
    Serial.print("");
    Serial.print(c,HEX);
    Serial.println("");

  } 
}
