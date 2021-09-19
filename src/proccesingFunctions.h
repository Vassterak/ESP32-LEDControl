#include <Arduino.h>
#include <FastLED.h>
class ProccesingFunctions
{
    private:
        /* data */
    public:
        static uint16_t InputIDProcessing(std::string input);
        static CHSV InputColorProcessing(std::string input);
/*         static CHSV ColorInterpolation(CHSV color1, CHSV color2, float speed); */
        static std::tuple<CHSV,CHSV, CHSV, uint8_t> InputMultipleColorProcessing(std::string input);
};