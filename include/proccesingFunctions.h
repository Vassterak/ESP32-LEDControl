#include <Arduino.h>
#include <FastLED.h>
class ProccesingFunctions
{
    public:
        static uint16_t inputIDProcessing(std::string input);
        static CHSV inputColorProcessing(std::string input);
        static std::tuple<CHSV,CHSV, CHSV, uint8_t> inputMultipleColorProcessing(std::string input);
};