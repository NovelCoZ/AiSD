#pragma once
#include <stdlib.h>
//shortened queue class
template <class base> class queue {
private:
	struct node {
		base el;
		node* prev;
		node() {
			prev = NULL;
		}
	};
	node* first = NULL;
	node* last = NULL;
public:

	queue() {
		first = NULL;
		last = NULL;
	}

	bool is_null() {
		return !first;
	}

	void push(base element) {
		node* p = new node();
		p->el = element;
		if (first == NULL) {
			last = p;
			first = p;
			return;
		}
		last->prev = p;
		last = p;
	}

	base pop() {
		base res;
		if (first) res = first->el;
		node* prev;
		prev = first->prev;
		delete first;
		first = prev;
		return res;
	}

};