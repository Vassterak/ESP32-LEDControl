#include "definitions.h"
#include <FastLED.h>

class AddresableLED
{
    public:
    CRGB leds[LEDS_TOTAL_NUMBER];
    CHSV currentColor;


    AddresableLED()
    {
        FastLED.addLeds<NEOPIXEL,LEDS_DATA_PIN>(leds, LEDS_TOTAL_NUMBER);
    }

    void SolidPart(CHSV color, int fromZone, int toZone); //right side of bed

    // whole strip
    void StaticRainbow(uint8_t HUEIncrementor);
    void AnimeRainbow(uint8_t speed, uint8_t HUEIncrementor);
    void FallingStars(uint8_t speedOfDisappear, CHSV color);
    void Fade1(uint8_t speedOfTransition, CHSV color1, CHSV color2);
    void Fade2(uint8_t speedOfTransition, CHSV color1, CHSV color2, CHSV color3);
    void Fade3(uint8_t speedOfTransition, CHSV color1, CHSV color2, CHSV color3, CHSV color4);
    void MovingToEachOther(uint8_t speed, CHSV color1, CHSV color2);
};