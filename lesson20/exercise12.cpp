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
	Link<Elem>* last;
public:
	List() :first(new Link<Elem>()), last(first) { }

	class iterator;

	iterator begin()const { return iterator(first); }
	iterator end()	const {	return iterator(last); }
	
	iterator insert(iterator p, const Elem& v)
	{
		Link<Elem>* newval = new Link<Elem>(p.current()->prev, 
											p.current(), v);
		if (p == begin())
			{ first = newval; }
		else
			{ p.current()->prev->succ = newval; }
		p.current()->prev = newval;
		return iterator(newval);
	}

	iterator erase(iterator p)
	{
		if (p == end())
			{ return p; }
		if (p == begin())
			{ first = p.current()->succ; }
		else
			{ p.current()->prev->succ = p.current()->succ; }
		p.current()->succ->prev = p.current()->prev;
		iterator ret(p.current()->prev);
		delete p.current();
		return ret;
	}

	void push_back(const Elem& v)	{ insert(end(), v); }
	void push_front(const Elem& v)	{ insert(begin(), v); }
	void pop_back()					{ erase(--end()); }
	void pop_front()				{ erase(begin()); }

	Elem& front()	{ return *begin(); }
	Elem& back()	{ return *(--end()); }
	
	Elem& front() const { return *begin(); }
	Elem& back() const	{ return *(--end()); }
};

template<typename Elem>
class List<Elem>::iterator {
	Link<Elem>* curr;
public:
	iterator(Link<Elem>* c) :curr{ c } { }

	Link<Elem>* current()	{ return curr; }

	iterator& operator++()	{ curr = curr->succ; return *this; }
	iterator& operator--()	{ curr = curr->prev; return *this; }

	Elem& operator*()		{ return curr->val; }

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
		{ cout << "}\n"; return; }
	for (const Elem& p : l)
		{ cout << p << (&p == &l.back() ? " }\n" : ", "); }
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
	l.erase(--l.end());
	list_check(l, "after erase");
	l.pop_back();
	list_check(l, "after pop_back");
	l.pop_front();
	list_check(l, "after pop_front");

	return 0;
}