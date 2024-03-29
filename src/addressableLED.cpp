#include "addressableLED.h"

void AddressableLED::solidPart()
{
    fill_solid(leds+fromLED, numberOfLEDtoFill, setColors[0]);
}

void AddressableLED::staticRainbow()
{
    fill_rainbow(leds + fromLED, numberOfLEDtoFill, 0, currentSpeed); //currentSpeed = hue incrementor
    FastLED.setBrightness(setColors[0].value);
}

void AddressableLED::animeRainbow() 
{
    fill_rainbow(leds + fromLED, numberOfLEDtoFill, beat8(currentSpeed, 255), currentSpeed /2); //currentSpeed = hue incrementor
    FastLED.setBrightness(setColors[0].value);
}

void AddressableLED::fallingStars() 
{
    leds[random8(fromLED, fromLED + numberOfLEDtoFill)] = CHSV(setColors[0]);
    //speedOfDisappear is how much brightness will decrese per frame 0-255
    fadeToBlackBy(leds + fromLED, numberOfLEDtoFill, currentSpeed);
}

void AddressableLED::pulsing()
{
    if (newColor)
    {
        maxBrightness = setColors[0].value; //get max brightness

        for (uint8_t i = 0; i < numberOfColors; i++) //remove brightness values from all colors
            setColors[i].value = 0;

        helpInt = 0; //reset variables
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
    fill_solid(leds + fromLED, numberOfLEDtoFill, setColors[helpInt2]);
}

void AddressableLED::breathing()
{
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
    fill_solid(leds + fromLED, numberOfLEDtoFill, setColors[helpInt]);
}

void AddressableLED::blending()
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
            fill_solid(leds + fromLED, numberOfLEDtoFill, blend(setColors[helpInt2], setColors[0], helpInt));

        else
            fill_solid(leds + fromLED, numberOfLEDtoFill, blend(setColors[helpInt2], setColors[helpInt2 + 1], helpInt));

        helpInt += currentSpeed;

        if (helpBoolean)
        {
            helpInt2++;

            if (helpInt2 == 3)
                helpInt2 = 0;

            helpBoolean = false;
        }
    }
    else
        fill_solid(leds + fromLED, numberOfLEDtoFill, blend(setColors[0], setColors[1], beatsin8(currentSpeed, 0, 255)));
}

void AddressableLED::pointTravel()
{
    leds[beatsin8(currentSpeed, fromLED, fromLED + numberOfLEDtoFill, 0, 0)] = CHSV(setColors[0]); //udělej vyjímky pro to!!!
    fadeToBlackBy(leds + fromLED, numberOfLEDtoFill, 10);
}