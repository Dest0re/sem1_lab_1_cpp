#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "InputOutput.h"
#include "UserInput.h"
#include "Program.h"

int main() {
	Program program = Program();
	program.greeting();
	//program.ask_for_debug();
	program.run();

	return 0;
}
