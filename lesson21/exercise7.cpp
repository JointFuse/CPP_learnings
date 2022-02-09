#include <vector>
#include <list>
#include <iostream>

using namespace std;

vector<int>::iterator Binary_search(vector<int>& dat, int v)
{
	if (dat.size() == 0) { return dat.end(); }
	auto a = dat.begin();
	auto b = --dat.end();
	if (v < *a || *b < v)
		{ return dat.end(); }
	while (true) {
		auto m = a + (b - a) / 2;
		if (*m == v) { return m;}
		else if (*m < v) { a = m; }
		else { b = m; }
		if (b - a == 1) { 
			if (*b == v) 
				{ return b; }
			else if (*a == v)
				{ return a; }
			return dat.end();
		}
	}
}

list<string>::iterator Binary_search(list<string>& dat, string s)
{
	if (dat.size() == 0) { return dat.end(); }
	auto a = dat.begin();
	auto b = --dat.end();
	auto l = dat.size();
	if (s < *a || *b < s)
		{ return dat.end(); }
	while (true) {
		auto m = a;
		l /= 2;
		for (int i{0}; i < l; ++i)
			{ ++m; }
		if (*m == s) {  return m; }
		else if (*m < s) { a = m; }
		else { b = m; }
		if (l == 0) {
			if (*b == s)
				{ return b; }
			else if (*a == s)
				{ return a; }
			return dat.end();
		}
	}
}

void check_vec(vector<int>& vec, int v, string desc)
{
	cout << "Has [" << desc << "] value: " << v << "? { ";
	auto p = Binary_search(vec, v);
	if (p != vec.end())
		{ cout << "YES: " << *p; }
	else
		{ cout << "NO"; }
	cout << " }\n";
}

void check_lis(list<string>& lis, string s, string desc)
{
	cout << "Has [" << desc << "] value: " << s << "? { ";
	auto p = Binary_search(lis, s);
	if (p != lis.end())
		{ cout << "YES: " << *p; }
	else
		{ cout << "NO"; }
	cout << " }\n";
}

int main()
{
	vector<int> even{ 0, 3, 4, 5, 7, 8, 9, 11, 12, 13 };
	vector<int> odd{ 0, 1, 2, 3, 4, 5, 6, 8 };
	for (int i{0}; i < 14; ++i) {
		check_vec(even, i, "even vector");
		check_vec(odd, i, "odd vector");
	}

	list<string> l_even{ "a", "b", "q", "w" };
	list<string> l_odd{ "a", "b", "c", "q", "qk", "w", "wr" };
	list<string> l_orig{ "c", "b", "asd", "eqw", "dad", "cgf", "a", "qk", "w" };
	for (string orig : l_orig) {
		check_lis(l_even, orig, "even list");
		check_lis(l_odd, orig, "odd list");
	}
	

	return 0;
}