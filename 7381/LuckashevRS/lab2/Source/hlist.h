#pragma once
#include <fstream>
#include <iostream>

namespace h_list {

template <class el>
	struct two_ptr {
		el* head;
		el* tail;
	};

template <class base>
	struct hlist {
		bool tag;
		union {
			base atom;
			two_ptr<hlist> list;
		} node;
	};
	
template <class base>
	bool isatomic(const hlist<base>* ptr);

template <class base>
	bool empty(const hlist<base>* ptr);

template <class base>
	hlist<base>* head(const hlist<base>* ptr);

template <class base>
	hlist<base>* tail(const hlist<base>* ptr);

template <class base>
	hlist<base>* cons(const hlist<base>* head, const hlist<base>* tail);

template <class base>
	hlist<base>* make_atom(const base el);

template <class base>
	base get_atom(const hlist<base>* ptr);

template <class base>
	void destroy(hlist<base>* ptr);
	
template <class base>
	hlist<base>* copy(const hlist<base>* ptr);

#include "hlist_impl.h"

}