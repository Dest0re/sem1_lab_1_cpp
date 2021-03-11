#pragma once
#include <iostream>

struct ProgramOutput
{
	bool State;

	ProgramOutput(bool state) : State{state} {}

	void write(std::ostream* stream) {
		*stream << State << std::endl;
	}
};
