#include <string>
#include <istream>
#include <ostream>
#include <fstream>
#include <fcntl.h>
#include <io.h>
#include "InputOutput.h"

InputOutput::InputOutput(std::istream *input_stream, std::ostream *output_stream) {
	istream = input_stream;
	ostream = output_stream;
}

std::string InputOutput::get_string() {
	return get_string(istream);
}

char InputOutput::get_char() {
	return get_char(istream);
}

void InputOutput::print(std::string str, std::string end) {
	print(str, ostream, end);
}

void InputOutput::print(long long num, std::string end) {
	print(num, ostream, end);
}

void InputOutput::print(long double num, std::string end) {
	print(num, ostream, end);

}

std::ostream& InputOutput::operator<<(std::string str) {
	print(str, "");
	return *ostream;
}

std::ostream& InputOutput::operator<<(const long long num) {
	print(num, "");
	return *ostream;
}

std::ostream& InputOutput::operator<<(const long double num) {
	print(num, "");
	return *ostream;
}

std::istream& InputOutput::operator>>(std::string& str) {
	str += get_string();
	return *istream;
}

