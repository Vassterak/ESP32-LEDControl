#include <Arduino.h>
#include <FastLED.h>
class ProccesingFunctions
{
    public:
        static uint16_t InputIDProcessing(std::string input);
        static CHSV InputColorProcessing(std::string input);
        static std::tuple<CHSV,CHSV, CHSV, uint8_t> InputMultipleColorProcessing(std::string input);
};