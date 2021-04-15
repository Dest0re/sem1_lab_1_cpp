#pragma once
#include <string>
#include <istream>
#include <iostream>
#include <fstream>
#include <filesystem>


struct ReadNumError : std::exception {
private:
	std::string _error_text;

public:
	ReadNumError(std::string error_text) : _error_text{ error_text } {};

	const char* what() {
		return _error_text.c_str();
	}
};

struct FileReadingError : std::exception {
private:
	std::string _error_text;

public:
	FileReadingError(std::string error_text) : _error_text{ error_text } {};

	const char* what() {
		return _error_text.c_str();
	}
};

struct FileNotOpenError : std::exception {
private:
	std::string _error_text;

public:
	FileNotOpenError(std::string error_text) : _error_text{ error_text } {};

	const char* what() {
		return _error_text.c_str();
	}
};

struct EOFError : std::exception {
private:
	std::string _error_text;

public:
	EOFError(std::string error_text) : _error_text{ error_text } {};

	const char* what() {
		return _error_text.c_str();
	}
};

class InputI {
public:
	std::istream* stream = 0;


	virtual std::string get_string() = 0;


	// Получение строки.
	std::string _get_string() {
		std::string str;
		std::getline(*stream, str);

		return (str != "" ? str : "\n");
	}

	// Получение числа типа T, ReadNumException при неудаче.
	template <typename T>
	T _get_num() {
		T number;
		*stream >> number;

		if (stream->fail()) {
			stream->clear();
			stream->ignore(INT_MAX, '\n');

			throw ReadNumError("Error while reading a number");
		}

		stream->ignore(INT_MAX, '\n');

		return number;
	}
};


class ConsoleInput : InputI {

private:

	// Получение числа типа double в диапазоне от min до max, range_error при неудаче.
	template <typename T>
	T _get_num(T min, T max) {
		T number = get_num<T>();

		if (number >= min && number <= max) {
			return number;
		}
		else {
			throw std::range_error("Number must be in provided range");
		}
	}


public:
	template <typename T>
	T get_num() {
		while (true) {
			try {
				return InputI::_get_num<T>();
			}
			catch (ReadNumError e) {
				std::cout << "Wrong number! Try again:" << std::endl;
			}
		}
	}

	ConsoleInput() {
		this->stream = &std::cin;
	}

	std::string get_string() {
		return this->_get_string();
	}

	template <typename T>
	T get_num(T min, T max) {
		while (true) {
			try {
				return _get_num<T>(min, max);
			}
			catch (std::range_error e) {
				std::cout << "Number not in range! Please enter the num between " << min << " and " << max << ":" << std::endl;
			}
		}
	}

};


class FileInput : InputI {
private:
	std::string _filepath;

	void eof_exc(std::string text = "") {
		throw EOFError("End of a file! " + text);
	}

	static bool IsRegularFile(std::string filepath) {
		std::error_code ec;

		return std::filesystem::is_regular_file(filepath, ec);
	}

	// Получение числа типа double в диапазоне от min до max, range_error при неудаче.
	template <typename T>
	T _get_num(T min, T max) {
		T number = get_num<T>();

		if (number >= min && number <= max) {
			return number;
		}
		else {
			throw std::range_error("Number must be in provided range");
		}
	}

public:
	FileInput(std::string filepath, std::ios_base::openmode mode) : _filepath{ filepath } {
		this->stream = new std::ifstream(filepath, mode);

		if (!static_cast<std::ifstream*>(stream)->is_open()) {
			static_cast<std::ifstream*>(stream)->close();
			throw FileNotOpenError("Error while opening file.");
		}

		if (!IsRegularFile(filepath)) {
			static_cast<std::ifstream*>(stream)->close();
			throw FileNotOpenError("Invalid filepath.");
		}
	}


	std::string get_string() {
		if (!static_cast<std::ifstream*>(stream)->eof()) {
			return _get_string();
		}
		else {
			eof_exc("Error while getting a string.");
		}
	}

	template <typename T>
	T get_num() {
		if (!static_cast<std::ifstream*>(stream)->eof()) {
			return InputI::_get_num<T>();
		}
		else {
			eof_exc("Error while getting a num.");
		}
	}

	template <typename T>
	T get_num(T min, T max) {
		if (!static_cast<std::ifstream*>(stream)->eof()) {
			return _get_num<T>(min, max);
		}
		else {
			eof_exc("Error while getting a num in range.");
		}
	}

	~FileInput() {
		static_cast<std::ifstream*>(stream)->close();
		delete stream;
	}
};