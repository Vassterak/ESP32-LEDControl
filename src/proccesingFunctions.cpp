#include "proccesingFunctions.h"
#include <tuple>

uint16_t ProccesingFunctions::InputIDProcessing(std::string input)
{
	if (input.length() > 0)
	{
		Serial.println(atoi(input.c_str()));
		return atoi(input.c_str());
	}

	else
		return 0;
};

CHSV ProccesingFunctions::InputColorProcessing(std::string input)
{
	std::string colors[3];
	uint8_t output[3];
	uint8_t id = 0;

	if (input[0] == 'c') //check if input starts with 'c' as for color code.
	{
		for (uint8_t i = 1; i <= input.length(); i++)
		{
			if (std::isdigit(input[i]))
				colors[id] += input[i];

			else if (input[i] == '-' && id < 4 )
				id++;

			else
				break;
		}
		
		for (uint8_t i = 0; i < sizeof(colors)/sizeof(*colors) ; i++)
			output[i] = atoi(colors[i].c_str());
		
		return CHSV(output[0],output[1], output[2]);
	}

	else
		return CHSV(0,0,0);
};

/* std::tuple<uint8_t, uint8_t, uint8_t> ProccesingFunctions::InputColorProcessing(std::string input)
{
	std::string colors[3];
	uint8_t output[3];
	uint8_t id = 0;

	if (input[0] == 'c') //check if input starts with 'c' as for color code.
	{
		for (uint8_t i = 1; i <= input.length(); i++)
		{
			if (std::isdigit(input[i]))
				colors[id] += input[i];

			else if (input[i] == '-' && id < 4 )
				id++;

			else
				break;
		}
		
		for (uint8_t i = 0; i < sizeof(colors)/sizeof(*colors) ; i++)
			output[i] = atoi(colors[i].c_str());
		
		return std::make_tuple(output[0],output[1], output[2]);
	}

	else
		return std::make_tuple(0,0,0);
}; */

