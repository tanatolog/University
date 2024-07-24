#pragma once

#include <windows.h>

struct console {
	HANDLE hout;
	HANDLE hin;
	short  width;
	short  height;
};

struct node {
	node* next;
	console val;
};

class list {
private:
	node* head, * tail;
	size_t cnt;
public:
	list(void);
	~list(); 
	void add(console val);
	void clear(void);
	node* begin(void);
	size_t size(void);
	bool empty(void);
	console& front(void);
};

class usefullist : public list {
private:
	node* p, * prev;
	node* head, * tail;
	size_t cnt;
public:
	usefullist(void);
	usefullist(node* setp);
	usefullist(node* setp, node* setprev);
	bool operator != (node* setp);
	usefullist& operator ++ (void);
	console* operator -> (void);
	void erase(usefullist pos);
	usefullist InsertfromIndex(size_t index);
};