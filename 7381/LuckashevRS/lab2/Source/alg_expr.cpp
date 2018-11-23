#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "alg_expr.h"

	alg_el* read_el(std::istream &input) {
		if (input.eof()) return NULL;
		char* n = new char;
		int i = 0;
		alg_el* el = new alg_el;
		do {
			*(n + i) = input.get();
		} while ((*(n + i) == ' ') && input.eof());

		input.unget();
		while (input.good()) {
			*(n + i) = input.get();
			if (input.eof()) break;
			if (*(n + i) == ' ') break;
			if (*(n + i) == '\n') break;
			if (*(n + i) == '(' || *(n + i) == ')') {
				input.unget();
				break;
			}
			i++;
			n = (char*)realloc(n, (i + 1) * sizeof(char));
		}
		if ((i == 0) || ((*n == '(') || (*n == ')'))) return NULL;
		*(n + i) = '\0';
		if ((strcmp(n, "+")) && (strcmp(n, "-")))
		if (i != 0) {
			i--;
			for (i; i >= 0; i--) {
				if ((i == 0) && (*(n + i) == '-') || *(n + i) == '+') continue;
				if ((*(n + i) >= '0') && (*(n + i) <= '9')) continue;
				else break;
			}
		}
		if (i == -1) {
			el->el_type = NUMBER;
			el->el.num = atoll(n);
		}
		else {
			if (!strcmp(n, "exp")) el->el_type = FUNCTION;
			else
				if (!(strcmp(n, "+")) || !(strcmp(n, "-")) || !(strcmp(n, "*")) || !(strcmp(n, "^"))) {
					el->el_type = OPERATION;
					//el->el.str = n;
				}
				else {
					for (i = 0; i < strlen(n); i++)
						if (!isalpha(*(n + i))) return NULL;
					el->el_type = VARIABLE;
					//el->el.str = n;
				}
		el->el.str = n;
		}
		return el;
	}

	void print_el(std::ostream &output, alg_el* el) {
		if (el) {
			switch (el->el_type) {
			case NUMBER: output << el->el.num; break;
			case OPERATION: output << el->el.str; break;
			case VARIABLE: output << el->el.str; break;
			case FUNCTION: output << el->el.str; break;
			}
		}
	}

	alg_el* make_el(const char* str, type t) {
		alg_el* res = new alg_el();
		res->el.str = (char*)malloc(4 * sizeof(char));
		res->el_type = t;
		strcpy(res->el.str, str);
		return res;
	}

	alg_el* make_el(int num, type t) {
		alg_el* res = new alg_el();
		res->el_type = t;
		res->el.num = num;
		return res;
	}