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

		*stream << end;

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

		std::ifstream file(filepath, std::ifstream::in);
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

	template <typename T>
	bool print(T value, std::string end = "\n") {
		try {
			return _print(value, end);
		}
		catch (WriteError) {
			return true;
		}
	}

	FileOutput(std::string filepath, std::ios_base::openmode mode) : _filepath{ filepath } {
		std::error_code ec;
		if (!std::filesystem::is_regular_file(filepath, ec)) {
			throw FileNotOpenError("File cannot be open");
		}

		if (!TryToOverwrite(filepath)) {
			throw FileAlreadyExistError("File already exist.");
		}

		stream = new std::ofstream(filepath, mode);
	}

	~FileOutput() {
		static_cast<std::ofstream*>(stream)->close();
		delete stream;
	}
};
