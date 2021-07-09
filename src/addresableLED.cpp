#include "addresableLED.h"
#include <FastLED.h>

void AddresableLED::Duha(CRGB addLEDs[],uint8_t numberOfLEDs, uint8_t HUEIncrementor)
{
    fill_rainbow(addLEDs, numberOfLEDs, 0, HUEIncrementor);
}