#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include "bintree.h"
#include "queue.h"

std::ofstream out("output.txt", std::ofstream::out);
std::ifstream input;

void walk_wide(btree tree, queue<base> *nodes) {
		bintree p;
		queue<bintree> q;
		//index of the first entry (tree root) is 2, empty tree is not being processed
		q.push(2);
		while (!q.is_null()) {
			p = q.pop();
			nodes->push(tree.root(p));
			out << "push " << tree.root(p) << std::endl;
			std::cout << "push " << tree.root(p) << std::endl;
			if (!tree.is_null(tree.left(p))) q.push(tree.left(p));
			if (!tree.is_null(tree.right(p))) q.push(tree.right(p));
		}
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


int main(int argc, char* argv[]){
	btree tree = btree();
	queue<base>* nodes = new queue<base>();
	base* str = new base[5000];

	if (argc < 2) {
		std::cout << "Please, enter input string (max 5000 characters):" << std::endl;
		std::cin.getline(str, 5000);
	}
	else {
		input.open(argv[1], std::ifstream::in);
		displayFileContents(&input);
		input.clear();
		input.seekg(0);
		input.getline(str, 5000);
		if (!input.eof()) {
			out << "!-excess characters";
			std::cout << "!-excess characters";
			return 0;
		}
	}

	read_btree(str, tree);

	if (get_index() < (int)strlen(str)) {
		out << "!-excess characters";
		std::cout << "!-excess characters";
		exit(1);
	}
	walk_wide(tree, nodes);

	out << "result: \n";
	std::cout << "result: \n";
	while (!nodes->is_null()) {
		base el;
		el = nodes->pop();
		out << el;
		std::cout << el;
	}
	std::cout << std::endl;

	//for (int i = 1; i < 12; i++) {
	//	std::cout << "i:" << i << ' ' << tree.mem[i].left << ' ' << tree.mem[i].info << ' ' << tree.mem[i].right << std::endl;
	//}
	delete nodes;
	delete [] str;
	std::cin.get();
    return 0;
}

