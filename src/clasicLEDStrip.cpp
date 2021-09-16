#include "clasicLEDStrip.h"

void ClassicLEDStrip::SolidColor()
{
    if (newColor)
    {
        outputColor = setColors[0];
        newColor = false;
    }
};

void ClassicLEDStrip::Breathing()
{
    if ((setColors[0].value + currentSpeed) < 255 && !helpBoolean)
    {
        setColors[0].value += currentSpeed;
    }

    else
    {
        helpBoolean = true;
        setColors[0].value -= currentSpeed;
    }

    if ((setColors[0].value - currentSpeed) < 0)
    {
        helpBoolean = false;
    }
};

void ClassicLEDStrip::Breathing2()
{
    if (newColor)
    {
        maxBrightness = setColors[0].value;
        for (uint8_t i = 0; i < numberOfColors; i++) //set initial brightness level for all colors to 0
            setColors[i].value = 0;
        
        Serial.println("Nová barva, přijata");
        newColor = false;
    }
        if ((setColors[helpInt].value + currentSpeed) < maxBrightness && !helpBoolean)
            setColors[helpInt].value += currentSpeed;

        else
        {
            helpBoolean = true;
            setColors[helpInt].value -= currentSpeed;
        }

        if ((setColors[helpInt].value - currentSpeed) < 0)
        {
            helpBoolean = false;
            helpInt++;

            if (helpInt >= numberOfColors)
                helpInt = 0;
        }
        outputColor = setColors[helpInt];
};

void ClassicLEDStrip::Rainbow()
{
    if (newColor)
    {
        outputColor = setColors[0];
        newColor = false;
    }

    outputColor.hue += currentSpeed;
    outputColor.saturation = 255;
};

void ClassicLEDStrip::Update()
{
    hsv2rgb_rainbow(outputColor, rgbOutput); //converting HSV to RGB color scheme.
    ledcWrite(PWMChannelR, rgbOutput.red);
    ledcWrite(PWMChannelG, rgbOutput.green);
    ledcWrite(PWMChannelB, rgbOutput.blue);
}