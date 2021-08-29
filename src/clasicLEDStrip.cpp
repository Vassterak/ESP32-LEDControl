#include "clasicLEDStrip.h"

void ClassicLEDStrip::SolidColor(CHSV color)
{
    currentColor = color;
};

void ClassicLEDStrip::Breathing(CHSV color, uint8_t speed)
{
    if((currentColor.value + speed) <255 && !helpVariable)
    {
        currentColor.value += speed;
    }

    else
    {
        helpVariable = true;
        currentColor.value -= speed;
    }

    if ((currentColor.value - speed) < 0)
    {
        helpVariable = false;
    }
};

void ClassicLEDStrip::Rainbow(uint8_t speed)
{
    currentColor.hue += speed;
    currentColor.saturation = 255;
};

void ClassicLEDStrip::Update()
{
    hsv2rgb_rainbow(currentColor, rgbOutput); //converting HSV to RGB color scheme.
    ledcWrite(PWMChannelR, rgbOutput.red);
    ledcWrite(PWMChannelG, rgbOutput.green);
    ledcWrite(PWMChannelB, rgbOutput.blue);
}