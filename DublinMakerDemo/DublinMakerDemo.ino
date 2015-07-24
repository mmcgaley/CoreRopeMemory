/* This is the Arduino logic for reading the bits from a 
 * demo of Core Rope Memory
 * it was written for the demo produced for Dublin Maker 2015
 * the demo uses 5 bits to encode ASCII capital letters
 * meaigs@timui.org */

/* #include statements for the quad alphanum display */
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_AlphaNum4 quadDisplay = Adafruit_AlphaNum4();

/* mux control pins */
int s0 = 8;
int s1 = 9;
int s2 = 10;
int s3 = 11;

/* enable pin and signal pin for mux */
int en = 12;
int sigPin = A0;

/* global bool for dealing with user moving probe */
boolean newChar = true;

/* display buffer for quadDisplay */
char displayBuffer[4] = {' ', ' ', ' ', ' '};

void setup() {
  //Serial.begin(9600); // setup serial monitor for debugging
  
  /* signal control pins for mux */
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  
  /* set enable pin LOW -- this enables the mux */
  pinMode(en, OUTPUT);
  digitalWrite(en, LOW);
  
  quadDisplay.begin(0x70);

  /* send some setup-y looking characters to the quad display */
  quadDisplay.writeDigitRaw(3, 0x0);
  quadDisplay.writeDigitRaw(0, 0xFFFF);
  quadDisplay.writeDisplay();
  delay(200);
  quadDisplay.writeDigitRaw(0, 0x0);
  quadDisplay.writeDigitRaw(1, 0xFFFF);
  quadDisplay.writeDisplay();
  delay(200);
  quadDisplay.writeDigitRaw(1, 0x0);
  quadDisplay.writeDigitRaw(2, 0xFFFF);
  quadDisplay.writeDisplay();
  delay(200);
  quadDisplay.writeDigitRaw(2, 0x0);
  quadDisplay.writeDigitRaw(3, 0xFFFF);
  quadDisplay.writeDisplay();
  delay(200);
  
  quadDisplay.clear();
  quadDisplay.writeDisplay();
}

void loop() {
  char bits[5]; // array to hold the bits read from the CRM
  readBits(bits);
  
  /* if all bits are 0, assume we're about to read a new 
   * character */
  if (bits[0] + bits[1] + bits[2] + bits[3] + bits[4] == 0) {
    newChar = true;
  }
  else {
    /* if we've read all zeros since the last time we got here */
    if (newChar) {
      delay(300); // give it a moment
      readBits(bits); // then read again
      
      /* if we get all zeros at this stage the user has had
       * some trouble making a good connection, keep reading 
       * till we have something */
      while(bits[0] + bits[1] + bits[2] + bits[3] + bits[4] == 0) {
        delay(100);
        readBits(bits);
      }
      
      /* convert the 5 bits to an ASCII char, and display
       * that to the quadDisplay -- this function scrolls
       * previously read characters across the display */
      displayChar(convertToAscii(bits));
      
      /* reset the flag so we don't get endless repetitions 
       * as long as the probe is held in place */
      newChar = false;
    } // end if new char
  } // end else all bits 0
} // end main loop

void readBits(char bits[]) {
  /* a bit hack-y, but we know it's 5 bits, and sizeof wasn't 
   * working as expected */
  for (int i = 0; i < 5; i++) {
    /* get the voltage of bit i */
    int voltage = readMux(i);
    
    /* if the voltage is dangerously high for the Arduino,
     * disable all mux pins, print an error, and loop forever */
    if (voltage > 1000) {
      digitalWrite(en, HIGH);
      while(1){
        displayChar('*');
        delay(100);
        displayChar('*');
        delay(100);
        displayChar('H');
        delay(100);
        displayChar('i');
        delay(100);
        displayChar('g');
        delay(100);
        displayChar('h');
        delay(100);
      }
    }
    
    if (voltage > 300) { 
      bits[i] = 1;
    }
    else {
      bits[i] = 0;
    }
  }
} // end function readBits

/* read voltage from specified channel on the mux
 * with thanks to 
 * bildr.org/2011/02/cd74hc4067-arduino/ */
int readMux(int channel) {
  int controlPin[] = {s3, s2, s1, s0}; // least sig. bit first
  
  int muxChannel[16][4] = {
    {0, 0, 0, 0}, // channel 0
    {0, 0, 0, 1}, // channel 1
    {0, 0, 1, 0}, // channel 2
    {0, 0, 1, 1}, // channel 3
    {0, 1, 0, 0}, // channel 4
    {0, 1, 0, 1}, // channel 5
    {0, 1, 1, 0}, // channel 6
    {0, 1, 1, 1}, // channel 7
    {1, 0, 0, 0}, // channel 8
    {1, 0, 0, 1}, // channel 9
    {1, 0, 1, 0}, // channel 10
    {1, 0, 1, 1}, // channel 11
    {1, 1, 0, 0}, // channel 12
    {1, 1, 0, 1}, // channel 13
    {1, 1, 1, 0}, // channel 14
    {1, 1, 1, 1}, // channel 15
  };
  
  for (int i = 0; i < 4; i++) {
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }
  
  int val = analogRead(sigPin);
  
  return val;
} // end function readMux

char convertToAscii(char bitArray[]) {
  char converted = '@'; // 01000000 in ASCII
  
  for (int i = 0; i < 5; i++) {
    /* bitwise OR the base character with each of the bits
     * we're interested in
     * (4 - i) because we're starting with the most significant
     * bit and working right */
    converted = converted | (bitArray[i] << (4 - i));
  }
  
  return converted;
}

/* display a character to the quad display
 * with thanks to Adafruit */
void displayChar(char c) {
  // scroll down display
  displayBuffer[0] = displayBuffer[1];
  displayBuffer[1] = displayBuffer[2];
  displayBuffer[2] = displayBuffer[3];
  displayBuffer[3] = c;
 
  // set every digit to the buffer
  quadDisplay.writeDigitAscii(0, displayBuffer[0]);
  quadDisplay.writeDigitAscii(1, displayBuffer[1]);
  quadDisplay.writeDigitAscii(2, displayBuffer[2]);
  quadDisplay.writeDigitAscii(3, displayBuffer[3]);
 
  // write it out!
  quadDisplay.writeDisplay();
}

