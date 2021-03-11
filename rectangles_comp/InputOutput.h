#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <malloc.h>
#include "geometry/Rect.h"

class InputOutput {
public:
	std::istream* istream;
	std::ostream* ostream;

	InputOutput(std::istream* = &std::cin, std::ostream* = &std::cout);

	static std::string get_string(std::istream* stream) {
		std::string str = "";
		std::getline(*stream, str);
		return (str != "" ? str : "\n");
	}

	std::string get_string();

	static char get_char(std::istream* stream) {
		std::string str = get_string(stream);
		return str[0];
	}

	char get_char();

	std::ostream& operator<<(std::string);

	std::ostream& operator<<(const long long num);

	std::ostream& operator<<(const long double num);

	std::istream& operator>>(std::string&);

	template <typename T>
	T get_num() {
		T num = 0;
		std::string str;
		std::stringstream ss;
		*this >> str;
		ss << str;
		ss >> num;

		while (ss.fail()) {
			if (istream == &std::cin) {
				print("Error! Enter the correct number!");
				ss.clear();
				ss.ignore();
				ss << str;
				ss >> num;
				continue;
			}
			else {
				print("Error! Number input isn't correct!");
				throw std::invalid_argument("Invalid number");
			}
		}
		return num;
	}

	static void print(std::string str, std::ostream* ostream, std::string end = "\n") {
		*ostream << str + end;
	};

	static void print(long long num, std::ostream* ostream, std::string end = "\n") {
		*ostream << std::to_string(num) + end;
	};

	static void print(long double num, std::ostream* ostream, std::string end = "\n") {
		*ostream << std::to_string(num) + end;
	}

	void print(std::string, std::string = "\n");

	void print(long long num, std::string = "\n");

	void print(long double num, std::string = "\n");

	template <typename T>
	static void print_arr(T *arr, std::ostream* stream, std::string sep=" ") {
		int size = _msize(arr) / sizeof(T);
		
		for (int i = 0; i < size; i++) {
			*stream << arr[i] << sep;
		}
	}

	template <typename T>
	void print_arr(T* arr, std::string sep = " ") {
		print_arr<T>(arr, ostream, sep);
	}

	bool file_exists(std::string filepath) {

	}

	bool file_exists_and_correct(std::string filepath) {
		
	}
};
