//necessary libraries
#include <Arduino.h>
#include <FastLED.h>
//My classes
#include "addresableLED.h"
#include "clasicLEDStrip.h"

#define NUMBEROFLEDS 150
#define DATAPIN 22
CRGB leds[NUMBEROFLEDS];
AddresableLED _addresableLED;

void setup()
{
  FastLED.addLeds<NEOPIXEL,DATAPIN>(leds, NUMBEROFLEDS);
}

void loop() 
{
  delay(1000);
  _addresableLED.Duha(leds, NUMBEROFLEDS, 2);
  FastLED.show();
}



