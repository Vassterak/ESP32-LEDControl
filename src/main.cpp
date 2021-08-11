#include <Arduino.h>
#include <FastLED.h>

//My files
#include "definitions.h" //all define values
#include "addresableLED.h"
#include "clasicLEDStrip.h"

const int PWMFreq = 50; // 50Hz smooth enought. Also the animation will be played at 50FPS and 50Hz is compliant with frequency of power grid in EU. (Avoid flickering in camera)
const int PWMChannelR = 0, PWMChannelG = 1, PWMChannelB = 2;
const int PWMResolution = 8; // 8bits, from 0 (off state) to 255 (max brightness) 
const int MAX_DUTY_CYCLE = (int)(pow(2, PWMResolution) -1 ); //calculates duty cicle from resolution

//Classes -------------------------------------------------------------
ClasicLEDStrip _classicLEDStrip;
//AddresableLED _addresableLED;

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

  //FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUMBER_OF_LEDS);

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
    
    //_addresableLED.FallingStars(leds,NUMBER_OF_LEDS, 10, CRGB(10,100,250));
    FastLED.show();
  }

};
