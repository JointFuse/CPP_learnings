#include <iostream>
#include "lesson18_lib.h"

static int g{1};

long int f()
{
	int s{1};
	return reinterpret_cast<long int>(&s);
}

int main()
{
	char* m = new char[9999999];
	long int* add = new long int[3];
	add[0] = reinterpret_cast<long int>(&g);
	add[2] = f();
	int* d = new int{1};
	add[1] = reinterpret_cast<long int>(d);
	std::cout << "Global memory int &g =\t" << std::hex << add[0] << '\n'
			  << "Dynamic memory int* d =\t" << add[1] << '\n'
			  << "Stack memory f() =\t" << add[2] << '\n'
			  << "massive &add[0] =\t" << reinterpret_cast<long int>(&add[0]) << '\n'
			  << "massive &add[2] =\t" << reinterpret_cast<long int>(&add[2]) << '\n';
	Lib18::is_palindrome(&m[0], 999999999);

	return 0;
}