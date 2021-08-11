#include "addresableLED.h"

enum{

};

void AddresableLED::SolidPart1(CRGB color)
{
    fill_solid(leds, 60, color);
}

void AddresableLED::SolidPart2(CRGB color)
{
    fill_solid(leds+60, 89, color);
}

void AddresableLED::SolidPart3(CRGB color)
{
    fill_solid(leds+89, 149, color);
}

void AddresableLED::StaticRainbow(uint8_t HUEIncrementor)
{
    fill_rainbow(leds, NUMBER_OF_LEDS, 0, HUEIncrementor);
}

void AddresableLED::AnimeRainbow(uint8_t speed, uint8_t HUEIncrementor) 
{
    uint8_t hue = beat8(speed, 255);
    fill_rainbow(leds, NUMBER_OF_LEDS, hue, HUEIncrementor);
}

void AddresableLED::FallingStars(uint8_t speedOfDisappear, CRGB color)
{
    leds[random8(0, 149-1)] = CRGB(color);
    fadeToBlackBy(leds, NUMBER_OF_LEDS, speedOfDisappear);
}

void AddresableLED::Fade1(uint8_t speedOfTransition, CRGB color1, CRGB color2)
{
    nblend(color1, color2, speedOfTransition);
}


