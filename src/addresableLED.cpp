#include "addresableLED.h"

void AddresableLED::SolidPart(CHSV color, int fromZone, int toZone)
{
    fill_solid(leds+fromZone, toZone, color);
}

void AddresableLED::staticRainbow(uint8_t HUEIncrementor)
{
    fill_rainbow(leds, LEDS_TOTAL_NUMBER, 0, HUEIncrementor);
}

void AddresableLED::animeRainbow(uint8_t speed, uint8_t HUEIncrementor) 
{
    uint8_t hue = beat8(speed, 255);
    fill_rainbow(leds, LEDS_TOTAL_NUMBER, hue, HUEIncrementor);
}

void AddresableLED::fallingStars(uint8_t speedOfDisappear, CHSV color) 
{
    leds[random8(0, 149-1)] = CHSV(color);
    //speedOfDisappear is how much brightness will decrese per frame 0-255
    fadeToBlackBy(leds, LEDS_TOTAL_NUMBER, speedOfDisappear);
}

void AddresableLED::fade1(uint8_t speedOfTransition, CHSV color1, CHSV color2)
{
    nblend(color1, color2, speedOfTransition);
}


