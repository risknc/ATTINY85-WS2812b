#include <Adafruit_NeoPixel.h>
#include <SM.h>
//#include <State.h>

/*The color palette initially should support the following:

White:	(255,255,255).
Orange: (255,102,0) 
Deep Red: (255,0,0)
Green:	(0,255,0)
Blue:  (0,128,255)
Purple: (128,0,255)
Yellow:  (255,255,0)

And support the speeds of Slow, Medium, Fast for each color.

To speed up the transition rate do:

To speed up/slow down the flash rates do:

This gives up the following combinations for the state machine.  
0    OFF   
1    ON WHITE
2    SLOW WHITE
3    MEDIUM WHITE
4    ON ORANGE
5    SLOW ORANGE
6    MEDIUM ORANGE
7    ON RED
8    SLOW RED
9    FAST RED
10.  ON GREEN   
11.  SLOW GREEN
12.  MEDIUM GREEN 

Next set of colors are for fun.

13.   FAST BLUE
14.   FAST YELLOW
15.   FAST PURPLE

The color transition effect are disabled, can be added later.

State S1(){
//low white fade in/out 
//Fadeup
for (uint16_t b = 5; b< 30; b++) {
 colorFast(strip.Color(b,b,b),15);
}
stateread();

//Fadedown  
for (uint16_t b = 30; b> 5; b=b-1) {
  colorFast(strip.Color(b,b,b),8);
}
stateread();
  
 State S3(){
 // low fade red
 for (uint16_t b = 5; b< 30; b++) {
   colorFast(strip.Color(b,0,0),15);
 }
 stateread();
 for (uint16_t b = 30; b> 5; b=b-1) {
   colorFast(strip.Color(b,0,0),8);
 }
 stateread();

}

#TODO

Need to get more accurate color representation

Checkout example at:

https://learn.adafruit.com/downloads/pdf/neopixel-ring-clock.pdf

Need to get a better & faster transition.

Need to experiment with more subtle flashing effect.

*/

SM Simple(S1);

#define D1 0
#define D2 1
#define D3 2
#define D4 3
#define NUM_LEDS 12 //60LED per strip
#define DATA_PIN 4 //output pin on ATTiny85
//#define BTN_PIN 0 //input pin on ATTiny85
//#define BTN_DELAY 250 //add delay for debounce
#define NUM_PATTERNS 16 //patterns avail
#define CTR_THRESH 16

uint8_t j = 0;
uint8_t pattern=1;
//uint8_t buttonState=0;
uint8_t lastPix=0; 
uint8_t myPix=0;
uint8_t direction=1;
uint8_t counter=0;
uint8_t colors[3];
uint32_t setColor=0;
unsigned long mark;
  boolean flag1=0;
  boolean flag2=0;
  boolean flag3=0;
  boolean flag4=0;

// Uses GRB instead of RGB 
// Uses 800Khz datastream

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);

void colorFast(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
  delay(wait);
}

void setup(){
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D4, INPUT);
  // Initialize with medium fast white.
  strip.begin();
  Simple.Set(S2);  
/*  for (uint16_t b = 1; b< 15; b++) {
    colorFast(strip.Color(b,b,b),50);
  }
  for (uint16_t b = 15; b> 1; b=b-1) {
    colorFast(strip.Color(b,b,b),25);
  }
*/
}

// Colorfast is a function which iterates through all the pixels in the strip, wait is delay in milliseconds.

void stateread() {
  flag1 = digitalRead(D1);
  flag2 = digitalRead(D2);
  flag3 = digitalRead(D3);
  flag4 = digitalRead(D4);
  
  if(!flag1&&!flag2&&!flag3&&!flag4) Simple.Set(S0);
  if(flag1&&!flag2&&!flag3&&!flag4) Simple.Set(S1);
  if(!flag1&&flag2&&!flag3&&!flag4) Simple.Set(S2);
  if(flag1&&flag2&&!flag3&&!flag4) Simple.Set(S3);
  
  if(!flag1&&!flag2&&flag3&&!flag4) Simple.Set(S4);
  if(flag1&&!flag2&&flag3&&!flag4) Simple.Set(S5);
  if(!flag1&&flag2&&flag3&&!flag4) Simple.Set(S6);
  if(flag1&&flag2&&flag3&&!flag4) Simple.Set(S7);
  
  if(!flag1&&!flag2&&!flag3&&flag4) Simple.Set(S8);
  if(flag1&&!flag2&&!flag3&&flag4) Simple.Set(S9);
  if(!flag1&&flag2&&!flag3&&flag4) Simple.Set(S10);
  if(flag1&&flag2&&!flag3&&flag4) Simple.Set(S11);
  
  if(!flag1&&!flag2&&flag3&&flag4) Simple.Set(S12);
  if(flag1&&!flag2&&flag3&&flag4) Simple.Set(S13);
  if(!flag1&&flag2&&flag3&&flag4) Simple.Set(S14);
  if(flag1&&flag2&&flag3&&flag4) Simple.Set(S15);
}

void loop(){
  EXEC(Simple);
}

State S0(){
//Wipe all colors.	
    strip.show();
    for (uint16_t b = 1; b< 15; b++) {
    colorFast(strip.Color(0,0,0),15);
    delay(10);
  }
  stateread();
  for (uint16_t b = 15; b> 1; b=b-1) {
    colorFast(strip.Color(0,0,0),8);
    delay(10);
  }
}

State S1(){
//Bright Solid White 255,255,255
    for (uint16_t b = 1; b< 15; b++) {
    colorFast(strip.Color(255,255,255),15);
    delay(10);
  }
  stateread();
  for (uint16_t b = 15; b> 1; b=b-1) {
    colorFast(strip.Color(255,255,255),8);
    delay(10);
  }
  stateread();
}


State S2(){
 //Low Slow White 30,30,30
   for (uint16_t b = 5; b< 30; b++) {
    colorFast(strip.Color(b,b,b),100);
  }
  stateread();
  for (uint16_t b = 30; b> 5; b=b-1) {
    colorFast(strip.Color(b,b,b),50);
  }
  stateread();
}

State S3(){
//Medium Fast White 60,60,60 
  for (uint16_t b = 1; b< 15; b++) {
    colorFast(strip.Color(b,b,b),50);
  }
  stateread();
  for (uint16_t b = 15; b> 1; b=b-1) {
    colorFast(strip.Color(b,b,b),25);
  }
  stateread();
}

State S4(){
//Bright Solid Orange 255,102,0
   for (uint16_t b = 1; b< 15; b++) {
    colorFast(strip.Color(128,51,0),15);
    delay(10);
  }
  stateread();
  for (uint16_t b = 15; b> 1; b=b-1) {
    colorFast(strip.Color(128,51,0),8);
    delay(10);
  }
  stateread();
}

State S5(){
//Low Slow Orange 255,102,0
   for (uint16_t b = 1; b< 15; b++) {
    colorFast(strip.Color( b * 4 , b * 2 ,0),100);
  }
  stateread();
  for (uint16_t b = 15; b> 1; b=b-1) {
    colorFast(strip.Color( b * 4 , b * 2 , 0),50);
  }
  stateread();
}
State S6(){
//Medium Fast Orange 255,102,0
   for (uint16_t b = 1; b< 15; b++) {
    colorFast(strip.Color(b * 4 , b * 2 , 0 ),50);
  }
  stateread();
  for (uint16_t b = 15; b> 1; b=b-1) {
    colorFast(strip.Color(b * 4, b * 2 , 0),25);
  }
  stateread();
}

State S7(){
//Bright Solid Red 255,0,0
    for (uint16_t b = 1; b< 15; b++) {
    colorFast(strip.Color(255,0,0),15);
    delay(10);
  }
  stateread();
  for (uint16_t b = 15; b> 1; b=b-1) {
    colorFast(strip.Color(255,0,0),8);
    delay(10);
  }
  stateread();
}

State S8(){
//Low Slow Red 255,0,0
  for (uint16_t b = 1; b< 15; b++) {
    colorFast(strip.Color( b, 0, 0),100);
  }
  stateread();
  for (uint16_t b = 15; b> 1; b=b-1) {
    colorFast(strip.Color( b, 0, 0),50);
  }
  stateread();

}
State S9(){
//Fast Red 255,0,0
  for (uint16_t b = 128; b< 15; b++) {
    colorFast(strip.Color( b, 0, 0),25);
  }
  stateread();
  for (uint16_t b = 128; b> 1; b=b-1) {
    colorFast(strip.Color( b, 0, 0),15);
  }
  stateread();
}
State S10(){
//Bright Solid Green 0,255,0 
   for (uint16_t b = 1; b< 15; b++) {
    colorFast(strip.Color( 0, 128, 0),15);
    delay(10);
  }
  stateread();
  for (uint16_t b = 15; b> 1; b=b-1) {
    colorFast(strip.Color( 0, 128, 0),8);
    delay(10);
  }
  stateread();
}

State S11(){
//Low Slow Green 0,255,0 
  for (uint16_t b = 1; b< 15; b++) {
    colorFast(strip.Color( 0, b, 0),100);
  }
  stateread();
  for (uint16_t b = 15; b> 1; b=b-1) {
    colorFast(strip.Color( 0, b, 0),50);
  }
  stateread();
}    

State S12(){
//Medium Fast Green 0,255,0 
     for (uint16_t b = 1; b< 15; b++) {
    colorFast(strip.Color( 0 , b, 0),50);
  }
  stateread();
  for (uint16_t b = 15; b> 1; b=b-1) {
    colorFast(strip.Color( 0 , b, 0),25);
  }
  stateread();
}

State S13(){
//Medium Fast Blue 0,128,255
    for (uint16_t b = 1; b< 15; b++) {
    colorFast(strip.Color( 0, b, 2 * b),15);
  }
  stateread();
  for (uint16_t b = 15; b> 1; b=b-1) {
    colorFast(strip.Color( 0, b, 2 * b),8);
  }
  stateread();
}
State S14(){
//Medium Fast Yellow 255,255,0
    for (uint16_t b = 1; b< 15; b++) {
    colorFast(strip.Color( b, b, 0),15);
  }
  stateread();
  for (uint16_t b = 15; b> 1; b=b-1) {
    colorFast(strip.Color( b, b, 0),8);
  }
  stateread();
}
State S15(){
//Horrible Hack to keep it white.  
//Medium Fast Purple 128,0,255 
  for (uint16_t b = 1; b< 15; b++) {
    colorFast(strip.Color( b, b, b),15);
  }
  stateread();
  for (uint16_t b = 15; b> 1; b=b-1) {
    colorFast(strip.Color( b, b, b),8);
  }
  stateread();
}
////Medium Fast Purple 128,0,255 
//    for (uint16_t b = 1; b< 15; b++) {
//    colorFast(strip.Color( b, 0 , 2 * b),15);
//  }
//  stateread();
//  for (uint16_t b = 15; b> 1; b=b-1) {
//    colorFast(strip.Color( b, 0, 2 * b),8);
//  }
//  stateread();
//}

