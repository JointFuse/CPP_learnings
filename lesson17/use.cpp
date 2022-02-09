#include <iostream>
#include <string>
#include "lesson17_lib.h"

int main()
{
	std::string cstr{"QWERTYUIOPASDFGHJKLZXCVBNMqldhcgs';]123^#@%&0"};
	My_pointers::to_lower(&cstr[0]);
	std::cout << cstr << '\n';

	char* strcopy = My_pointers::strdup(&cstr[0]);
	std::cout << "Copy of string: ";
	for (int i{ 0 }; strcopy[i] != '0'; ++i)
		std::cout << strcopy[i];
	std::cout << '\n';
	delete[] strcopy;

	std::string orig{"ghj0"};
	char* finded = My_pointers::findx(&cstr[0], &orig[0]);
	if(finded != nullptr)
		std::cout << finded << '\n';

	return 0;
}