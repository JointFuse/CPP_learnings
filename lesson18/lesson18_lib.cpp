#include "lesson18_lib.h"
#include <exception>
#include <random>

using namespace Lib18;

//-----------------------------------------------------------

inline std::default_random_engine& get_rand()
{
	static std::default_random_engine ran;	// note: not thread_local
	return ran;
};

inline void seed_randint(int s) { get_rand().seed(s); }

inline int randint(int min, int max) { return std::uniform_int_distribution<>{min, max}(get_rand()); }

inline int randint(int max) { return randint(0, max); }


//-----------------------------------------------------------

int chlen(const char* ptr) 
{ 
	if (!ptr) { return 0; }
	int count{ 0 };
	while (*ptr) { ++ptr; ++count; }
	return count;
}

//-----------------------------------------------------------

char* Lib18::strdup(const char* to_copy)
{
	const char* ptr = to_copy;
	int count{ 1 };
	while(*ptr) { ++ptr; ++count; }

	char* ret = new char[count];
	char* ptr2 = ret;
	ptr = to_copy;
	while (*ptr) {
		*ptr2 = *ptr;
		++ptr2; ++ptr;
	}
	*ptr2 = 0;

	return ret;
}

//-----------------------------------------------------------

char* Lib18::findx(const char* where, const char* what)
{
	const char* ptr = where;
	const char* ptr2 = what;

	while (*where) {
		ptr = where;
		ptr2 = what;
		while (*ptr == *ptr2) {
			++ptr; ++ptr2;
			if (!*ptr2)
				return const_cast<char*>(where);
		}
		++where;
	}

	return nullptr;
}

//-----------------------------------------------------------

int Lib18::strcmp(const char* s1, const char* s2)
{
	while (*s1 == *s2) {
		if(*s1 == 0) { return 0; }
		++s1; ++s2;
	}
	
	if (*s1 < *s2)
		return -1;
	else
		return 1;
}

//-----------------------------------------------------------

std::string Lib18::cat_dot(const std::string& s1, const std::string& s2, const std::string& s3)
{
	return std::string{ s1 + s3 + s2 };
}

//-----------------------------------------------------------

char* Lib18::cat_dotc(const char* s1, const char* s2, const char* dot)
{
	bool is_dot{ false };
	if (!dot) { 
		is_dot = true; 
		dot = new char[2];
		*const_cast<char*>(dot) = '.';
		*const_cast<char*>(dot + 1) = 0;
	}

	int count = 1 + chlen(s1) + chlen(s2) + chlen(dot);
	char* ret = new char[count];
	ret[count - 1] = 0;

	const char* ptr = s1;
	char* ptr2 = ret;
	while (*ptr) {
		*ptr2 = *ptr;
		++ptr2; ++ptr;
	}
	ptr = dot;
	while (*ptr) {
		*ptr2 = *ptr;
		++ptr2; ++ptr;
	}
	ptr = s2;
	while (*ptr) {
		*ptr2 = *ptr;
		++ptr2; ++ptr;
	}

	if (is_dot) { delete[] const_cast<char*>(dot); }
	return ret;
}

//-----------------------------------------------------------

bool Lib18::is_palindrome(const std::string& s)
{
	int first{0};
	int last{int(s.length()) - 1};
	while (first < last) {
		if (s[first] != s[last]) return false;
		++first; --last;
	}
	return true;
}

//-----------------------------------------------------------

bool Lib18::is_palindrome(const char s[], int n)
{
	if (n < 0) 
		throw std::exception("wrong massive size");

	int first{0};
	int last{n - 1};
	while (first < last) {
		if (s[first] != s[last]) return false;
		++first; --last;
	}
	return true;
}

//-----------------------------------------------------------

bool Lib18::is_palindrome(const char* first, const char* last)
{
	if (first < last) {
		if (*first != *last) return false;
		return is_palindrome(first + 1, last - 1);
	}
	return true;
}

//-----------------------------------------------------------

std::string Lib18::reverse(const std::string& s)
{
	std::string rev;
	const char* first = &s[0];
	const char* last = &s[s.size() - 1];
	while (first <= last) {
		rev.push_back(*last);
		--last;
	}
	return rev;
}

//-----------------------------------------------------------

// Для избежания повторной очистки уже очищенной памяти,
// деструкторы ячеек данных вызываются только горизонтально
Skip_list::data::~data()
{
	if(next) { delete next; next = nullptr; }
}

// Вызов деструктора первого элемента горизонтального списка
// вызывает рекурсивный вызов деструкторов всей линии уровня
Skip_list::~Skip_list()
{
	for (int i{int(levels.size()) - 1}; 0 <= i; --i)// Очистка происходит сверху-вниз из-за появления указателей
		{ delete levels[i]; }						// на освобожденную память при очистке снизу-вверх
}

void Skip_list::vcheck(const std::string& s)
{
	if (s == "") throw std::exception("skip list: empty value");
}

Skip_list::data* Skip_list::insert(data*& ptr, const std::string& s, data* d)
{
	if (!ptr) { ptr = new data(nullptr, d, s); return ptr; }

	data* n = ptr;
	ptr = new data(n, d, s);
	return ptr;
}

void Skip_list::add(const std::string& s)
{
	vcheck(s);
	bool first{false};
	data* down{nullptr};

	for (data*& p : levels) {
		data** pp = &p;
		if (first && randint(1)){ return; }
		if (!first)				{ first = true; }

		while(*pp && (*pp)->value < s)
			{ pp = &(*pp)->next; }
		
		if (*pp && (*pp)->value == s)
			{ return; }
		down = insert(*pp, s, down);
	}
}

void Skip_list::del(const std::string& s)
{
	vcheck(s);
	bool is_not{true};

	for (data*& p : levels) {
		data** pp = &p;

		while (*pp && (*pp)->value != s) 
			{ pp = &(*pp)->next; }
		
		if (*pp) {
			data* to_del = *pp;
			*pp = (*pp)->next;
			to_del->next = nullptr;
			delete to_del;
			is_not = false;
		}

		if (is_not) { return; }
	}
}

bool Skip_list::search(const std::string& s)
{
	vcheck(s);
	data* pp{nullptr};
	int l{int(levels.size())};

	while (0 < l) {
		pp = levels[--l];
		if ((pp && pp->value > s) || !pp)
			{ continue; }

		while (pp) {
			while (pp->value < s) {
				if (pp->next && pp->next->value > s)
					{ break; }
				if (pp->next) 
					{ pp = pp->next; }
				else
					{ break; }
			}
			if (pp->value == s)
				{ return true; }
			pp = pp->down;
		}
		return false;
	}
	return false;
}

//-----------------------------------------------------------
