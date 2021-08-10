#include <FastLED.h>
class AddresableLED
{
    public:
    void SolidPart1(CRGB LEDstrip[], CRGB color); //right side of bed
    void SolidPart2(CRGB LEDstrip[], CRGB color); //center
    void SolidPart3(CRGB LEDstrip[], CRGB color); //left side of bed

    // whole strip
    void StaticRainbow(CRGB LEDstrip[],uint8_t numberOfLEDs, uint8_t HUEIncrementor);
    void AnimeRainbow(CRGB LEDstrip[],uint8_t numberOfLEDs,uint8_t speed, uint8_t HUEIncrementor);
    void FallingStars(CRGB LEDstrip[], uint8_t numberOfLEDs, uint8_t speedOfDisappear, CRGB color);
    void Fade1(CRGB LEDstrip[], uint8_t speedOfTransition, CRGB color1, CRGB color2);
    void Fade2(CRGB LEDstrip[], uint8_t speedOfTransition, CRGB color1, CRGB color2, CRGB color3);
    void Fade3(CRGB LEDstrip[], uint8_t speedOfTransition, CRGB color1, CRGB color2, CRGB color3, CRGB color4);
    void MovingToEachOther(CRGB LEDstrip[], uint8_t speed, CRGB color1, CRGB color2);
};