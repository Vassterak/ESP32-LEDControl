#include <Arduino.h>
#include "definitions.h"
#include <FastLED.h>

class ClassicLEDStrip
{
    public:
        bool newColor = false;
        CHSV setColors[3];
        CHSV outputColor;
        uint8_t numberOfColors = 1, currentSpeed = 1, currentEffectID = 0;
        void solidColor();
        void breathing();
        void breathing2();
        void blending();
        void pulsing();
        void rainbow();
        void update();

    private:
        bool helpBoolean = false;
        uint8_t helpInt = 0, maxBrightness = 0, helpInt2 = 0;
        CRGB rgbOutput;
};
