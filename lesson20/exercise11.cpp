#include <vector>
#include <list>
#include <iostream>
#include <algorithm>

using namespace std;

void f(const list<int>& l)
{
	vector<double> v(l.size());
	auto pv = v.begin();
	auto pl = l.begin();
	while (pl != l.end()) {
		*pv = double(*pl);
		++pv;
		++pl;
	}
	sort(v.begin(), v.end());
	cout << "{ ";
	for (double& d : v) {
		cout << d << (&d == &(*--v.end()) ? " }" : ", ");
	}
}

int main()
{
	list<int> ll{ 99, 100, 15, 0, 67, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	f(ll);

	return 0;
}