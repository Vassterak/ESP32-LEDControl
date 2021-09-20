#include "proccesingFunctions.h"
#include <tuple>

//simple conversion from string to int.
uint16_t ProccesingFunctions::InputIDProcessing(std::string input)
{
	if (input.length() > 0)
		return atoi(input.c_str()); 

	else
		return 0;
};

//OLD METHOD, NOT USED. For one color only
CHSV ProccesingFunctions::InputColorProcessing(std::string input)
{
	std::string colors[3];
	uint8_t output[3];
	uint8_t id = 0;

	if (input.length() > 0)
	{
		for (uint8_t i = 0; i <= input.length(); i++)
		{
			if (std::isdigit(input[i]))
				colors[id] += input[i];

			else if (input[i] == '_' && id < 4 )
				id++;

			else
				break;
		}

		//get the number of elements in array and convert the string array into int array.
		for (uint8_t i = 0; i < sizeof(colors)/sizeof(*colors) ; i++)
			output[i] = atoi(colors[i].c_str());

		return CHSV(output[0],output[1], output[2]);
	}

	else
		return CHSV(0,0,0);
};

//CURRENT METHOD. Not very efficient, need to be rewritten.
std::tuple<CHSV, CHSV, CHSV, uint8_t> ProccesingFunctions::InputMultipleColorProcessing(std::string input)
{
	CHSV colors[3] = {CHSV(0, 0, 0), CHSV(0, 0, 0), CHSV(0, 0, 0)};
	char output[9][4] = {'\0'};
	uint8_t valuePosition = 0, currentID = 0, numberOfColors = 1;

	if (input.length() > 0)
	{
		for (uint8_t i = 0; i < input.length(); i++)
		{
			if (isdigit(input[i]))
			{
				output[currentID][valuePosition] = input[i];
				valuePosition++;
			}

			//space between color information (hue_saturation_value)
			else if (input[i] == '_')
			{
				valuePosition = 0;
				currentID++;
			}

			//space between each color, after '-' comes next color
			else if (input[i] == '-')
			{
				numberOfColors++;
				valuePosition = 0;
				currentID++;
			}
		}

		colors[0] = CHSV(atoi(output[0]), atoi(output[1]), atoi(output[2]));

		if (numberOfColors > 1)
		{
			colors[1] = CHSV(atoi(output[3]), atoi(output[4]), atoi(output[5]));

			if (numberOfColors > 2)
				colors[2] = CHSV(atoi(output[6]), atoi(output[7]), atoi(output[8]));
		}

		return std::make_tuple(colors[0], colors[1], colors[2], numberOfColors);
	}

	else
		return std::make_tuple(CHSV(0, 0, 0), CHSV(0, 0, 0), CHSV(0, 0, 0), 0);
};
