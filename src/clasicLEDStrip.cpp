#include "clasicLEDStrip.h"

void ClassicLEDStrip::SolidColor()
{
    //runs only after the new color is received from mobile app.
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
        setColors[0].value += currentSpeed;

    else
    {
        helpBoolean = true;
        setColors[0].value -= currentSpeed;
    }

    if ((setColors[0].value - currentSpeed) < 0)
        helpBoolean = false;
};

//Effect is used for changing brightness value from 0 to 255 in linear motion.
//Each time a value gets to the 0 the color is swapped for a new one.
//Then it's repating to the end of the array and after that starts all over again.
void ClassicLEDStrip::Breathing2()
{
    //same as in "void ClassicLEDStrip::SolidColor()"
    if (newColor)
    {
        maxBrightness = setColors[0].value;

        for (uint8_t i = 0; i < numberOfColors; i++)
            setColors[i].value = 0;
        
        helpInt = 0;
        helpInt2 = 0;
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

    //When value reach 0
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
            outputColor = blend(setColors[helpInt2], setColors[0], helpInt);

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

    //When there are only 2 colors. beatsin8 generates sinusodial wawe to oscilate between them.
    else 
        outputColor = blend(setColors[0], setColors[1], beatsin8(currentSpeed, 0,255));
};

void ClassicLEDStrip::Pulsing()
{
    if (newColor)
    {
        maxBrightness = setColors[0].value;

        for (uint8_t i = 0; i < numberOfColors; i++)
            setColors[i].value = 0;

        helpInt = 0;
        helpInt2 = 0;
        helpBoolean = false;
        newColor = false;
    }

    if ((helpInt + currentSpeed) > 255)
    {
        helpInt = 255;

        if (!helpBoolean)
        {
            helpInt2++;
            if (helpInt2 >= numberOfColors)
                helpInt2 = 0;
        }

        helpBoolean = !helpBoolean;
    }

    helpBoolean ? setColors[helpInt2].value = maxBrightness : setColors[helpInt2].value = 0;

    helpInt += currentSpeed;
    outputColor = setColors[helpInt2];
};

void ClassicLEDStrip::Update()
{
    //converting HSV to RGB color scheme.
    hsv2rgb_rainbow(outputColor, rgbOutput);

    ledcWrite(PWMChannelR, rgbOutput.red);
    ledcWrite(PWMChannelG, rgbOutput.green);
    ledcWrite(PWMChannelB, rgbOutput.blue);
}