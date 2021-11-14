#include "definitions.h"
#include <FastLED.h>

class AddresableLED
{
    public:
    CRGB leds[LEDS_TOTAL_NUMBER];
    CHSV currentColors[3];
    uint8_t currentEffectID = 0;

    AddresableLED()
    {
        FastLED.addLeds<NEOPIXEL,LEDS_DATA_PIN>(leds, LEDS_TOTAL_NUMBER);
    }

    void SolidPart(CHSV color, int fromZone, int toZone); //right side of bed

    // whole strip
    void staticRainbow(uint8_t HUEIncrementor);
    void animeRainbow(uint8_t speed, uint8_t HUEIncrementor);
    void fallingStars(uint8_t speedOfDisappear, CHSV color);
    void fade1(uint8_t speedOfTransition, CHSV color1, CHSV color2);
    void fade2(uint8_t speedOfTransition, CHSV color1, CHSV color2, CHSV color3);
    void fade3(uint8_t speedOfTransition, CHSV color1, CHSV color2, CHSV color3, CHSV color4);
    void movingToEachOther(uint8_t speed, CHSV color1, CHSV color2);
};