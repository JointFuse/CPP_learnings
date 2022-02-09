#include <iostream>
#include "lesson18_lib.h"

int main()
{
	Lib18::Skip_list slist{ 5 };
	slist.add("s");
	slist.add("q");
	slist.add("a");
	slist.add("sq");
	slist.add("sd");
	slist.add("sv");
	slist.add("vs");
	slist.add("sr");
	slist.add("h");
	slist.add("sz");
	slist.add("sk");
	slist.add("k");
	slist.add("p");
	slist.add("b");
	slist.add("c");
	slist.add("sa");
	slist.add("sd");
	slist.add("w");
	slist.add("n");
	slist.add("m");
	std::cout << slist.search("h") << '\n';
	std::cout << slist.search("w") << '\n';
	std::cout << slist.search("a") << '\n';

	return 0;
}