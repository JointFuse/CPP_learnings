#include "Lesson19.h"
#include <string>

using namespace MyLib;

int main()
{
	File_handle test{"test_file.txt"};
	string str;
	getline(*test, str);
	cout << str << '\n';
	test >> str;
	cout << str << '\n';
	test << "\nthis one you writed from prog" << flush;
	getline(*test, str);
	cout << str << '\n';
	getline(*test, str);
	cout << str << '\n';

	return 0;
}