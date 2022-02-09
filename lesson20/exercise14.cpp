#include <iostream>
#include <exception>
#include <string>

using namespace std;

template<typename Elem>
struct Link {
	Link* succ{ nullptr };
	Elem val;

	Link() :val{ NULL } { }
	Link(const Elem& v) :val{ v } { }
	Link(Link* s, const Elem& v)
		:val{ v }, succ{ s } { }
};

template<typename Elem>
class SList {
	Link<Elem>* first;
public:
	SList() :first(nullptr) { }

	class iterator;

	iterator begin()const { return iterator(first); }
	iterator end()	const { return iterator(nullptr); }

	iterator insert(iterator p, const Elem& v);
	iterator erase(iterator p);

	void push_back(const Elem& v)	{ insert(end(), v); }
	void push_front(const Elem& v)	{ insert(begin(), v); }
	void pop_back()	{ erase(end()); }
	void pop_front(){ erase(begin()); }

	Elem& front() { return *begin(); }
	Elem& back()
	{
		iterator ret(first);
		while (ret.current()->succ)
			{ ++ret; }
		return *ret;
	}

	Elem& front()	const { return *begin(); }
	Elem& back()	const
	{
		iterator ret(first);
		while (ret.current()->succ)
			{ ++ret; }
		return *ret;
	}
};

template<typename Elem>
class SList<Elem>::iterator {
	Link<Elem>* curr;
public:
	iterator(Link<Elem>* c) :curr{ c } { }

	Link<Elem>* current()	{ return curr; }

	iterator& operator++()	{ curr = curr->succ; return *this; }

	Elem& operator*()	{ return curr->val; }

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
void list_check(const SList<Elem>& l, const string& desc)
{
	cout << desc << ": { ";
	if (l.begin() == l.end())
		{ cout << "}\n"; return; }
	for (const Elem& p : l)
		{ cout << p << (&p == &l.back() ? " }\n" : ", "); }
}

//----------------------------------------------------------------------

template<typename Elem>
typename SList<Elem>::iterator SList<Elem>::insert(SList<Elem>::iterator p, const Elem& v)
{
	if (p == begin()) {
		first = new Link<Elem>(p.current(), v);
		return iterator(first);
	}

	iterator in(first);
	while (in.current()->succ != p.current())
		{ ++in; }
	in.current()->succ = new Link<Elem>(p.current(), v);
	return iterator(in.current()->succ);
}

template<typename Elem>
typename SList<Elem>::iterator SList<Elem>::erase(SList<Elem>::iterator p)
{
	if (p == begin()) {
		first = p.current()->succ;
		delete p.current();
		return iterator(first);
	}

	iterator in(first);
	while ((p.current()?in.current()->succ:in.current()->succ->succ) != p.current())
		{ ++in; }
	in.current()->succ = p.current() ? p.current()->succ : p.current();
	delete p.current();
	return iterator(in.current()->succ);
}

//----------------------------------------------------------------------

int main()
{
	SList<int> sl;
	for (int i{0}; i < 5; ++i)
		{ sl.push_back(i); }
	list_check(sl, "After push_back");
	for (int i{5}; i < 10; ++i)
		{ sl.push_front(i); }
	list_check(sl, "After push_front");
	sl.pop_back();
	list_check(sl, "After pop_back");
	sl.pop_front();
	list_check(sl, "After pop_front");
	sl.insert(sl.end(), 99);
	list_check(sl, "After insert(end)");
	cout << "SList back() = " << sl.back() << '\n';
	sl.insert(sl.begin(), -99);
	list_check(sl, "After insert(begin)");
	cout << "SList front() = " << sl.front() << '\n';
	sl.erase(sl.end());
	list_check(sl, "After erase(end)");
	sl.erase(sl.begin());
	list_check(sl, "After erase(begin)");
	auto p = sl.begin();
	for (int i{0}; i < 4; ++i)
		{ ++p; }
	sl.insert(p, 777);
	list_check(sl, "After insert(p)");
	sl.erase(p);
	list_check(sl, "After erase(p)");

	return 0;
}