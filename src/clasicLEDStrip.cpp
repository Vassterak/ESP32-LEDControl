#include "clasicLEDStrip.h"

void ClassicLEDStrip::SolidColor()
{
    if (newColor)
    {
        outputColor = setColors[0];
        newColor = false;
    }
};

//not used
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
        
        helpInt = 0;
        newColor = false;
        helpBoolean = false;
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

//looping through hue value forever
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

//First time I've tried to make my own algorithm for color blending / interpolation but it wasn't very effitient.
//So I use integrated from FastLED library, for more info there are links:
//https://www.alanzucconi.com/2016/01/06/colour-interpolation/
//http://fastled.io/docs/3.1/group___colorutils.html
void ClassicLEDStrip::Blending()
{
    if (newColor)
    {
        helpInt = 0;
        helpInt2 = 0;
        newColor = false;
        helpBoolean = false;
    }

    if (numberOfColors > 2)
    {
        if ((helpInt + currentSpeed) > 255)
        {
            helpInt = 255;
            helpBoolean = true;
        }

        if (helpInt2 == 2)
        {
            outputColor = blend(setColors[helpInt2], setColors[0], helpInt);
        }
        else
            outputColor = blend(setColors[helpInt2], setColors[helpInt2 + 1], helpInt);

        helpInt += currentSpeed;

        if (helpBoolean)
        {
            helpInt2++;
            if (helpInt2 == 3)
                helpInt2 = 0;
            helpBoolean = false;
        }

    }

    //8bit sinusoidal wave for smooth color blending. 0 = setColors[0], 255 = setCorlos[1] betweeen 2 colors
    else 
        outputColor = blend(setColors[0], setColors[1], beatsin8(currentSpeed, 0,255));
};

void ClassicLEDStrip::Pulsing()
{

};

void ClassicLEDStrip::Update()
{
    hsv2rgb_rainbow(outputColor, rgbOutput); //converting HSV to RGB color scheme.
    ledcWrite(PWMChannelR, rgbOutput.red);
    ledcWrite(PWMChannelG, rgbOutput.green);
    ledcWrite(PWMChannelB, rgbOutput.blue);
}