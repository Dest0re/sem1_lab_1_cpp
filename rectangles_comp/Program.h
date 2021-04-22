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
				FileOutput file = open_file_for_output(choice);

				for (int r = 0; r < 2; r++) {
					for (int c = 0; c < 8; c++) {
						file.print<double>(rects[r][c]);
					}
				}

				std::cout << "Successful save." << std::endl;
			}

			std::cout << "The rectengles are " << ((*rect_objects)[0].are_intersect(*rect_objects[1]) ? "intersect " : "not intersect") << std::endl;

			std::cout << "Do you want to save output? Filepath to save, [ENTER] to continue: ";

			getline(std::cin, choice);

			if (choice != "") {
				FileOutput file = open_file_for_output(choice);

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

				std::cout << "Successful save." << std::endl;
			}
		}
		else {
			FileInput input = open_file_for_input(choice);
			double** rects = new double* [2];
			for (int i = 0; i < 2; i++) {
				rects[i] = new double[8];
			}

			Rect** rect_objects = new Rect* [2];

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
					FileOutput file = open_file_for_output(choice);

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

					std::cout << "Successful save." << std::endl;
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
