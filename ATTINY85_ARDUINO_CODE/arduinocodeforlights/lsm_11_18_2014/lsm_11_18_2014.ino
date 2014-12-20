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
#define NUM_LEDS 24//12 for enviros 16 for cameras 24 for base stations
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

void theaterChase(uint32_t c, uint8_t wait) {

    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c-random(1,50));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
 
}

void colorFast(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
  delay(wait);
}

void swirler(uint32_t c, uint8_t wait, uint8_t taillength, boolean dir) {
  if (dir) {
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      for (uint16_t f = 1; f < taillength; f++){
        strip.setPixelColor(i-f,c*(1/f));
      }
      strip.setPixelColor(i-(taillength+1),0);
    }
    strip.show();
    delay(wait);
  }
      else {
        for (uint16_t i = strip.numPixels(); i > 0; i=i-1) {
      strip.setPixelColor(i, c);
      for (uint16_t f = taillength; f > 1; f=f-1){
        strip.setPixelColor(i+f,c*(1/f));
      }
      strip.setPixelColor(i-(taillength-1),0);
    }
    strip.show();
    delay(wait);
    }
  }
 void swirlerbase(uint32_t c, uint8_t wait, uint8_t taillength, boolean dir) {
  if (dir) {
    for (uint16_t i = 1; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.setPixelColor(i+1, c);
      
      for (uint16_t f = 1; f < taillength; f++){
        strip.setPixelColor(i-f,c*(1/f));
        strip.setPixelColor(i-(f+1),c*(1/f));
      strip.setPixelColor(i-(taillength),0);
      strip.setPixelColor(i-(taillength+1),0);
      }
      strip.show();
      strip.setPixelColor(i,0);
      strip.setPixelColor(i+1,0);
    delay(wait);
    }
    
  }
      else {
        for (uint16_t i = strip.numPixels(); i > 0; i=i-1) {
      strip.setPixelColor(i, c);
      strip.setPixelColor(i-1, c);
      for (uint16_t f = taillength; f > 1; f=f-1){
        strip.setPixelColor(i-f,c*(1/f));
        strip.setPixelColor(i-f+1,c*(1/f));
      }
      strip.setPixelColor(i-(taillength-1),0);
      strip.setPixelColor(i-(taillength-2),0);
      strip.show();
    delay(wait);
    }
    
    }
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

//State S11(){
//Low Slow Green 0,255,0 
  //for (uint16_t b = 1; b< 15; b++) {
    //colorFast(strip.Color( 0, b, 0),100);
  //}
  //stateread();
  //for (uint16_t b = 15; b> 1; b=b-1) {
    //colorFast(strip.Color( 0, b, 0),50);
 // }
  //stateread();
//}    
State S11(){
  // Blue Swirl
  for (uint16_t b=1; b<100; b=b+5) {
    swirlerbase(strip.Color(0,0,b),20,5,true);
  }
  stateread();
  swirlerbase(strip.Color(0,0,80),15,5,false);
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
//party harty
    for (uint16_t b = 20; b< 80; b++) {
    theaterChase(strip.Color( b, b, b),40);
  }
  stateread();
  for (uint16_t b = 80; b> 20; b=b-1) {
    colorFast(strip.Color( b, b, b),30);
  }
  stateread();
}
State S15(){
//Horrible Hack to keep it white.  
//Medium Fast Purple 128,0,255 
  //for (uint16_t b = 1; b< 15; b++) {
    //colorFast(strip.Color( b, b, b),15);
  //}
  //stateread();
  //for (uint16_t b = 15; b> 1; b=b-1) {
    //colorFast(strip.Color( b, b, b),8);
  //}
  //stateread();
   
    colorFast(strip.Color(0,0,0),0);
    strip.show();
  
  swirlerbase(strip.Color(0,0,150),30,20,true);
  swirlerbase(strip.Color(0,0,150),30,20,true);
  swirlerbase(strip.Color(0,0,150),30,20,true);
  
  
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

