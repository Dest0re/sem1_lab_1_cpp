#include "UserInput.h"
#include "InputOutput.h"
#include <iostream>

UserInput::UserInput(InputOutput io) {
	IO = io;
};

ProgramInput* UserInput::user_input() {
	ProgramInput *program_input = new ProgramInput();

	if (IO.istream == &std::cin) {
		for (int r = 0; r < 2; r++) {
			IO << "Entering the coordinates of the points of the " << r + 1 << " rectangle: " << std::endl;
			for (int p = 0; p < 4; p++) {
				IO << "  Entering the coordinates of the point #" << p + 1 << ":" << std::endl;
				IO << "    Y: ";
				program_input->rects[r][p][0] = IO.get_num<float>();
				IO << "    X: ";
				program_input->rects[r][p][1] = IO.get_num<float>();
				IO << "" << std::endl;
			}
		}
	}
	else {
		for (int r = 0; r < 2; r++) {
			for (int p = 0; p < 4; p++) {
				program_input->rects[r][p][0] = IO.get_num<float>();
				program_input->rects[r][p][1] = IO.get_num<float>();
			}
		}
	}

	return program_input;
}

RectsPair ProgramInput::extract() {
	Rect* rect1 = new Rect(rects[0]);
	Rect* rect2 = new Rect(rects[1]);
	return RectsPair(rect1, rect2);
}
