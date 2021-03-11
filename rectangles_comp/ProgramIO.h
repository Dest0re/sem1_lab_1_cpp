#pragma once
#include <iostream>
#include "UserInput.h"
#include "ProgramOutput.h"

struct ProgramIO
{
	ProgramInput input;
	ProgramOutput output;

	ProgramIO(ProgramInput program_input, ProgramOutput program_output) : input{ program_input }, output{ program_output } {}

	void write(std::ostream* stream) {
		*stream << "Input and output data of the program \"Intersection of rectangles\"." << std::endl;
		*stream << "Input data:" << std::endl << std::endl;

		input.write(stream);

		*stream << std::endl << std::endl << "Output data:" << std::endl << std::endl;

		output.write(stream);
	}
};
