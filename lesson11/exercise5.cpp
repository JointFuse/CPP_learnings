#include "/Users/tony/source/repos/libs/std_lib_facilities.h"

int main()
{
	for (string s; cin >> s; )
		for (char ch : s) {
			cout << ch << " - ";
			if (isspace(ch))
				cout << "space, ";
			if (isalpha(ch))
				cout << "alpha, ";
			if (isdigit(ch))
				cout << "digit, ";
			if (isxdigit(ch))
				cout << "xdigit, ";
			if (isupper(ch))
				cout << "upper, ";
			if (islower(ch))
				cout << "lower, ";
			if (isalnum(ch))
				cout << "alnum, ";
			if (iscntrl(ch))
				cout << "cntrl, ";
			if (ispunct(ch))
				cout << "punct, ";
			if (isprint(ch))
				cout << "print, ";
			if (isgraph(ch))
				cout << "graph, ";
			cout << '\n';
		}
	return 0;
}