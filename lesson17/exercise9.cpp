#include <iostream>

int main()
{
	for (int i{ 0 }; i < 10; ++i) {
		char* ptr = new char[100];
		std::cout << (void*)ptr << '\n';
	}

	return 0;
}