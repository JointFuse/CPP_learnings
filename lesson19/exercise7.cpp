#include "Lesson19.h"
#include <vector>

using namespace MyLib;

template<typename T, typename U>		// requires Number<T, U> ()
T f(const vector<T>& vt, const vector<U>& vu)
{
	T ret{ 0 };
	for (int i{ 0 }; i < vt.size() && i < vu.size(); ++i)
	{
		ret += vt.at(i) * T(vu.at(i));
	}
	return ret;
}

int main()
{
	vector<Number<int>> vin = { {0}, {-1}, {2}, {-3}, {4}, {-5} };
	vector<Number<double>> vdn = { {0.0}, {1.1}, {2.2}, {3.3}, {4.4}, {5.5} };
	vector<Number<unsigned int>> vun = { {0}, {1}, {2}, {3}, {4}, {5} };
	cout << "Sum of increase = " << f(vun, vdn);

	return 0;
}