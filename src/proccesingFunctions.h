#include <Arduino.h>
#include <FastLED.h>
class ProccesingFunctions
{
    private:
        /* data */
    public:
        static uint16_t InputIDProcessing(std::string input);
        static CHSV InputColorProcessing(std::string input);
        //static std::tuple<uint8_t, uint8_t,uint8_t> InputColorProcessing(std::string input);
};