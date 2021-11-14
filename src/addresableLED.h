#include "definitions.h"
#include <FastLED.h>

class AddresableLED
{
    public:
    CRGB leds[LEDS_TOTAL_NUMBER];
    CHSV setColors[3];
    uint8_t numberOfColors = 1, currentEffectID = 0, currentSpeed = 0, selectedZone = 0;

    AddresableLED() //constructor
    {
        FastLED.addLeds<NEOPIXEL,LEDS_DATA_PIN>(leds, LEDS_TOTAL_NUMBER);
    }

    void solidPart();
    void staticRainbow();
    void animeRainbow();
    void fallingStars();
/*     void fade1(uint8_t speedOfTransition, CHSV color1, CHSV color2);
    void fade2(uint8_t speedOfTransition, CHSV color1, CHSV color2, CHSV color3);
    void fade3(uint8_t speedOfTransition, CHSV color1, CHSV color2, CHSV color3, CHSV color4);
    void movingToEachOther(uint8_t speed, CHSV color1, CHSV color2); */
};