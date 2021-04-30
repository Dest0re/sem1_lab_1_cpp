#pragma once
#include <iostream>

#include "geometry/Rect.h"
#include "new_input.h"
#include "new_output.h"
#include "DebugSet.h"

const std::string greeting_string =
"Starikov Danil, 404 gr. variation 10, task 1.\n\n"
"Please enter the coordinates of the points in the specified sequence:\n"
" 1+----------------+2 \n"
"  |                |  \n"
"  |                |  \n"
"  |                |  \n"
" 4+----------------+3 \n";

namespace Program {
	void greeting() {
		std::cout << greeting_string << std::endl;
	}

	FileOutput open_file_for_output(std::string filepath) {
		while (true) {
			try {
				return FileOutput(filepath, std::ofstream::trunc);
			}
			catch (FileAlreadyExistError) {
				std::cout << "Filepath: ";
			}
			catch (FileNotOpenError) {
				std::cout << "File cannot exist. Filepath: ";
			}
			getline(std::cin, filepath);
		}
	}

	void save_output(std::string filepath, double** rects, bool result) {
		FileOutput file = Program::open_file_for_output(filepath);

		file.print("Input and output data of the program \"Intersection of rectangles\"", "\n\n\n");
		file.print("Input data: ", "\n\n");

		for (int r = 0; r < 2; r++) {
			for (int c = 0; c < 8; c += 2) {
				file.print("[ ", "");
				file.print(rects[r][c], "");
				file.print("; ", "");
				file.print(rects[r][c + 1], "");
				file.print(" ]\n");
			}
		}

		file.print("\nOutput data: \n");
		file.print("The rectangles are ", "");
		file.print(result ? "intersect " : "not intersect");

		std::cout << "Successful save." << std::endl;
	}

	void ask_for_debug() {
		std::string choice;

		std::cout << "Run tests? [ENTER] to run, any letter to continue; ";
		getline(std::cin, choice);

		if (choice != "") return;

		DebugSet set = DebugSet();

		Rect* r1 = nullptr;
		Rect* r2 = nullptr;

		int result;

		for (int i = 0; i < set.size; i++) {
			try {
				r1 = new Rect(set.datasets[i][0]);
				r2 = new Rect(set.datasets[i][1]);

				result = static_cast<int>(r1->are_intersect(*r2));
			}
			catch (std::invalid_argument) {
				result = -1;
			}

			if (result != set.results[i]) {
				std::cout << "Its an ERROR occured while passing the tests!" << std::endl;
				std::cout << "Test #" << i + 1 << " failed!" << std::endl << std::endl;
				std::cout << "Dataset: " << std::endl << std::endl;

				for (int r = 0; r < 2; r++) {
					std::cout << "Rect #" << r + 1 << ": " << std::endl;

					for (int c = 0; c < 8; c += 2) {
						std::cout << "[ " << set.datasets[i][r][c] << "; " << set.datasets[i][r][c + 1] << " ]" << std::endl;
					}
				}

				std::cout << std::endl << "Expected result: " << DebugSet::get_result_text(set.results[i]) << std::endl;
				std::cout << "Real result: " << DebugSet::get_result_text(result) << std::endl;

				std::cout << "The program will be terminated immediately!" << std::endl << std::endl << std::endl;

				std::cout << "Sorry!" << std::endl;

				exit(2);
			}
		}

		std::cout << "All the tests passed successfully!" << std::endl << std::endl;

		delete r1;
		delete r2;
	}

	FileInput open_file_for_input(std::string filepath) {
		while (true) {
			try {
				return FileInput(filepath, std::ifstream::in);
			}
			catch (FileNotExistError) {
				std::cout << "File does not exist. Filepath: ";
				getline(std::cin, filepath);
			}
			catch (FileNotOpenError) {
				std::cout << "File does not exist. Filepath: ";
				getline(std::cin, filepath);
			}
		}
	}


	bool read_rects_from_file(double** rects, Rect** rect_objects, FileInput &input) {
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
		}
		catch (ReadNumError) {
			return false;
		}
		catch (EOFError) {
			return false;
		}
		catch (std::invalid_argument) {
			return false;
		}
		catch (FileNotOpenError) {
			return false;
		}

		return true;
	}

	void read_rects_from_console(double** rects, Rect** rect_objects) {
		ConsoleInput input = ConsoleInput();
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
	}

	void ask_for_input_save(double** rects) {
		std::string choice;


		std::cout << "Do you want to save input to file? [ENTER] for \"no\", filepath to save: ";

		getline(std::cin, choice);


		if (choice != "") {
			FileOutput file = open_file_for_output(choice);

			for (int r = 0; r < 2; r++) {
				for (int c = 0; c < 8; c++) {
					file.print<double>(rects[r][c]);
				}
			}

			std::cout << "Successful save." << std::endl;
		}
	}

	void ask_for_output_save(double** rects, bool result) {
		std::string filepath;

		std::cout << "Do you want to save output? Filepath to save, [ENTER] to continue: ";

		getline(std::cin, filepath);

		if (filepath != "") Program::save_output(filepath, rects, result);
	}


	void loop() {
		double** rects = new double*[2];
		for (int i = 0; i < 2; i++) {
			rects[i] = new double[8];
		}
		Rect** rect_objects = new Rect*[2];

		std::cout << "Choose input method. [ENTER] for console input, filepath for input from file: ";
		
		std::string choice;
		getline(std::cin, choice);
		
		std::cout << std::endl;

		if (choice == "") {
			Program::read_rects_from_console(rects, rect_objects);
			bool result = (*rect_objects)[0].are_intersect(*rect_objects[1]);

			Program::ask_for_input_save(rects);

			std::cout << "The rectengles are " << ((*rect_objects)[0].are_intersect(*rect_objects[1]) ? "intersect " : "not intersect") << std::endl;

			Program::ask_for_output_save(rects, result);
		}

		else {
			FileInput input = Program::open_file_for_input(choice);

			if (!read_rects_from_file(rects, rect_objects, input)) {
				std::cout << "Invalid file. Please choose another one." << std::endl;
				return;
			}

			bool result = (*rect_objects)[0].are_intersect(*rect_objects[1]);

			std::cout << std::endl;
			std::cout << "The rectengles are " << (result ? "intersect " : "not intersect") << std::endl << std::endl;

			Program::ask_for_output_save(rects, result);
		}

		for (int i = 0; i < 2; i++) {
			delete rects[i];
			delete rect_objects[i];
		}
		delete[] rects;
		delete[] rect_objects;
	}

	void run() {
		Program::greeting();
		Program::ask_for_debug();

		std::string choice;
		do {
			std::cout << std::endl;
			Program::loop();
			std::cout << "[ENTER] to exit, any key to continue;";
			getline(std::cin, choice);
		} while (choice != "");
		std::cout << "Bye!" << std::endl;
	}
};
