#include "clasicLEDStrip.h"

void ClasicLEDStrip::SolidColor(CHSV color)
{
    CRGB rgbOutput;
    hsv2rgb_rainbow(color, rgbOutput); //converting HSV to RGB color scheme.
    ledcWrite(PWMChannelR, rgbOutput.red);
    ledcWrite(PWMChannelG, rgbOutput.green);
    ledcWrite(PWMChannelB, rgbOutput.blue);
};

void ClasicLEDStrip::Rainbow(CHSV color, uint8_t speed)
{
    
}