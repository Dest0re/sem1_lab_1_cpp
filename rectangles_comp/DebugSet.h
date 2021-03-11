#pragma once
#include "UserInput.h"

struct ProgramDebug : ProgramInput {
	bool expected = false;
	ProgramDebug() : ProgramInput() {}
};

struct DebugSet {
	unsigned int size;
	ProgramDebug* set;

	DebugSet(unsigned int Size = 0, ProgramDebug* Set = NULL) : size{ Size }, set{ Set } {}

	~DebugSet() {
		delete set;
	}

	ProgramDebug operator[](int num) {
		return set[num];
	}
};
