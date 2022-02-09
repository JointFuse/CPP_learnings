#include <iostream>

using namespace std;

int ga[10] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 };

void f(int m[], int n)
{
	int la[10];
	for (int i{ 0 }; i < 10; ++i)
		la[i] = ga[i];

	for (int i{ 0 }; i < 10; ++i)
		cout << "la[" << i << "] = " 
			 << la[i] << "; ";
	cout << '\n';

	int* p = new int[n];
	for (int i{0}; i < n; ++i)
		p[i] = m[i];

	for (int i{0}; i < n; ++i)
		cout << "p[" << i << "] = "
			 << p[i] << "; ";
	cout << '\n';

	delete[] p;
}

int fac(int n) { return n == 0 ? 1 : n * fac(n - 1); }

int main()
{
	f(ga, 10);
	
	int aa[10];
	for (int i{0}; i < 10; ++i)
		aa[i] = fac(i + 1);

	f(aa, 10);

	return 0;
}