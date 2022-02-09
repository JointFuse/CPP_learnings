#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int main()
{
	map<string, int> words;

	ifstream text{"simple.txt"};

	for (string s; text >> s; )
		{ ++words[s]; }

	multimap<int, string> counts;
	for (const auto& p : words)
		{ counts.insert({ p.second, p.first }); }
	for (const auto& p : counts) { 
		cout << p.first << ": "
			 << p.second << '\n';
	}
	
	return 0;
}