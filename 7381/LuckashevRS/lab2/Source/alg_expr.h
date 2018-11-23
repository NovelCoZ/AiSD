#pragma once
#include <fstream>
#include <iostream>
#include "hlist.h"

	enum type { VARIABLE, NUMBER, OPERATION, FUNCTION };

	struct alg_el {

		type el_type;

		union {
			long long num;
			char* str;
		} el;
	};

	alg_el* read_el(std::istream &input);

	void print_el(std::ostream &output, alg_el* el);

	alg_el* make_el(const char* str, type t);
	alg_el* make_el(int num, type t);