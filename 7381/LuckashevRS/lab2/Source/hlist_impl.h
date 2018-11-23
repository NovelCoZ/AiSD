#pragma once
template <class base>
	bool isatomic(const hlist<base>* ptr) {
		return ptr && ptr->tag;
	}

template <class base>
	bool empty(const hlist<base>* ptr) {
		return !ptr;
	}

template <class base>
	hlist<base>* head(const hlist<base>* ptr) {
		if (!ptr) return NULL;
		if (!isatomic(ptr)) return ptr->node.list.head;
		else return NULL;
	}

template <class base>
	hlist<base>* tail(const hlist<base>* ptr) {
		if (!isatomic(ptr)) return ptr->node.list.tail;
		else return NULL;
	}

template <class base>
	hlist<base>* cons(hlist<base>* head, hlist<base>* tail) {
		hlist<base>* new_node = new hlist<base>;
		if (isatomic(tail) || !new_node) return NULL;
		new_node->tag = false;
		new_node->node.list.head = head;
		new_node->node.list.tail = tail;
		return new_node;
	}

template <class base>
	hlist<base>* make_atom(const base el) {
		hlist<base>* new_atom = new hlist<base>;
		if (!new_atom) return NULL;
		new_atom->tag = true;
		new_atom->node.atom = el;
		return new_atom;
	}

template <class base>
	base get_atom(const hlist<base>* ptr) {
		if (isatomic(ptr)) return ptr->node.atom;
		else {
			std::cerr << "get_atom(!isatomic)";
			std::cin.get();
		}
	}

template <class base>
void destroy(hlist<base>* ptr) {
	if (ptr) {
		if (!isatomic(ptr)) {
			destroy(head(ptr));
			destroy(tail(ptr));
		}
		delete ptr;
	}
}

template <class base>
hlist<base>* copy(const hlist<base>* ptr) {
	if (empty(ptr)) return NULL;
	hlist<base>* res = new hlist<base>;
	if (!res) return NULL;
	if (ptr->tag == true) {
		res = make_atom(get_atom(ptr));
	}
	else {
		res->tag = false;
		res->node.list.head = copy(head(ptr));
		res->node.list.tail = copy(tail(ptr));
	}
	return res;
}
