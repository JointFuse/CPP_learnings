#include "lesson8.h"

int main()
try{
	vector<string> vs{ "one", "two", "three", "four", "five", "six", "seven", "quit", "futher", "six", "milk", "abs", "will" };
	vector<int> vl = string_analize(vs);
	for (int i : vl)
		cout << i << '\n';
	return 0;
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
	return 1;
}
catch(...){
	cerr << "exception\n";
	return 2;
}