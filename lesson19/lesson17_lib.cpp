#include "lesson17_lib.h"
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

bool My_link::operator== (const God& g1, const God& g2)
{
	return g1.name == g2.name;
}

//----------------------------------------------------------------