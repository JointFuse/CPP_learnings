#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <sstream>

using namespace std;

template<typename Iter>
int getpos(Iter f1, Iter e, Iter s)
{
	if (s == e) { return -1; }

	int pos{0};
	while (f1 != s) {
		++f1;
		++pos;

	}
	return pos;
}

void copy(int* f1, int* e1, int* f2)
{
	for (int* p = f1; p != e1; ++p) {
		*p = *f2;
		++f2;
	}
}

template<typename Iter1, typename Iter2>
Iter2 Copy(Iter1 f1, Iter1 e, Iter2 f2)
{
	while (f1 != e) {
		*f2 = *f1;
		++f1;
		++f2;
	}
	return f2;
}

template<typename T, typename Iter>
void f(T& obj, Iter b, Iter e, string descript)
{
	cout << descript << ":\n";
	int size{0};
	for (Iter p = b; p != e; ++p)
		{ ++size; }
	cout << "String length = " << size << '\n';
	string orig{"Hello"};
	string comp{"Howdy"};
	cout << "Word is" << (equal(b, e, &orig[0], &orig[0] + orig.size()) ? "" : "'nt") << " Hello\n"
		 << "Word is " << (lexicographical_compare(b, e, &comp[0], &comp[0] + comp.size())?"lower":"higher") 
		 << " then Howdy\n";
	if (b == e) { return; }
	//T copied = obj;
	//cout << "Copied = " << copied << '\n';
}

template<typename Iter> // requires Iterator<Iter>
void advance(Iter& p, int n)
{
	if (n < 0) {
		while (n < 0) { --p; ++n; }
		return;
	}
	while (0 < n) { ++p; --n; }
}

int main()
{
	char m[] = "Hello";
	vector<char> v{ 'H', 'e', 'l', 'l', 'o' };
	list<char> l{ 'H', 'e', 'l', 'l', 'o' };
	string s{ "Hello" };
	f(m, &m[0], &m[0] + 5, "Massive");
	f(v, v.begin(), v.end(), "Vector");
	f(l, l.begin(), l.end(), "List");
	f(s, s.begin(), s.end(), "String");

	int nm[] = {1,2,3,4,5};
	vector<int> nv{ 1,2,3,4,5 };
	list<int> nl{ 1,2,3,4,5 };
	f(nm, &nm[0], &nm[0] + 5, "Numeric massive");
	f(nv, nv.begin(), nv.end(), "Numeric vector");
	f(nl, nl.begin(), nl.end(), "Numeric list");

	int t1m1[] = {0,1,2,3,4,5,6,7,8,9};
	vector<int> t1v1{0,1,2,3,4,5,6,7,8,9};
	list<int> t1l1{ 0,1,2,3,4,5,6,7,8,9 };
	int t1m2[]{ t1m1[0], t1m1[1], t1m1[2], t1m1[3], t1m1[4], t1m1[5], t1m1[6], t1m1[7], t1m1[8], t1m1[9], };
	vector<int> t1v2{t1v1};
	list<int> t1l2{t1l1};
	for (int i{0}; i < 10; ++i)
		{ t1m1[i] += 2; }
	for (int& v : t1v1)
		{ v += 3; }
	for (int& l : t1l1)
		{ l += 5; }
	Copy(&t1m1[0], &t1m1[0] + 10, t1v1.begin());
	Copy(t1l1.begin(), t1l1.end(), &t1m1[0]);
	int vpos = getpos(t1v1.begin(), t1v1.end(), find(t1v1.begin(), t1v1.end(), 3));
	ostringstream svpos;
	svpos << vpos;
	cout << "Number 3 " << (vpos == -1 ? "not include" : "position = " + svpos.str()) << " in t1v1\n";
	int lpos = getpos(t1l1.begin(), t1l1.end(), find(t1l1.begin(), t1l1.end(), 27));
	ostringstream slpos;
	slpos << lpos;
	cout << "Number 27 " << (lpos == -1 ? "not include" : "position = " + slpos.str()) << " in t1l1\n";

	return 0;
}