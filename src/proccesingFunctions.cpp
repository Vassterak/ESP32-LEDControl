#include "proccesingFunctions.h"

uint16_t ProccesingFunctions::IDInputProcessing(std::string input)
{
	if (input.length() > 0)
	{
		Serial.print("\nOutput after parsing: ");
		Serial.println(atoi(input.c_str()));
		return atoi(input.c_str());
	}
}