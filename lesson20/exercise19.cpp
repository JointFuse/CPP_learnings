#include <iostream>
#include <exception>
#include <string>

using namespace std;

template<typename Elem>
struct Link {
	Link* prev{ nullptr };
	Link* succ{ nullptr };
	Elem val;

	Link() :val{ NULL } { }
	Link(const Elem& v) :val{ v } { }
	Link(Link* p, Link* s, const Elem& v)
		:val{ v }, prev{ p }, succ{ s } { }
};

template<typename Elem>
class List {
	Link<Elem>* first;
public:
	using size_type = unsigned long;

	List() :first(nullptr) { }

	class iterator;

	iterator begin()const { return iterator(first); }
	iterator end()	const { return iterator(nullptr); }

	iterator insert(iterator p, const Elem& v);
	iterator erase(iterator p);

	void push_back(const Elem& v) { insert(end(), v); }
	void push_front(const Elem& v) { insert(begin(), v); }
	void pop_back() { erase(end()); }
	void pop_front() { erase(begin()); }

	Elem& front() { return *begin(); }
	Elem& back()
	{
		iterator ret(first);
		while (ret.current()->succ)
		{
			++ret;
		}
		return *ret;
	}

	Elem& front() const { return *begin(); }
	Elem& back() const
	{
		iterator ret(first);
		while (ret.current()->succ)
		{
			++ret;
		}
		return *ret;
	}
};

template<typename Elem>
class List<Elem>::iterator {
	Link<Elem>* curr;
public:
	iterator(Link<Elem>* c) :curr{ c } { }

	Link<Elem>* current() { return curr; }

	iterator& operator++() { if (curr == nullptr) { throw exception("iter range err"); } curr = curr->succ; return *this; }
	iterator& operator--() { if (curr == nullptr) { throw exception("iter range err"); } curr = curr->prev; return *this; }
	iterator& operator+=(size_type);
	iterator& operator-=(size_type);
	iterator operator+(size_type);
	iterator operator-(size_type);

	Elem& operator*() { return curr->val; }

	bool operator==(const iterator& b) const
		{ return curr == b.curr; }
	bool operator!=(const iterator& b) const
		{ return curr != b.curr; }
};

//----------------------------------------------------------------------

template<typename Iter>	// requires Input_iterator<Iter> ()
Iter high(Iter first, Iter last)
{
	Iter high = first;
	for (Iter p = first; p != last; ++p)
		if (*high < *p) high = p;
	return high;
}

//----------------------------------------------------------------------

template<typename Elem>	// requires Output_iterator<Iter> ()
void list_check(const List<Elem>& l, const string& desc)
{
	cout << desc << ": { ";
	if (l.begin() == l.end())
	{
		cout << "}\n"; return;
	}
	for (const Elem& p : l)
	{
		cout << p << (&p == &l.back() ? " }\n" : ", ");
	}
}

//----------------------------------------------------------------------

template<typename Elem>
typename List<Elem>::iterator List<Elem>::insert(List<Elem>::iterator p, const Elem& v)
{
	if (first == nullptr) {
		first = new Link<Elem>(v);
		return iterator(first);
	}

	if (p == end()) {
		p = iterator(first);
		while (p.current()->succ)
		{
			++p;
		}
		p.current()->succ = new Link<Elem>(p.current(), nullptr, v);
		return iterator(p.current()->succ);
	}

	Link<Elem>* newval = new Link<Elem>(p.current()->prev,
		p.current(), v);
	if (p == begin())
	{
		first = newval;
	}
	else
	{
		p.current()->prev->succ = newval;
	}
	p.current()->prev = newval;
	return iterator(newval);
}

template<typename Elem>
typename List<Elem>::iterator List<Elem>::erase(List<Elem>::iterator p)
{
	if (p == end()) {
		p = iterator(first);
		while (p.current()->succ)
		{
			++p;
		}
	}
	if (p == begin())
	{
		first = p.current()->succ;
	}
	else
	{
		p.current()->prev->succ = p.current()->succ;
	}
	if (p.current()->succ)
	{
		p.current()->succ->prev = p.current()->prev;
	}
	iterator ret(p.current()->prev);
	delete p.current();
	return ret;
}

template<typename Elem>
typename List<Elem>::iterator& List<Elem>::iterator::operator+=(size_type n)
{
	for (size_type i{ 0 }; i < n; ++i) {
		if (curr->succ == nullptr)
			{ return *this; }
		curr = curr->succ;
	}
	return *this;
}

template<typename Elem>
typename List<Elem>::iterator& List<Elem>::iterator::operator-=(size_type n)
{
	for (size_type i{ 0 }; i < n; ++i) {
		if (curr->prev == nullptr)
			{ return *this; }
		curr = curr->prev;
	}
	return *this;
}

template<typename Elem>
typename List<Elem>::iterator List<Elem>::iterator::operator+(size_type n)
{
	Link<Elem>* ret = curr;
	for (size_type i{ 0 }; i < n; ++i) {
		if (ret->succ == nullptr)
			{ return *this; }
		ret = curr->succ;
	}
	return ret;
}

template<typename Elem>
typename List<Elem>::iterator List<Elem>::iterator::operator-(size_type n)
{
	Link<Elem>* ret = curr;
	for (size_type i{ 0 }; i < n; ++i) {
		if (ret->prev == nullptr)
			{ return *this; }
		ret = curr->prev;
	}
	return ret;
}

//----------------------------------------------------------------------

int main()
{
	List<int> l;
	list_check(l, "empty");
	l.push_back(10);
	list_check(l, "after push_back");
	l.push_front(1);
	list_check(l, "after push_front");
	cout << "Front: " << l.front()
		<< "; Back: " << l.back() << ";\n";
	l.insert(l.end(), 9);
	list_check(l, "after insert");
	cout << "Highest: " << *high(l.begin(), l.end()) << '\n';
	l.erase(l.end());
	list_check(l, "after erase");
	l.pop_back();
	list_check(l, "after pop_back");
	l.pop_front();
	list_check(l, "after pop_front");

	return 0;
}