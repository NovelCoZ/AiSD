#pragma once
#include <stdlib.h>
template <class base>
class stack {
public:

	struct node {
		base* head;
		node* tail;
		node() {
			tail = NULL;
			head = NULL;
		};
	};

	void push(base element) {
		node* prev;
		prev = stackTop;
		stackTop = new node();
		stackTop->head = new base();
		*stackTop->head = element;
		stackTop->tail = prev;
	}

	base top() {
		if (stackTop && stackTop->head)
			return *(stackTop->head);
	}

	base pop() {
		base ret = top();
		node* old = stackTop;
		stackTop = stackTop->tail;
		delete old->head;
		delete old;
		return ret;
	}

	bool empty() {
		return !stackTop;
	}

	void destroy() {
		while (stackTop) { pop(); }
	}

private:
	node * stackTop = NULL;
};
