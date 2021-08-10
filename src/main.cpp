//necessary libraries
//using namespace std;
#include <Arduino.h>
#include <FastLED.h>

//My classes
#include "addresableLED.h"
#include "clasicLEDStrip.h"

//Addresable LED pins---------------------------------------------------
#define NUMBER_OF_LEDS 149 //for addresable LED, 149 because one LED is dead on my strip with 150 leds
#define DATA_PIN 22 //IO22 Pin nuber 36
#define BUTTON_PIN 32 //IO14 Pin nuber 13

//Clasic LED strip pins--------------------------------------------------
#define LED_R 25
#define LED_G 26
#define LED_B 27

const int PWMFreq = 60; // 60Hz smooth enought.
const int PWMChannelR = 0, PWMChannelG = 1, PWMChannelB = 2;
const int PWMResolution = 8; // 8bits, from 0 (off state) to 255 (max brightness) 
const int MAX_DUTY_CYCLE = (int)(pow(2, PWMResolution) -1 ); //calculates duty cicle from resolution

//Classes -------------------------------------------------------------
CRGB leds[NUMBER_OF_LEDS]; 
ClasicLEDStrip _classicLEDStrip;
AddresableLED _addresableLED;

//Button control----------------------------------------------------
uint8_t buttonState = 0;
uint8_t preState = 0;
uint8_t counter = 0;

void setup()
{
  pinMode(BUTTON_PIN, INPUT_PULLDOWN); //input test button

//SETUP for clasic led strip controlled by MOSFET, Gate is driven by PWM from defined pins
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  ledcSetup(PWMChannelR, PWMFreq, PWMResolution); //RED
  ledcAttachPin(LED_R, PWMChannelR);
  ledcSetup(PWMChannelG, PWMFreq, PWMResolution); //GREEN
  ledcAttachPin(LED_G, PWMChannelG);
  ledcSetup(PWMChannelB, PWMFreq, PWMResolution); //BLUE
  ledcAttachPin(LED_B, PWMChannelB);

//SETUP for addresable led strip
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUMBER_OF_LEDS);
  Serial.begin(9600);
};

void loop() 
{
  //Button-------------------------------------------------------------------
  if (digitalRead(BUTTON_PIN) == HIGH && preState == 0)
  {
    counter++;
    Serial.println(String(counter));
    preState = 1;
  }

  else if (digitalRead(BUTTON_PIN) == LOW)
  {
    preState = 0;
  }

  EVERY_N_MILLISECONDS(20) //20ms = 50FPS it's NOT the 50Hz as leds refresh rate.
  {

    for (uint8_t i = 0; i < 255; i +=5)
    {
      ledcWrite(PWMChannelR, i);
      ledcWrite(PWMChannelG, 255-i);
    }
    
    _addresableLED.FallingStars(leds,NUMBER_OF_LEDS, 10, CRGB(10,100,250));
    FastLED.show();
  }

};
