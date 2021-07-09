//necessary libraries
#include <Arduino.h>
#include <FastLED.h>
//#include <string>
using namespace std;

//My classes
#include "addresableLED.h"
#include "clasicLEDStrip.h"

#define NUMBER_OF_LEDS 150
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
/*   delay(1000);
  _addresableLED.Duha(leds, NUMBER_OF_LEDS, 2);
  FastLED.show(); */


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
    delay(500);
  }

    EVERY_N_MILLISECONDS(20) 
  {
    Serial.println("Ahoj kazdejch 20ms");
  }
}



