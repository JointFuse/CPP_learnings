#include "lesson18_lib.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	char orig[24];
	orig[23] = 'w';
	char two[8];
	two[7] = 'w';
	double x{166.54};
	int y[1000];
	int ptr = Lib18::strcmp(&orig[0], &two[0]);
	char* cptr = Lib18::strdup(&two[0]);
	cout << ptr << '\n' << (cptr == nullptr ? "not find" : cptr) << '\n';

	cout << Lib18::cat_dot("Nils", "Bor", " and ") << '\n';
	
	string s1{"ffff"};
	string s2{"sssss"};
	string dot{"ddddd"};
	char* conc = Lib18::cat_dotc(&s1[0], &s2[0]);
	cout << conc << '\n';
	delete[] conc;

	for (string s; cin >> s;) {
		cout << s << " is:\n"
			 << s << (s == Lib18::reverse(s) ? " == " : " /= ") << Lib18::reverse(s) << '\n'
			 << "string: " << (Lib18::is_palindrome(s) ? "yes\n" : "no\n")
			 << "massive: " << (Lib18::is_palindrome(&s[0], s.size()) ? "yes\n" : "no\n")
			 << "array: " << (Lib18::is_palindrome(&s[0], &s[s.size() - 1]) ? "yes\n" : "no\n");
	}

	return 0;
}