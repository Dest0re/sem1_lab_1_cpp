#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>

#include "geometry/Rect.h"
#include "new_input.h"
#include "new_output.h"

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

	void greeting() {
		std::cout << greeting_string << std::endl;
	}

	FileOutput open_file_for_write(std::string filepath) {
		
	}

	/*void debug(DebugSet set) {
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
	}*/

	/*InputOutput select_input(std::string filepath) {
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
	}*/
	
	/*InputOutput choose_input() {
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
	}*/

	/*void ask_for_input_save(ProgramInput* input) {
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
	}*/

	/*void ask_for_output_save(ProgramIO output) {
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
	}*/

	/*ProgramOutput do_comp(Rect r1, Rect r2) {
		return ProgramOutput(r1.are_intersect(r2));
	}*/

	/*void rectangles_comp() {
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

		delete program_input;
		for (int i = 0; i < 2; i++) {
			delete rp.r[i];
		}
		delete rp.r;

	}*/

	void loop() {
		std::cout << "Choose input method. [ENTER] or \"console\" for console input, filepath for input from file: ";
		
		std::string choice;
		getline(std::cin, choice);
		
		std::cout << std::endl;

		if (choice == "" || choice == "console") {
			ConsoleInput input = ConsoleInput();
			double** rects = new double*[2];
			for (int i = 0; i < 2; i++) {
				rects[i] = new double[8];
			}

			Rect** rect_objects = new Rect*[2];

			for (int r = 0; r < 2; r++) {
				while (true) {
					std::cout << "Entering the coordinates of the points of the " << r + 1 << " rectangle: " << std::endl;
					for (int p = 0; p < 4; p++) {
						std::cout << "  Entering the coordinates of the point #" << p + 1 << ":" << std::endl;
						std::cout << "    X: ";
						rects[r][p * 2] = input.get_num<double>();
						std::cout << "    Y: ";
						rects[r][p * 2 + 1] = input.get_num<double>();
						std::cout << "" << std::endl;
					}

					try {
						rect_objects[r] = new Rect(new Point(rects[r][0], rects[r][1]), new Point(rects[r][2], rects[r][3]), new Point(rects[r][4], rects[r][5]), new Point(rects[r][6], rects[r][7]));
					}
					catch (std::invalid_argument) {
						std::cout << "The rectangle cannot exist; please enter another one: " << std::endl;
						continue;
					}
					break;
				}
			}

			std::cout << "Do you want to save input to file? [ENTER] for \"no\", filepath to save: ";

			getline(std::cin, choice);


			if (choice != "") {
				while (true) {
					try {
						FileOutput file = FileOutput(choice, std::ofstream::trunc);

						for (int r = 0; r < 2; r++) {
							for (int c = 0; c < 8; c++) {
								file.print<double>(rects[r][c]);
							}
						}
						break;
					}
					catch (FileAlreadyExistError) {
						std::cout << "Filepath: ";
					}
				}
			}

			std::cout << "The rectengles are " << ((*rect_objects)[0].are_intersect(*rect_objects[1]) ? "intersect " : "not intersect") << std::endl;

			std::cout << "Do you want to save output? Filepath to save, [ENTER] to continue: ";

			getline(std::cin, choice);

			if (choice != "") {
				while (true) {
					try {
						FileOutput file = FileOutput(choice, std::ofstream::trunc);

						file.print("Input and output data of the program \"Intersection of rectangles\"", "\n\n\n");
						file.print("Input data: ", "\n\n");

						for (int r = 0; r < 2; r++) {
							for (int c = 0; c < 8; c++) {
								file.print<double>(rects[r][c]);
							}
						}

						file.print("\nOutput data: \n");
						file.print("The rectangles are ", "");
						file.print(((*rect_objects)[0].are_intersect(*rect_objects[1]) ? "intersect " : "not intersect"));

						break;
					}
					catch (FileAlreadyExistError) {
						std::cout << "Filepath: ";
					}
				}
			}


		}
		else {
			try {
				FileInput input = FileInput(choice, std::ifstream::in);
				double** rects = new double* [2];
				for (int i = 0; i < 2; i++) {
					rects[i] = new double[8];
				}

				Rect** rect_objects = new Rect * [2];

				try {
					for (int r = 0; r < 2; r++) {
						for (int p = 0; p < 4; p++) {
							rects[r][p * 2] = input.get_num<double>();
							rects[r][p * 2 + 1] = input.get_num<double>();
						}

						rect_objects[r] = new Rect(new Point(rects[r][0], rects[r][1]), new Point(rects[r][2], rects[r][3]), new Point(rects[r][4], rects[r][5]), new Point(rects[r][6], rects[r][7]));
					}

					std::cout << "Successful input: ";

					for (int r = 0; r < 2; r++) {
						for (int i = 0; i < 8; i++) {
							std::cout << rects[r][i] << ", ";
						}
					}
					std::cout << std::endl;
					std::cout << "The rectengles are " << ((*rect_objects)[0].are_intersect(*rect_objects[1]) ? "intersect " : "not intersect") << std::endl << std::endl;

					std::cout << "Do you want to save output? Filepath to save, [ENTER] to continue: ";

					getline(std::cin, choice);

					if (choice != "") {
						while (true) {
							try {
								FileOutput file = FileOutput(choice, std::ofstream::trunc);

								file.print("Input and output data of the program \"Intersection of rectangles\"", "\n\n\n");
								file.print("Input data: ", "\n\n");

								for (int r = 0; r < 2; r++) {
									for (int c = 0; c < 8; c++) {
										file.print<double>(rects[r][c]);
									}
								}

								file.print("\nOutput data: \n");
								file.print("The rectangles are ", "");
								file.print(((*rect_objects)[0].are_intersect(*rect_objects[1]) ? "intersect " : "not intersect"));

								break;
							}
							catch (FileAlreadyExistError) {
								std::cout << "Filepath: ";
							}
						}
					}

				}
				catch (ReadNumError) {
					std::cout << "File format error. Please choose another file." << std::endl;
				}
				catch (EOFError) {
					std::cout << "File format error. Please choose another file." << std::endl;
				}
				catch (std::invalid_argument) {
					std::cout << "File format error. Please choose another file." << std::endl;
				}
				catch (FileNotOpenError) {
					std::cout << "Invalid file. " << std::endl;
				}
			}
			catch (FileNotExistError) {
				std::cout << "This file does not exist." << std::endl;
				return;
			}
		}
	}

	void run() {
		std::string choice;
		do {
			std::cout << std::endl;
			loop();
			std::cout << "[ENTER] to exit, any key to continue;";
			getline(std::cin, choice);
		} while (choice != "");
		std::cout << "Bye!";
	}
};
