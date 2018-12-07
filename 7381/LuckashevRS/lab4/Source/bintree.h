#pragma once
#include <stdlib.h>
#include <cstring>
template <class base> class binary_tree{
private:

public:
	typedef size_t adr;
	const adr max_adr = 1000;
	//bintree == index of node
	typedef adr bintree;	

	struct node {
		base info;
		bintree left;
		bintree right;
	};

	node* mem;

	binary_tree() {
		mem = new node[max_adr + 1];
		for (int i = 0; i <= max_adr; i++) {
			mem[i].left = (i+1) % max_adr;
			mem[i].right = 0;
		}
	}

	bool is_null(bintree t) {
		//index 0 is NULL pointer
		return !t;
	}

	base root(bintree t) {
		if (t > max_adr) return 0;
		return mem[t].info;
	}

	bintree left(bintree t) {
		if (t > max_adr) return 0;
		return mem[t].left;
	}

	bintree right(bintree t) {
		if (t > max_adr) return 0;
		return mem[t].right;
	}

	void insert_children(bintree parent, bintree left, bintree right) {
		if (parent > max_adr || left > max_adr || right > max_adr) return;
		mem[parent].left = left;
		mem[parent].right = right;
	}

	bintree create_node(base e) {
		if (mem[1].left == 0) return 0;
		node p;
		p.info = e;
		p.right = 0;
		p.left = 0;
		bintree freemem = mem[mem[1].left].left;
		mem[mem[1].left] = p;
		bintree res = mem[1].left;
		mem[1].left = freemem;
		return res;
	}

};

//char btree functions and type defenitions
typedef char base;
typedef binary_tree<base> btree;
typedef btree::bintree bintree;
typedef binary_tree<base>::node node;
bintree read_btree(base* str, btree tree);
int get_index();
void error_handler();