#include <iostream>
#include <list>
#include <vector>
#include <functional>

using namespace std;

template<typename Iter, typename T>
int Count(Iter begin, Iter end, T v)
{
	int cnt{0};
	while (begin != end) {
		if (*begin == v) { ++cnt; }
		++begin;
	}
	return cnt;
}

/* Exercise 4 */
template<typename Iter, typename T, typename Pred>
int Count_if(Iter begin, Iter end, T v, Pred p)
{
	int cnt{0};
	while (begin != end) {
		if (p(*begin, v)) { ++cnt; }
		++begin;
	}
	return cnt;
}

int main()
{
	int m[]{ 0, 1, 2, 3, 4, 0, 5, 6, 0, 7, 8, 9, };
	list<double> l{ 1.152, 2.64, 0.641, 1.0644, 6.456, 7.054, 1.99, 23.016 };
	vector<string> v{ "one", "two", "three", "four", "five", "two" ,"six", "seven", "two" };
	cout << "Total 0 in m[]: " 
		 << Count(&m[0], &m[11], 0) 
		 << '\n'
		 << "Total x < 5 in m[]: " 
		 << Count_if(&m[0], &m[11], 5, 
					 [](int x, int y) 
					 { return x < y; }) 
		 << '\n'
		 << "Total 1.0644 in l: " 
		 << Count(l.begin(), l.end(), 1.0644)
		 << '\n'
		 << "Total x < 3 in l: " 
		 << Count_if(l.begin(), l.end(), 3,
					 [](double x, double y)
					 { return x < y; })
		 << '\n'
		 <<  "Total <two> in v: "
		 << Count(v.begin(), v.end(), "two")
		 << '\n'
		 << "Total s < <wednsday> in v: "
		 << Count_if(v.begin(), v.end(), 
					 "wednsday", less<string>())
		 << '\n';

	return 0;
}