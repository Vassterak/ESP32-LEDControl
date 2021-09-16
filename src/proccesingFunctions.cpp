#include "proccesingFunctions.h"
#include <tuple>

uint16_t ProccesingFunctions::InputIDProcessing(std::string input)						//simple conversion from string to int.
{
	if (input.length() > 0)
		return atoi(input.c_str()); 

	else
		return 0;
};

CHSV ProccesingFunctions::InputColorProcessing(std::string input) 						//Old method for one color only
{
	std::string colors[3];
	uint8_t output[3];
	uint8_t id = 0;

	if (input.length() > 0)
	{
		for (uint8_t i = 0; i <= input.length(); i++)
		{
			if (std::isdigit(input[i])) 												//check if char is number
				colors[id] += input[i]; 												//put the number into the colors array

			else if (input[i] == '_' && id < 4 ) 										//when the spacer is detected, it will increte the id value. So the next number is placed into the correct array's element/part. You know what I mean.
				id++;

			else
				break;
		}
		
		for (uint8_t i = 0; i < sizeof(colors)/sizeof(*colors) ; i++) 					//get the number of elements in array and convert the string array into int array. So it can be returned as complete color.
			output[i] = atoi(colors[i].c_str());
		
		return CHSV(output[0],output[1], output[2]);
	}

	else
		return CHSV(0,0,0);
};

//horribly inefficient method for convertion, I'm awere of that. If it works don't touch it. Just a joke I'll fix it later...
std::tuple<CHSV, CHSV, CHSV, uint8_t> ProccesingFunctions::InputMultipleColorProcessing(std::string input)
{
	Serial.print("Received string: ");
	Serial.println(input.c_str());

	CHSV colors[3] = {CHSV(0, 0, 0), CHSV(0, 0, 0), CHSV(0, 0, 0)}; 					//initializing empty color array, each element is one color.
	char output[9][4] = {'\0'};															//initializing empty char array, that will hold parsed values from input string
	uint8_t valuePosition = 0;	
	uint8_t currentID = 0;
	uint8_t numberOfColors = 1;

	if (input.length() > 0)
	{
		for (uint8_t i = 0; i < input.length(); i++)
		{
			if (isdigit(input[i]))
			{
				output[currentID][valuePosition] = input[i];
				valuePosition++;
			}
			else if (input[i] == '_')
			{
				valuePosition = 0;
				currentID++;
			}
			else if (input[i] == '-')
			{
				numberOfColors++;
				valuePosition = 0;
				currentID++;
			}
		}

		colors[0] = CHSV(atoi(output[0]), atoi(output[1]), atoi(output[2])); 			//...no comment for this inefficiency
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

