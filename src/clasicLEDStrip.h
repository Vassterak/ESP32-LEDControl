#include <Arduino.h>
#include "definitions.h"
#include <FastLED.h>
class ClasicLEDStrip
{
    public:
        CHSV currentColor;
        uint8_t currentSpeed;
        uint8_t currentEffectID;
        void SolidColor(CHSV color);
        void Rainbow(uint8_t speed);
        void Update();

    private:
        CRGB rgbOutput;
};
