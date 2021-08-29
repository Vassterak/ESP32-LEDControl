#include <Arduino.h>
#include "definitions.h"
#include <FastLED.h>
class ClassicLEDStrip
{
    public:
        CHSV currentColor;
        uint8_t currentSpeed = 0;
        uint8_t currentEffectID = 0;
        void SolidColor(CHSV color);
        void Breathing(CHSV color, uint8_t speed);
        void Rainbow(uint8_t speed);
        void Update();

    private:
        bool helpVariable = false;
        CRGB rgbOutput;
};
