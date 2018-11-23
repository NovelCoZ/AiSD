#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "hlist.h"
#include "alg_expr.h"

typedef h_list::hlist<alg_el>* lisp;

std::ofstream outf("output.txt", std::ofstream::out);
enum err_code {NO_FILE, NO_CLOSING, NO_OPENING, NO_VARIABLE, NOT_ENOUGH_ARGS,\
			   UNEXPECTED_SYM, EXPECTED_OP, TOO_MANY_ARGS, EXCESS_C, EXP_VARIABLE};

lisp lst = NULL;
alg_el* diff = NULL;

//flag for definition of second call for error_handler
bool fin = 0;

void read_expr(lisp& d, int ldepth, alg_el* op, std::istream &in, std::ostream &out);
void read_seq(alg_el* prev, lisp& d, int ldepth, alg_el* op, std::istream &in, std::ostream &out);
void print_expr(const lisp& d, std::ostream& out);
void error_handler(err_code code, std::ostream& out);
void print_seq(const lisp& x, std::ostream& out);

void read_expr(lisp& d, int ldepth, alg_el* op, std::istream &in, std::ostream &out) {
	alg_el* el = NULL;
	lisp p1, p2;
	p1 = NULL;
	p2 = NULL;
	char c;
	do in >> c; while (c == ' ' );

	if (in.eof()) {
		d = NULL;
		return;
	}

	out << ldepth << "." << c;
	for (int i = 0; i < ldepth; i++) out << "\t.";
	out << " ["<< (op ? op->el.str : " ") << "]" << std::endl;

	if (c == '(') {
		read_seq(NULL, p1, 0, NULL, in, out);

		do in >> c; while (c == ' ');
		if (c != ')') error_handler(NO_CLOSING, out);

			if(!isatomic(head(p1)) && !op)
			error_handler(EXPECTED_OP, out);

		read_expr(p2, ldepth + 1, op, in, out);

		d = h_list::cons(p1, p2);
		return;
	}
	else {

		if (c == ')') {
			in.unget();
			if (op) {
				if (!strcmp(op->el.str, "^")) {
					if (ldepth < 3) error_handler(NOT_ENOUGH_ARGS, out); else
						if (ldepth > 3) error_handler(TOO_MANY_ARGS, out);
				}
				else
					if (!strcmp(op->el.str, "exp")) {
						if (ldepth == 0) error_handler(NOT_ENOUGH_ARGS, out);
						else
							if (ldepth > 1) error_handler(TOO_MANY_ARGS, out);
					}
					else
						if (!strcmp(op->el.str, "-")) {
							if (ldepth < 2) error_handler(NOT_ENOUGH_ARGS, out);
						}
						else
							if (ldepth < 3) error_handler(NOT_ENOUGH_ARGS, out);
			}
			else
				error_handler(EXPECTED_OP, out);

			d = NULL;

		}
		else {

			in.unget();
			el = read_el(in);

			if (!el) error_handler(NO_VARIABLE, out);

			if (ldepth == 0) {
				if (!(op && op->el_type == FUNCTION))
						if (el->el_type != OPERATION && el->el_type != FUNCTION) error_handler(EXPECTED_OP, out);
			}

			if (el->el_type == OPERATION) {
				op = el;
				if (op && op->el_type == FUNCTION && ldepth == 1);
				else
					if (ldepth != 0) error_handler(UNEXPECTED_SYM, out);
			}
			else {

				if (el->el_type == FUNCTION) {
					do in >> c; while (c == ' ');
					if (c != '(') error_handler(NO_OPENING, out);

					out << ldepth << "." << c;
					for (int i = 0; i < ldepth; i++) out << "\t.";
					out << " [" << (op ? op->el.str : " ") << "]" << std::endl;


					lisp p3 = h_list::make_atom(*el);
					read_seq(NULL, p1, 0, el, in, out);
					lisp p4;

					if (!isatomic(head(p1)) || (h_list::get_atom(head(p1)).el_type == VARIABLE \
										      || h_list::get_atom(head(p1)).el_type == NUMBER))
					{
						p4 = h_list::cons(p3, p1);
					}
					else {
						lisp nil = NULL;
						p4 = h_list::cons(p3, h_list::cons(p1, nil));
					}
					do in >> c; while (c == ' ');
					if (c != ')') error_handler(NO_CLOSING, out);
					
					read_expr(p2, ldepth + 1, op, in, out);
					d = h_list::cons(p4, p2);
					return;
				}
				else {
					if (!op) error_handler(EXCESS_C, out);
				}
			}
			
			read_seq(el, p1, ldepth + 1, op, in, out);
			read_expr(p2, ldepth + 1, op, in, out);
			d = h_list::cons(p1, p2);
		}
	}
}

void error_handler(err_code code, std::ostream& out) {

	out << "\n! - ";
	switch (code) {
	case NO_FILE:
		out << "No input file."; 
		std::cout << "No input file. Please, pass input file as an argument to program \
(or click and drag input file onto executable file).\n";
		break;
	case NO_CLOSING: out << "Expected closing bracket"; break;
	case NOT_ENOUGH_ARGS: out << "Not enough arguments"; break;
	case UNEXPECTED_SYM: out << "Unexpected symbol"; break;
	case EXPECTED_OP: out << "Expected operation"; break;
	case TOO_MANY_ARGS:out << "Too many arguments"; break;
	case NO_OPENING: out << "Expected opening bracket"; break;
	case EXCESS_C: out << "Excess characters"; break;
	case NO_VARIABLE: out << "Expected variable or constant as an argument"; break;
	case EXP_VARIABLE: out << "Expected variable"; break;
	}
	out << '\n';
	if (fin == 0) {
		fin = 1;
		error_handler(code, std::cout);
	}

	h_list::destroy(lst);
	#ifdef _WIN32
		system("PAUSE");
	#endif
	exit(1);
}

void read_seq(alg_el* prev, lisp& d, int ldepth, alg_el* op, std::istream &in, std::ostream &out) {
	if (prev) {
		d = h_list::make_atom(*prev);
	}
	else read_expr(d, ldepth, op, in, out);
}

void print_expr(const lisp& d, std::ostream& out)
{
	if (h_list::empty(d)) out << "()";
	else if (h_list::isatomic(d)) { 
		print_el(out, &h_list::get_atom(d));
		out << ' ';
	}
	else {
		if (h_list::isatomic(h_list::head(d)) && head(d)->node.atom.el_type == FUNCTION) {
			if (h_list::isatomic(head(h_list::tail(d)))) {
				print_el(out, &h_list::get_atom(head(d)));
				print_expr(tail(d), out);
			}
			else {
				print_el(out, &h_list::get_atom(head(d)));
				print_expr(head(tail(d)), out);
			}
		}
		else {
			out << "( ";
			print_seq(d, out);
			out << ") ";
		}
	}
} 

void print_seq(const lisp& x, std::ostream& out)
{
	if (!h_list::empty(x)) {
		print_expr(head(x), out);
		print_seq(tail(x), out);
	}
}

lisp derivative(const lisp& d);
lisp derivPM(const lisp& c);
lisp derivMul(const lisp& c, int depth);
lisp derivPow(const lisp& c, int step);
lisp derivExp(const lisp& c);

lisp derivPM(const lisp& c) {
	//(a +- b +- c +- ...)' = a' +- b' +- c' +- ...
	if (h_list::empty(c)) return NULL;
	return h_list::cons( derivative(h_list::head(c)), derivPM( h_list::tail(c) ));
}

lisp derivMul(const lisp& c, int depth) {
	//(a*b*c*...)' = a'*b*c*... + a*b'*c*... + a*b*c'*... + ...
	lisp x;
	x = h_list::copy(c);
	lisp d;
	d = x;
	for (int i = 0; i < depth; i++) {
		d = tail(d);
	}
	if (h_list::empty(d)) return NULL;
	lisp j = NULL;
	j = derivative(h_list::head(d));
	*head(d) = *j;
	return h_list::cons(x, derivMul(c, depth + 1));
}

lisp derivPow(const lisp& c, int step) {
	//(u^v)' = v*u^(v-1)*u' + u^(v)*v'*ln(u)
	lisp nil = NULL;
	switch (step) {
	case 0: return h_list::cons(h_list::make_atom(*make_el("+", OPERATION)), derivPow(c,1));
	case 1: return h_list::cons(derivPow(c, 2), h_list::cons(derivPow(c, 9), nil));
	case 2: return h_list::cons(h_list::make_atom(*make_el("*", OPERATION)), derivPow(c, 3));
	case 3: return h_list::cons(h_list::copy(head(tail(c))), h_list::cons(derivPow(c, 4),\
				   h_list::cons(derivative(head(c)),nil)));
	case 4: return h_list::cons(h_list::make_atom(*make_el("^", OPERATION)), derivPow(c,5));
	case 5: return h_list::cons(h_list::copy(head(c)), h_list::cons(derivPow(c, 6), nil));
	case 6: return h_list::cons(h_list::make_atom(*make_el("-", OPERATION)), derivPow(c, 7));
	case 7: return h_list::cons(h_list::copy(head(tail(c))), derivPow(c, 8));
	case 8: return h_list::cons(h_list::make_atom(*make_el(1, NUMBER)), nil);
	case 9: return h_list::cons(h_list::make_atom(*make_el("*", OPERATION)), derivPow(c, 10));
	case 10: return h_list::cons(derivPow(c,11), h_list::cons(derivative(head(tail(c))),derivPow(c,12)));
	case 11: return h_list::cons(h_list::make_atom(*make_el("^", OPERATION)),\
				    h_list::cons(h_list::copy(head(c)), h_list::cons(h_list::copy(head(tail(c))), nil)));
	case 12: return h_list::cons(h_list::make_atom(*make_el("ln", FUNCTION)),\
					h_list::cons(h_list::copy(head(c)), nil));
	default: break;
	}
	return NULL;
}

lisp derivExp(const lisp& c){
	//(e^u)' = u'*e^u
	lisp nil = NULL;
	lisp ex = h_list::copy(c);
	return h_list::cons(h_list::make_atom(*make_el("*", OPERATION)),\
		   h_list::cons(derivative(head(tail(c))), h_list::cons(ex, nil)));
}

lisp derivative(const lisp& d) {
	if (h_list::empty(d)) return NULL;
	lisp res = NULL;
	lisp c = NULL;

	alg_el* nil = make_el(0,NUMBER);

	if (h_list::isatomic(d)) {

		if (h_list::get_atom(d).el_type == VARIABLE) {
			if (!strcmp(h_list::get_atom(d).el.str , diff->el.str)) {
				res = h_list::make_atom(*nil);
				std::cout << "Met diff\n";
				res->node.atom.el.num = 1;
			}
			else {
				std::cout << "Met var\n";
				res = h_list::make_atom(*nil);
			}
		} else
		if (h_list::get_atom(d).el_type == NUMBER) {
			std::cout << "Met const\n";
			res = h_list::make_atom(*nil);
		}
		return res;

	} else

		if (h_list::isatomic(head(d))) {
			if (!strcmp(h_list::get_atom(head(d)).el.str, "+") \
				|| !strcmp(h_list::get_atom(head(d)).el.str, "-")) {
				std::cout << "Met +-\n";
				c = tail(d);
				lisp p1 = derivPM(c);
				lisp atm = h_list::make_atom(h_list::get_atom(head(d)));
				res = h_list::cons(atm, p1);
				std::cout << "Exiting +-\n";
				return res;
			}
			if (!strcmp(h_list::get_atom(head(d)).el.str, "*")) {
				std::cout << "Met *\n";
				c = d;
				lisp p1 = derivMul(c, 1);
				lisp atm = h_list::make_atom(*make_el("+", OPERATION));
				res = h_list::cons(atm, p1);
				std::cout << "Exiting *\n";
				return res;
			}
			if (!strcmp(h_list::get_atom(head(d)).el.str, "^")) {
				std::cout << "Met ^\n";
				res = derivPow(tail(d), 0);
				std::cout << "Exiting ^\n";
				return res;
			}
			if (!strcmp(h_list::get_atom(head(d)).el.str, "exp")) {
				std::cout << "Met exp\n";
				res = derivExp(d);
				std::cout << "Exiting exp\n";
				return res;
			}
		}
		else
			return derivative(head(d));
	return NULL;
}

void displayFileContents(std::ifstream* in) {
	std::cout << "File contents:\n";
	std::cout << "-begin-\n";
	char c;
	c = in->get();
	while (!in->eof()) {
		std::cout << c;
		c = in->get();
	}
	std::cout << "\n-end-\n";
}

int main(int argc, char* argv[]) {

	if (argc != 2) {
		std::cout << "Please, enter the variable for which you want to take the derivative.\n";
		diff = read_el(std::cin);
		if (!diff || diff->el_type != VARIABLE) error_handler(EXP_VARIABLE, outf);
		std::cout << "Enter algebraic function (use ctrl-Z (ctrl-D for unix) to determine end of input):\n";
		read_expr(lst, 0, NULL, std::cin, outf);
		if (!std::cin.eof()) error_handler(EXCESS_C, outf);
	}
	else {
		std::ifstream in(argv[1], std::ifstream::in);
		//std::ifstream in("test.txt", std::ifstream::in);
		displayFileContents(&in);
		in.clear();
		in.seekg(0);		
		diff = read_el(in);

		if (!diff) {
			std::cout << "Please, enter the variable for which you want to take the derivative.\n";
			diff = read_el(std::cin);
		}	
		if (diff->el_type != VARIABLE) error_handler(NO_VARIABLE, outf);
		read_expr(lst, 0, NULL, in, outf);
		if (!in.eof()) error_handler(EXCESS_C, outf);
	}

	lisp res = NULL;
	res = derivative(lst);
	outf << "derivative:\n";
	std::cout << "derivative:\n";
	print_expr(res, outf);
	print_expr(res, std::cout);

	std::cout << '\n';
#ifdef _WIN32
	system("PAUSE");
#endif
	h_list::destroy(lst);
	h_list::destroy(res);
    return 0;
}

