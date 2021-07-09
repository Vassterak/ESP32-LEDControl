#include "addresableLED.h"
#include <FastLED.h>

void AddresableLED::StaticRainbow(CRGB LEDstrip[],uint8_t numberOfLEDs, uint8_t HUEIncrementor)
{
    fill_rainbow(LEDstrip, numberOfLEDs, 0, HUEIncrementor);
}
void AddresableLED::AnimeRainbow(CRGB LEDstrip[],uint8_t numberOfLEDs,uint8_t speed, uint8_t HUEIncrementor) 
{
    uint8_t hue = beat8(speed, 255);
    fill_rainbow(LEDstrip, numberOfLEDs, hue, HUEIncrementor);
}

void AddresableLED::SolidPart1(CRGB LEDstrip[], CRGB color)
{
    fill_solid(LEDstrip, 60, color);
}
void AddresableLED::SolidPart2(CRGB LEDstrip[], CRGB color)
{
    fill_solid(LEDstrip+60, 89, color);
}
void AddresableLED::SolidPart3(CRGB LEDstrip[], CRGB color)
{
    fill_solid(LEDstrip+89, 149, color);
}
