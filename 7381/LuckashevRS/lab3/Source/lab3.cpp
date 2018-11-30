#include "stack.h"
#include <fstream>
#include <iostream>

std::ofstream out("output.txt", std::ofstream::out);
std::ofstream inter_data("interData.txt", std::ofstream::out);
std::ifstream input;

void printLine(stack<char>* s) {
	char c;

	while (!s->empty()) {
		c = s->pop();
		inter_data << "pop [" << c << ']' << std::endl;
		if (c == '\n') continue;
		std::cout << c;
		out << c;
	}

	std::cout << '\n';
	out << '\n';
}

void displayFileContents(std::istream* in) {
	std::cout << "File contents:\n";
	out << "File contents:\n";
	std::cout << "-begin-\n";
	out << "-begin-\n";
	char c;
	c = in->get();
	while (!in->eof()) {
		std::cout << c;
		out << c;
		c = in->get();
	}
	std::cout << "\n-end-\n";
	out << "\n-end-\n";
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		std::cout << "Please, open this application with input file as an argument (drag the input file onto executable file).\n";
		return 0;
	}
	else {
		input.open(argv[1], std::ifstream::in);
		displayFileContents(&input);
		input.clear();
		input.seekg(0);
	}
	//input.open("test.txt", std::ifstream::in);
	stack<char> s;

	char c;

	c = input.get();
	while (!input.eof()) {
		s.push(c);
		inter_data << "push [" << c << ']' << std::endl;
		c = input.get();
		if(s.top() == '\n') printLine(&s);
	}
	
	printLine(&s);
#ifdef _WIN32
	system("PAUSE");
#endif
    return 0;
}

