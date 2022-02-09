#include "/Users/tony/source/repos/libs/std_lib_facilities.h"

int main()
{
	stringstream orig{ "qwe eqwe fds fdsfsfa fdsgfs" };
	vector<string> symbs;
	for (string buf; orig >> buf;)
		symbs.push_back(buf);
	for (int i{ 0 }; i <= symbs.size() / 2; ++i)
		swap(symbs[i], symbs[symbs.size() - 1 - i]);
	if (symbs.size() % 2 == 0)
		swap(symbs[symbs.size() / 2 - 1], symbs[symbs.size() / 2]);
	for (string s : symbs)
		cout << s << ' ';
	return 0;
}