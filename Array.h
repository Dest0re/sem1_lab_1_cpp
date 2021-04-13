#pragma once
#include <iostream>
#include <assert.h>


class InvalidArraySize : std::exception {
private:
	std::string _error_text;

public:
	InvalidArraySize(std::string error_text) : _error_text{ error_text } {};

	const char* what() {
		return this->_error_text.c_str();
	}
};

template <int length, class T>
class Array {
private:
	T* _data;
	int _length;

public:
	Array() {
		_data = nullptr;
		_length = 0;
	}

	template <int length, typename T>
	Array(bool clear = true) {
		if (length < 0) {
			throw InvalidArraySize("Please provide correct array length");
		}

		_length = length;
		_data = new T[length];

		if (clear) {
			for (int i = 0; i < length; i++) {
				_data[i] = 0;
			}
		}
	}

	~Array() {
		delete[] _data;
	}

	void Erase() {
		delete[] _data;
		_data = nullptr;
		_length = 0;
	}

	T& operator[](const int index) {
		assert(index >= 0 && index < _length);
		return this->_data[index];
	}

	int getLength() {
		return _length;
	}

	void Print(std::ostream& stream = &std::cout, std::string sep = " ", std::string end = "") {
		for (int i = 0; i < _length-1; i++) {
			stream << this->_data[i] << sep;
		}
		stream << this->_data[_length - 1] << end;
	}
};


void test() {
	Array a = Array<1, int>();
	a[0] = 0;
}
