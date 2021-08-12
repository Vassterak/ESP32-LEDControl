#include "definitions.h"
#include <FastLED.h>

class AddresableLED
{
    public:
    CRGB leds[LEDS_TOTAL_NUMBER];
    AddresableLED()
    {
        FastLED.addLeds<NEOPIXEL,LEDS_DATA_PIN>(leds, LEDS_TOTAL_NUMBER);
    }

    void SolidPart1(CRGB color); //right side of bed
    void SolidPart2(CRGB color); //center
    void SolidPart3(CRGB color); //left side of bed

    // whole strip
    void StaticRainbow(uint8_t HUEIncrementor);
    void AnimeRainbow(uint8_t speed, uint8_t HUEIncrementor);
    void FallingStars(uint8_t speedOfDisappear, CRGB color);
    void Fade1(uint8_t speedOfTransition, CRGB color1, CRGB color2);
    void Fade2(uint8_t speedOfTransition, CRGB color1, CRGB color2, CRGB color3);
    void Fade3(uint8_t speedOfTransition, CRGB color1, CRGB color2, CRGB color3, CRGB color4);
    void MovingToEachOther(uint8_t speed, CRGB color1, CRGB color2);
};