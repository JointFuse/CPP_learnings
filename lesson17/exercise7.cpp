#include <iostream>
#include <string>

int main()
{
	char* dynmas = new char[0];
	char ch{ ' ' };
	std::cin >> ch;
	for (int i{ 1 }; ch != '!'; ++i) {
		char* buf = new char[i];

		for (int j{ 0 }; j < i - 1; ++j) {
			buf[j] = dynmas[j];
		}

		buf[i - 1] = ch;
		delete[] dynmas;
		dynmas = buf;

		std::cin >> ch;
	}
	std::cout << dynmas << '\n';
	delete[] dynmas;

	return 0;
}