#include <iostream>
#include <vector>
#include <exception>

using namespace std;

template<typename Iter, typename Elem>
Iter Find(Iter first, Iter last, Elem v)
{
	while (first != last && *first != v)
		{ ++first; }
	if (*first == v)
		{ return first; }
	throw exception("not found");
}

template<typename Iter, typename Elem>
int Count(Iter first, Iter last, Elem v)
{
	int cnt{0};
	while (first != last) {
		if (*first == v)
			{ ++cnt; }
		++first;
	}
	if (*first == v)
		{ ++cnt; }
	return cnt;
}

template<typename Iter, typename Elem>
void find_interface(Iter first, Iter last, Elem v)
try {
	auto p = Find(first, last, v);
	cout << "Find() returned iterator to: " << *p << endl;
}
catch (exception& e) {
	cout << "Find() throwed: " << e.what() << endl;
}

int main()
{
	vector<int> v{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	find_interface(v.begin(), --v.end(), 32);
	find_interface(v.begin(), --v.end(), 2);

	cout << "Total 0 in v: " << Count(v.begin(), --v.end(), 0) << '\n';

	return 0;
}