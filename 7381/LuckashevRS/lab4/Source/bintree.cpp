#include "bintree.h"
#include <fstream>
#include <stdlib.h>
#include <iostream>

int index_ = 0;
std::ofstream inter_data("interData.txt", std::ofstream::out);

int get_index(){
	return index_;
}
//base == char
base read_el(base* str) {
	base el;
	while (*(str + index_) == ' ') index_++;
	el = *(str + index_);
	index_++;
	return el;
}
//example (a(b(#)(d))(c(e(f)(g))(#)))
bintree read_btree(base* str, btree tree) {

	bintree res = 0;
	if (index_ > strlen(str)) error_handler();
	while (*(str + index_) == ' ') index_++;
	if (*(str + index_) == ')') {

		return 0;
	}
	if (*(str + index_) == '(') {

		index_++;
		base el = read_el(str);
		if (el == ')' || el == '(') error_handler();
		if (el == '#') {

			inter_data << "met empty leaf" << std::endl;

		}
		else {
			res = tree.create_node(el);

			inter_data << "create node " << el << std::endl;

			bintree left = read_btree(str, tree);
			while (*(str + index_) == ' ') index_++;
			bintree right = read_btree(str, tree);
			while (*(str + index_) == ' ') index_++;
			tree.insert_children(res, left, right);
			inter_data << "cons " << tree.root(res) << ' ' << tree.root(left) << ' ' << tree.root(right) << std::endl;
		}
	}
	if (*(str + index_) != ')') error_handler();

	index_++;
	return res;
}

void error_handler() {
	std::cout << "Input error" << std::endl;
	std::cin.get();
	exit(1);
}