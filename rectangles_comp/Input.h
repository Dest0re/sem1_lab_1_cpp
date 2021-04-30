#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>


// Ошибка при неудачном считывании числа
struct ReadNumError : std::exception {
private:
	std::string _error_text;

public:
	ReadNumError(std::string error_text) : _error_text{ error_text } {};

	const char* what() {
		return _error_text.c_str();
	}
};

// Ошибка при попытке открыть несуществующий файл
struct FileNotExistError : std::exception {
private:
	std::string _error_text;

public:
	FileNotExistError(std::string error_text) : _error_text{ error_text } {};

	const char* what() {
		return _error_text.c_str();
	}
};

// Ошибка при попытке прочитать файл
struct FileReadingError : std::exception {
private:
	std::string _error_text;

public:
	FileReadingError(std::string error_text) : _error_text{ error_text } {};

	const char* what() {
		return _error_text.c_str();
	}
};

// Ошибка при попытке открыть файл
struct FileNotOpenError : std::exception {
private:
	std::string _error_text;

public:
	FileNotOpenError(std::string error_text) : _error_text{ error_text } {};

	const char* what() {
		return _error_text.c_str();
	}
};

// Ошибка - конец файла
struct EOFError : std::exception {
private:
	std::string _error_text;

public:
	EOFError(std::string error_text) : _error_text{ error_text } {};

	const char* what() {
		return _error_text.c_str();
	}
};

// Абстрактный класс ввода
class InputI {
public:
	// Поток ввода
	std::istream* stream = 0;
	
	// Абстрактный метод получения строки
	virtual std::string get_string() =0;


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


// Класс консольного ввода
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
	// Получение числа
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

	// Конструктор
	ConsoleInput() {
		this->stream = &std::cin;
	}

	// Получение строки
	std::string get_string() {
		return this->_get_string();
	}

	// Получение строки в диапазоне от min до max
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

// Класс файлового ввода
class FileInput : InputI {
private:
	// Путь к файлу
	std::string _filepath;

	// Вывод исключения при достижении конца файла
	void _eof_exc(std::string text = "") {
		throw EOFError("End of a file! " + text);
	}

	// Проверка, доступен ли файл
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
	// Проверка, существует ли файл
	static bool IsFileExist(std::string filepath) {
		std::ifstream file(filepath);
		bool result = file.good();
		file.close();
		return result;
	}

	// Конструктор
	FileInput(std::string filepath, std::ios_base::openmode mode) : _filepath{ filepath } {
		this->stream = new std::ifstream(filepath, mode);

		if (!IsFileExist(filepath)) {
			throw FileNotExistError("File does not exist.");
		}

		if (!static_cast<std::ifstream*>(stream)->is_open()) {
			static_cast<std::ifstream*>(stream)->close();
			throw FileNotOpenError("Error while opening file.");
		}

		if (!IsRegularFile(filepath)) {
			static_cast<std::ifstream*>(stream)->close();
			throw FileNotOpenError("Invalid filepath.");
		}
	}

	// Получение строки
	std::string get_string() {
		if (!static_cast<std::ifstream*>(stream)->eof()) {
			return _get_string();
		}
		else {
			_eof_exc("Error while getting a string.");
			return "";
		}
	}

	// Получение числа
	template <typename T>
	T get_num() {
		if (!static_cast<std::ifstream*>(stream)->eof()) {
			return InputI::_get_num<T>();
		}
		else {
			_eof_exc("Error while getting a num.");
			return 0;
		}
	}

	// Получение числа в диапазоне от min до max
	template <typename T>
	T get_num(T min, T max) {
		if (!static_cast<std::ifstream*>(stream)->eof()) {
			return _get_num<T>(min, max);
		}
		else {
			_eof_exc("Error while getting a num in range.");
			return 0;
		}
	}

	// Деструктор
	~FileInput() {
		if (static_cast<std::ifstream*>(stream)->is_open()) {
			static_cast<std::ifstream*>(stream)->close();
		}
		if (this->stream) delete static_cast<std::ifstream*>(stream);
	}
};