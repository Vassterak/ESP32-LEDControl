//necessary libraries
#include <Arduino.h>
#include <FastLED.h>
//#include <string>
using namespace std;

//My classes
#include "addresableLED.h"
#include "clasicLEDStrip.h"

#define NUMBER_OF_LEDS 149
#define DATA_PIN 22 //IO22 Pin nuber 36
#define BUTTON_PIN 14 //IO14 Pin nuber 13

CRGB leds[NUMBER_OF_LEDS]; 
AddresableLED _addresableLED;

uint8_t buttonState = 0;
uint8_t preState = 0;
uint8_t counter = 0;

void setup()
{
  pinMode(BUTTON_PIN, INPUT);

  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUMBER_OF_LEDS);
  Serial.begin(9600);
}

void loop() 
{
  buttonState = digitalRead(BUTTON_PIN); //read button value
  if (buttonState == HIGH && preState == 0)
  {
    counter++;
    Serial.println(String(counter));
    preState = 1;
  }

  else if (buttonState == LOW)
  {
    preState = 0;
  }

    EVERY_N_MILLISECONDS(40) //20ms = 50FPS smooth enought
  {
    //_addresableLED.FallingStars(leds,NUMBER_OF_LEDS, 10, CRGB(10,100,250));
    _addresableLED.Fade1(leds,CRGB(10,200,100), CRGB(200,10,10), 10);
    FastLED.show();
  }
}



 