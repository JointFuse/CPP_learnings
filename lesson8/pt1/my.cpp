#include "my.h"
#include "std_lib_facilities.h"

int foo{ 0 };

void print_foo()
{
	cout << '\n' << foo << '\n';
}

void print(int i)
{
	cout << '\n' << i << '\n';
}

void swap_v(int a, int b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

void swap_r(int& a, int& b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

/*void swap_cr(const int& a, const int& b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}*/