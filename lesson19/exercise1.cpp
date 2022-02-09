#include <vector>
#include <iostream>

using namespace std;

template<typename Num>		// requires Number<Num> ()
void f(vector<Num>& v1, const vector<Num>& v2)
{
	vector<Num> buf = v1;
	for (int i{0}; i < buf.size() && i < v2.size(); ++i)
		{ buf.at(i) += v2.at(i); }
	swap(buf, v1);
}

template<typename T>		// requires Output_iterator<T> ()
void printvec(const vector<T>& v, string name = "vector")
{
	cout << name << ':';
	for (const T& i : v)
		{ cout << ' ' << i; }
	cout << '\n';
}

int main()
{
	vector<int> iv1{ 1, 2, 3, 4, 5, 6 };
	vector<int> iv2{ -1, -2, -3, -4, -5 };
	printvec(iv1, "Vec 1");
	printvec(iv2, "Vec 2");
	f(iv1, iv2);
	printvec(iv1, "Vec 1 + Vec 2");

	return 0;
}