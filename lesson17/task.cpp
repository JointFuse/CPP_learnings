#include <iostream>
#include <vector>
#include <math.h>

void print_array(std::ostream&, int*, int n = 10);
void print_vector(const std::vector<int>&);

int main()
{
	int* iptr = new int[10];
	for (int i{ 0 }; i < 10; ++i) {
		std::cout << iptr[i] << '\n';
	}
	delete[] iptr;

	int n{20};
	int* iptr2 = new int[n];
	for (int i{ 0 }; i < n; ++i) {
		iptr2[i] = 100 + i;
	}
	print_array(std::cout, iptr2, n);
	delete[] iptr2;

	std::vector<int> vin(20, 100);
	for(int& i : vin) { 
		static int j{0}; 
		i += j++;
	}
	print_vector(vin);

	std::cout << "\n\n";

	int* p1 = new int(7);
	std::cout << "p1 = " << p1 << 
				 "; *p1 = " << *p1 << '\n';

	int* p2 = new int[7];
	for (int i{ 0 }; i < 7; ++i) {
		p2[i] = int(pow(2, i));
	}
	std::cout << "array = " << p2 << '\n';
	print_array(std::cout, p2, 7);
	
	int* p3 = p2;

	delete[] p2;
	p2 = p1;
	p3 = p2;
	std::cout << "p1 = " << p1 << "; *p1 = " << *p1 << '\n'
			  << "p2 = " << p2 << "; *p2 = " << *p2 << '\n';
	
	delete p1;
	p1 = new int[10];
	for (int i{ 0 }; i < 10; ++i) { p1[i] = pow(2, i); }
	p2 = new int[10];
	for (int i{ 0 }; i < 10; ++i) { p2[i] = p1[i]; }
	print_array(std::cout, p2);
	delete[] p1;
	delete[] p2;

	std::vector<int> v1(10);
	std::vector<int> v2(10);
	for (int& i : v1) { static int j{0}; i = pow(2, j++); }
	v2 = v1;
	print_vector(v2);

	return 0;
}

void print_array(std::ostream& os, int* a, int n)
{
	for (int i{ 0 }; i < n; ++i) {
		os << "m[" << i << "] = " << a[i] << ";\n";
	}
}

void print_vector(const std::vector<int>& v)
{
	for (int i : v) { std::cout << i << '\n'; }
}