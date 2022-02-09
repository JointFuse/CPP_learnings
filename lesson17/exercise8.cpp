#include <iostream>
#include <string>
#include <vector>

int main()
{
	std::string mass;
	for(char ch{' '}; ch != '!'; std::cin >> ch)
		mass.push_back(ch);
	mass.erase(mass.begin());
	std::cout << mass << '\n';

	return 0;
}