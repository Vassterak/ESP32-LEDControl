#include "clasicLEDStrip.h"

void ClasicLEDStrip::SolidColor(CHSV color)
{
    currentColor = color;
};

void ClasicLEDStrip::Rainbow(uint8_t speed)
{
    currentColor.hue += speed;
    currentColor.saturation = 255;
};

void ClasicLEDStrip::Update()
{
    hsv2rgb_rainbow(currentColor, rgbOutput); //converting HSV to RGB color scheme.
    ledcWrite(PWMChannelR, rgbOutput.red);
    ledcWrite(PWMChannelG, rgbOutput.green);
    ledcWrite(PWMChannelB, rgbOutput.blue);
}