#include <Arduino.h>
#include "definitions.h"
#include <FastLED.h>
class ClassicLEDStrip
{
    public:
        bool newColor = false;
        CHSV setColors[3];
        CHSV outputColor;
        uint8_t numberOfColors = 1;
        uint8_t currentSpeed = 1;
        uint8_t currentEffectID = 0;
        uint8_t maxBrightness = 0;
        void SolidColor();
        void Breathing();
        void Breathing2();
        void Rainbow();
        void Update();

    private:
        bool helpBoolean = false;
        uint8_t helpInt = 0;
        CRGB rgbOutput;
};
