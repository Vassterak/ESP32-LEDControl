#include "definitions.h"
#include <FastLED.h>

class AddresableLED
{
    public:
        static CRGB leds[LEDS_TOTAL_NUMBER];
        CHSV setColors[3];
        bool newColor = false;
        uint8_t numberOfColors = 1, currentEffectID = 0, currentSpeed = 0, fromLED = 0, numberOfLEDtoFill = 0;
        
        void solidPart();
        void staticRainbow();
        void animeRainbow();
        void fallingStars();
        void breathing();
        void blending();
        void pulsing();
        void pointTravel();

        /*void fade1(uint8_t speedOfTransition, CHSV color1, CHSV color2);
        void fade2(uint8_t speedOfTransition, CHSV color1, CHSV color2, CHSV color3);
        void fade3(uint8_t speedOfTransition, CHSV color1, CHSV color2, CHSV color3, CHSV color4);
        void movingToEachOther(uint8_t speed, CHSV color1, CHSV color2); */

    private:
        bool helpBoolean = false;
        uint8_t helpInt = 0, helpInt2 = 0, maxBrightness = 0;
};