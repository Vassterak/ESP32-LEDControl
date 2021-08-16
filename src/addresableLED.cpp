#include "addresableLED.h"

enum{

};

void AddresableLED::SolidPart(CRGB color, int fromZone, int toZone)
{
    fill_solid(leds+fromZone, toZone, color);
}

void AddresableLED::StaticRainbow(uint8_t HUEIncrementor)
{
    fill_rainbow(leds, LEDS_TOTAL_NUMBER, 0, HUEIncrementor);
}

void AddresableLED::AnimeRainbow(uint8_t speed, uint8_t HUEIncrementor) 
{
    uint8_t hue = beat8(speed, 255);
    fill_rainbow(leds, LEDS_TOTAL_NUMBER, hue, HUEIncrementor);
}

void AddresableLED::FallingStars(uint8_t speedOfDisappear, CRGB color) 
{
    leds[random8(0, 149-1)] = CRGB(color);
    //speedOfDisappear is how much brightness will decrese per frame 0-255
    fadeToBlackBy(leds, LEDS_TOTAL_NUMBER, speedOfDisappear);
}

void AddresableLED::Fade1(uint8_t speedOfTransition, CRGB color1, CRGB color2)
{
    nblend(color1, color2, speedOfTransition);
}


