#pragma once
#include <iostream>
#include "InputOutput.h"
#include "geometry/Rect.h"
#include "Array.h"

struct RectsPair {
	Rect** r = new Rect*[2];
	RectsPair(Rect *r0, Rect *r1) {
		r[0] = r0;
		r[1] = r1;
 	}
	RectsPair() {
		Rect *r0 = new Rect();
		Rect *r1 = new Rect();
		r[0] = r0;
		r[1] = r1;
	}
	~RectsPair() {
	}
	Rect* operator[](int num) {
		return r[num];
	}
};

struct ProgramInput {
	Array<2, Array<4, Array<2, double>>> *rects = new Array<2, Array<4, Array<2, double>>>;

	ProgramInput() {
	}

	RectsPair extract();

	void write(std::ostream* stream) {
		for (int r = 0; r < 2; r++) {
			for (int d = 0; d < 4; d++) {
				*stream << (*rects)[r][d][0] << std::endl;
				*stream << (*rects)[r][d][1] << std::endl;
			}
		}
	}

	~ProgramInput() {
		delete rects;
	}

};

class UserInput {
public:
	InputOutput IO;

	UserInput(InputOutput);

	ProgramInput* user_input();
};