#include "addresableLED.h"
#include <FastLED.h>

void AddresableLED::Duha(CRGB addLEDs[],int numberOfLEDs, int HUEIncrementor)
{
    fill_rainbow(addLEDs, numberOfLEDs, 0, HUEIncrementor);
}