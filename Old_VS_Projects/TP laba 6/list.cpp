#include "list.h"

list::list(void) {
	head = NULL;
	tail = NULL;
	cnt = 0;
}

list::~list() { clear(); }

void list::add(console val) {
	node* p = new node;
	p->next = NULL;
	p->val = val;
	if (head == NULL) { 
		head = tail;
		head = p; }
	else {
		tail->next = p;
		tail = p;
	}
	++cnt;
}

void list::clear(void) {
	node* t;
	while (head != NULL) {
		t = head;
		head = head->next;
		delete t;
	}
	tail = NULL;
	cnt = 0;
}

node* list::begin(void) {
	return head;
}

size_t list::size(void) {
	return cnt;
}

bool list::empty(void) {
	return (head == NULL);
}

console& list::front(void) { return head->val; }

usefullist::usefullist(void) {
	p = NULL;
	prev = NULL;
}

usefullist::usefullist(node* setp) {
	p = setp;
	prev = NULL;
}

usefullist::usefullist(node* setp, node* setprev) {
	p = setp;
	prev = setprev;
}

bool usefullist::operator != (node* setp) {
	return (p != setp);
}

usefullist& usefullist::operator ++ (void) {
	prev = p;
	p = p->next;
	return *this;
}

console* usefullist::operator -> (void) {
	return &p->val;
}

void usefullist::erase(usefullist pos) {
	if (pos.p == NULL)
		return;
	else if (pos.p == head) {
		head = head->next;
		if (head == NULL)
			tail = NULL;
	}
	else {
		pos.prev->next = pos.p->next;
		if (pos.p == tail) {
			tail = pos.prev;
			tail->next = NULL;
		}
	}
	delete pos.p;
	--cnt;
}

usefullist usefullist::InsertfromIndex(size_t index) {
	node *prev = NULL, *p = head;
	for (size_t i = 0; (i < index) && (p != NULL); ++i) {
		prev = p;
		p = p->next;
	}
	return usefullist(p, prev);
}
