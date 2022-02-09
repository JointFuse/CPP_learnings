#include "lesson17_lib.h"
#include <iostream>
#include <cmath>

using namespace My_link;

//----------------------------------------------------------------

void My_pointers::to_lower(char* s)
{
	while (*s != '0') {
		if (64 < int(*s) && int(*s) < 91)
			*s = char(int(*s) + 32);
		++s;
	}
}

//----------------------------------------------------------------

char* My_pointers::strdup(const char* s)
{
	int size{0};
	const char* ptr = s;
	while(*ptr != '0') { ++size; ++ptr; }
	char* copy = new char[size + 1];
	ptr = s;
	for (int i{ 0 }; i < size; ++i) {
		copy[i] = *ptr;
		++ptr;
	}
	copy[size] = '0';

	return copy;
}

//----------------------------------------------------------------

char* My_pointers::findx(const char* s, const char* x)
{
	const char* sptr = s;
	const char* xptr = x;

	while (*s != '0') {
		sptr = s;
		xptr = x;
		while (*sptr == *xptr) {
			if(*(xptr + 1) == '0')
				return const_cast<char*>(s);
			++sptr;
			++xptr;
		}
		++s;
	}

	return nullptr;
}

//----------------------------------------------------------------

Link* My_link::Link::insert(Link* n)
{
	if (!n) return this;
	if(!this) return n;

	n->succ = this;
	if(prev) prev->succ = n;
	n->prev = prev;
	prev = n;

	return n;
}

Link* My_link::Link::add(Link* n)
{
	if(!n) return this;
	if(!this) return n;

	n->prev = this;
	if(succ) succ->prev = n;
	n->succ = succ;
	succ = n;

	return n;
}

Link* My_link::Link::erase()
{
	if (!this && succ) return succ;
	if (!this && prev) return prev;
	if (!this) return nullptr;

	Link* ret = nullptr;

	if (succ) {
		ret = succ;
		if (prev)	succ->prev = prev;
		else		succ->prev = nullptr;
		succ = nullptr;
	}
	if (prev) {
		ret = prev;
		if (succ)	prev->succ = succ;
		else		prev->succ = nullptr;
		prev = nullptr;
	}
	
	return ret;
}

Link* My_link::Link::find_name(const std::string& s)
{
	if (!this) return nullptr;

	Link* l = this;
	while(l->prev) l = l->prev;

	while (l) {
		if(l->value.name == s)
			return l;
		l = l->succ;
	}

	return nullptr;
}

const Link* My_link::Link::find_name(const std::string& s) const
{
	if (!this) return nullptr;

	const Link* l = this;
	while (l->prev) l = l->prev;

	while (l) {
		if (l->value.name == s)
			return l;
		l = l->succ;
	}

	return nullptr;
}

Link* My_link::Link::advance(int n)
{
	if (!this)	return nullptr;

	Link* dest = this;
	int nn{ 0 };
	while (nn != n) {
		if (n > 0 && (dest->succ == nullptr)) 
			break;
		if (n < 0 && (dest->prev == nullptr))
			break;
		if (n < 0)	dest = dest->prev;
		else		dest = dest->succ;
		nn += n / abs(n);
	}
	if (!nn)		return this;

	Link* ret = this;
	if (succ) {
		ret = succ;
		if (prev)	succ->prev = prev;
		else		succ->prev = nullptr;
	}
	if (prev) {
		ret = prev;
		if (succ)	prev->succ = succ;
		else		prev->succ = nullptr;
	}

	if (nn > 0) {
		if (dest->succ) {
			succ = dest->succ;
			succ->prev = this;
		}
		else succ = nullptr;

		prev = dest;
		prev->succ = this;
	}
	else {
		if (dest->prev) {
			prev = dest->prev;
			prev->succ = this;
		}
		else prev = nullptr;

		succ = dest;
		succ->prev = this;
	}

	return ret;
}

Link* Link::add_ordered(Link* n)
{
	if (!n) return this;
	if (!this) return n;

	Link* ptr = this;
	while(ptr->prev) ptr = ptr->prev;
	Link* begin = ptr;

	bool in_end(false);
	while (ptr->value.name < n->value.name) {
		if (ptr->succ)	ptr = ptr->succ;
		else			{ in_end = true; break; }
	}

	if (in_end) {
		n->prev = ptr;
		ptr->succ = n;
		return begin;
	}
	else {
		n->succ = ptr;
		if(ptr->prev) {
			n->prev = ptr->prev;
			n->prev->succ = n;
		}
		ptr->prev = n;
		if (ptr == begin)
			return n;
	}

	return begin;
}

//----------------------------------------------------------------

std::ostream& My_link::operator<< (std::ostream& os, const God& g)
{
	return os << "{ " << g.name << ", " << g.from << (g.transport == "" ? "" : ", ")
			  << g.transport << ", " << g.weapon << " }";
}

//----------------------------------------------------------------

std::ostream& My_link::operator<< (std::ostream& os, const Mithology& m)
{
	switch (m) {
		case Mithology::greece:
			return os << "Greece";
		case Mithology::india:
			return os << "India";
		case Mithology::norway:
			return os << "Norway";
		case Mithology::slavic:
			return os << "Slavic";
		default:
			return os << "Nowhere";
	}
}

//----------------------------------------------------------------

void My_link::print_all(Link* p)
{
	while (p->previous())
		p = p->previous();

	std::cout << "{ " << '\n';
	while (p) {
		std::cout << '\t' << p->value << '\n';
		p=p->next();
	}
	std::cout << "}" << '\n';
}

//----------------------------------------------------------------
