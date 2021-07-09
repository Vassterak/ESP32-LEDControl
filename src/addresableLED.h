#include <FastLED.h>
class AddresableLED
{
    public:
    void StaticRainbow(CRGB LEDstrip[],uint8_t numberOfLEDs, uint8_t HUEIncrementor);
    void AnimeRainbow(CRGB LEDstrip[],uint8_t numberOfLEDs,uint8_t speed, uint8_t HUEIncrementor); 

    void SolidPart1(CRGB LEDstrip[], CRGB color); //right side of bed
    void SolidPart2(CRGB LEDstrip[], CRGB color); //center
    void SolidPart3(CRGB LEDstrip[], CRGB color); //left side of bed


};