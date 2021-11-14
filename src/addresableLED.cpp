#include "addresableLED.h"

void AddresableLED::SolidPart()
{
    fill_solid(leds+0, LEDS_TOTAL_NUMBER, setColors[0]);
}

void AddresableLED::staticRainbow()
{
    fill_rainbow(leds, LEDS_TOTAL_NUMBER, 0, currentSpeed);
}

void AddresableLED::animeRainbow() 
{
    uint8_t hue = beat8(currentSpeed, 255);
    fill_rainbow(leds, LEDS_TOTAL_NUMBER, hue, currentSpeed);
}

void AddresableLED::fallingStars() 
{
    leds[random8(0, 149-1)] = CHSV(setColors[0]);
    //speedOfDisappear is how much brightness will decrese per frame 0-255
    fadeToBlackBy(leds, LEDS_TOTAL_NUMBER, currentSpeed);
}

/* void AddresableLED::fade1(uint8_t speedOfTransition, CHSV color1, CHSV color2)
{
    nblend(color1, color2, speedOfTransition);
} */


