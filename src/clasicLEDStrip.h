#include <Arduino.h>
#include "definitions.h"
#include <FastLED.h>

class ClassicLEDStrip
{
    public:
        bool newColor = false;
        CHSV setColors[3];
        CHSV outputColor;
        uint8_t numberOfColors = 1, currentSpeed = 1, currentEffectID = 0, maxBrightness = 0;
        void SolidColor();
        void Breathing();
        void Breathing2();
        void Blending();
        void Pulsing();
        void Rainbow();
        void Update();

    private:
        bool helpBoolean = false;
        uint8_t helpInt = 0;
        uint8_t helpInt2 = 0;
        CRGB rgbOutput;
};
