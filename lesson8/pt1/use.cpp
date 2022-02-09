#include "my.h"
#include <iostream>

using std::cin;
using std::cout;

namespace X {
	int var{ 0 };
	void print()
	{
		cout << '\n' << "X: var = " << var << '\n';
	}
}

namespace Y {
	int var{ 0 };
	void print()
	{
		cout << '\n' << "Y: var = " << var << '\n';
	}
}

namespace Z {
	int var{ 0 };
	void print()
	{
		cout << '\n' << "Z: var = " << var << '\n';
	}
}

int main()
{
	foo = 7;
	print_foo();
	print(99);

	int x = 7;
	int y = 9;
	swap_r(x, y);
	cout << "x = " << x << "; y = " << y << '\n';

	X::var = 7;
	X::print();				// ����� var �� ������������ ���� �
	using namespace Y;
	var = 9;
	print();				// ����� var �� ������������ ���� Y
	{
		using Z::var;
		using Z::print;
		var = 11;
		print();			// ����� var �� ������������ ���� Z
	}
	print();				// ����� var �� ������������ ���� Y
	X::print();				// ����� var �� ������������ ���� X

	char cc;
	cin >> cc;
}