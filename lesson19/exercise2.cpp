#include <iostream>
#include <vector>

using namespace std;

template<typename T, typename U>		// requires Number<T, U> ()
T f(const vector<T>& vt, const vector<U>& vu)
{
	T ret{ 0 };
	for (int i{0}; i < vt.size() && i < vu.size(); ++i)
		{ ret += vt.at(i) * T(vu.at(i)); }
	return ret;
}

int main()
{
	vector<int> vi{ 1, 2, 3, 4, 5, 6 };
	vector<double> vd{ 1.2, 2.5, 3.8, 4.1, 9.5, 5.6 };
	vector<string> vs{ "ds", "dfsf", "ser", "sdfe", "qwer" };
	vector<char> vc{ 's', 'd', 'a', 'r', 'q' };
	auto sum = f(vd, vc);
	cout << "Sum of vectors increase: " << sum;
	return 0;
}