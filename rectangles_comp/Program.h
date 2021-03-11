#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include "ProgramOutput.h"
#include "InputOutput.h"
#include "UserInput.h"
#include "DebugSet.h"
#include "ProgramIO.h"
#include "geometry/Rect.h"

const std::string greeting_string =
"Starikov Danil, 404 gr. variation 10, task 1.\n\n"
"Please enter the coordinates of the points in the specified sequence:\n"
" 1+----------------+2 \n"
"  |                |  \n"
"  |                |  \n"
"  |                |  \n"
" 4+----------------+3 \n";

class Program {
public:
	InputOutput io = InputOutput();
	DebugSet debug_set = DebugSet(0);


	void greeting() {
		std::cout << greeting_string << std::endl;
	}

	void debug(DebugSet set) {
		RectsPair rects;

		for (unsigned int i = 0; i < set.size; i++) {
			rects = set[i].extract();
			if (rects[0]->are_intersect(*rects[1]) == set[i].expected) {

			}
			else {

			}
		}
	}

	void ask_for_debug() {
		io << "Run the tests? Y / N:" << std::endl;
		char choice = io.get_char(&std::cin);
		while (choice != 'y' && choice != 'n' && choice != 'Y' && choice != 'N') {
			choice = io.get_char(&std::cin);
		}

		switch (choice) {
		case 'y':
		case 'Y':
			debug(debug_set);
			return;
		case 'n':
		case 'N':
			return;
		}
	}

	InputOutput select_input(std::string filepath) {
		if (filepath == "\n" || filepath == "cin") {
			return InputOutput(&std::cin, &std::cout);
		}
		else {
			if (std::filesystem::exists(filepath)) {
				std::ifstream *ifile = new std::ifstream(filepath, std::ifstream::in);
				if (ifile->is_open()) {
					io << "Successful input!" << std::endl;
					return InputOutput(ifile, &std::cout);
				}
			}
			throw std::invalid_argument("Invalid filepath!");
		}
	}
	
	InputOutput choose_input() {
		InputOutput local_io;
		std::string choice;

		for (;;) {
			io << "Select the input source. [ENTER] or \"cin\" for console input, filepath for file input: " << std::endl;
			choice = io.get_string();
			try {
				return select_input(choice);
			}
			catch (std::invalid_argument) {
				io << "Invalid input! ";
				continue;
			}
		}
	}

	void ask_for_input_save(ProgramInput* input) {
		for (;;) {
			io << "[ENTER] to continue, filepath to save input to the file: " << std::endl;
			std::string filepath;
			io >> filepath;
			if (filepath == "\n") return;

			try {
				std::ofstream file_out(filepath);
				input->write(&file_out);
				io << "Input saved successfully!" << std::endl;
				return;
			}
			catch (std::system_error) {
				io << "Error! Check that the path you entered is correct.";
				continue;
			}
		}
	}

	void ask_for_output_save(ProgramIO output) {
		for (;;) {
			io << "[ENTER] to continue, filepath to save output to file: " << std::endl;
			std::string filepath;
			io >> filepath;
			if (filepath == "\n") return;

			try {
				std::ofstream file_out(filepath);
				output.write(&file_out);
				io << "Output saved successfully!" << std::endl;
				return;
			}
			catch (std::system_error) {
				io << "Error! Check that the path you entered is correct.";
				continue;
			}
		}
	}

	ProgramOutput do_comp(Rect r1, Rect r2) {
		return ProgramOutput(r1.are_intersect(r2));
	}

	void rectangles_comp() {
		InputOutput local_io = choose_input();
		UserInput user_input(local_io);
		ProgramInput* program_input = user_input.user_input();
		RectsPair rp;
		if (local_io.istream == &std::cin) ask_for_input_save(program_input);
		
		try {
			rp = program_input->extract();
		} 
		catch (std::invalid_argument) {
			io << "A rectangle with such coordinates does not exist." << std::endl;
			return;
		}

		ProgramOutput program_output = do_comp(*rp[0], *rp[1]);

		io << ((program_output.State) ? "The rectangles intersect." : "The rectangles do not intersect.") << std::endl << std::endl;

		ask_for_output_save(ProgramIO(*program_input, program_output));
		for (int i = 0; i < 2; i++) {
			delete rp[i];
		}
		delete rp.r;

	}

	void run() {
		do {
			rectangles_comp();
			io.print("[ENTER] to exit, any key to continue;", &std::cout);
		} while (io.get_char() != '\n');
		io.print("Bye!", &std::cout);
	}
};
