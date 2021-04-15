#pragma once
#include <iostream>
#include <ostream>
#include <filesystem>
#include <fstream>

struct WriteError : std::exception {
private:
	std::string _error_text;

public:
	WriteError(std::string error_text) : _error_text{ error_text } {};

	const char* what() {
		return _error_text.c_str();
	}
};

struct FileNotExistError : std::exception {
private:
	std::string _error_text;

public:
	FileNotExistError(std::string error_text) : _error_text{ error_text } {};

	const char* what() {
		return _error_text.c_str();
	}
};

struct FileAlreadyExistError : std::exception {
private:
	std::string _error_text;

public:
	FileAlreadyExistError(std::string error_text) : _error_text{ error_text } {};

	const char* what() {
		return _error_text.c_str();
	}
};

class OutputI {
protected:
	template <typename T>
	bool _print(T value, std::string end = "\n") {
		
		if (!(*stream << value)) throw WriteError("Error while writing data.");

		if (stream->fail()) {
			stream->clear();

			throw WriteError("Error while writing data");
		}
		
		return true;
	}

public:
	std::ostream* stream = nullptr;
};

class ConsoleOutput : OutputI {
public:
	ConsoleOutput() {
		stream = &std::cout;
	}

	template <typename T>
	bool print(T value, std::string end = "\n") {
		try {
			return _print(value, end);
		}
		catch (WriteError) {
			return false;
		}
	}
};

class FileOutput : OutputI {
private:
	std::string _filepath;
public:

	static bool IsFileExist(std::string filepath) {
		std::ifstream file(filepath);
		bool result = file.good();
		file.close();
		return result;
	}

	static bool TryToOverwrite(std::string filepath) {
		if (IsFileExist(filepath)) {
			std::string user_choice;
			std::cout << "File already exists. [ENTER] to overwrite, any symbol to return:" << std::endl;
			getline(std::cin, user_choice);
			return user_choice == "";
		}
		return true;
	}

	FileOutput(std::string filepath, std::ios_base::openmode mode) : _filepath{ filepath } {
		if (!IsFileExist(filepath)) {
			throw FileNotExistError("File does not exist.");
		}

		if (!TryToOverwrite(filepath)) {
			throw FileAlreadyExistError("File already exist.");
		}

		stream = &std::ofstream(filepath, mode);
	}
};
