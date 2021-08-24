#include <Arduino.h>
#include "definitions.h"
#include <FastLED.h>
class ClasicLEDStrip
{
    public:
        CHSV currentColor;
        void SolidColor(CHSV color);
        void Rainbow(CHSV color, uint8_t speed);

    private:
};
