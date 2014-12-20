HOKAY SO.

This is the Code for driving an arbitrary number of WS2812b LEDs with an ATTINY85

Get ATTiny85's Here:http://www.digikey.com/product-detail/en/ATTINY85-20PU/ATTINY85-20PU-ND/735469  
Get WS2812's Here:http://www.aliexpress.com/store/group/WS2812B-pixels-DMX-pixel-IC-and-controllers/701799_251310291.html
Get ATTINY Programmer Here:https://www.sparkfun.com/products/11801

Software:
Get Arduino-Tiny cores here so you can burn arduino to the ATTINY85: https://code.google.com/p/arduino-tiny/
Get Lighting Library from Adafruit here: https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library
Get Little Arduino State Machine Library Here:http://playground.arduino.cc/Code/SMlib

Reference
ATTINY85 Pinout: http://fc04.deviantart.net/fs70/f/2013/038/3/7/attiny_web_by_pighixxx-d5u4aur.png

This repo contains the arduino code to drive a few patterns to the LEDs.

It is currently setup to use 4 pins on the ATTINY85 as a truth table to determine which pattern to fire. This makes it easy to control with another micro that you can wiggle 4 pins on. You can change this very easily by commenting out the truth table part and making transitions between states happen with a button press or just a timed thing.

I've got example python script for controlling from a Beaglebone Black and a Wandboard lying around somewhere, and I've also managed to control it with other Arduinos, basically anything with GPIO that's at least 3.3v logic level. You might need resistors on the digital lines to pull up unless the micro has internal pull ups. 


