#include "concantinator.h"

int main()
try {
	cout << vocab_concant("data.txt", "copy.txt") << '\n';
	cout << file_summ("data.txt");
	return 0;
}
catch (exception& e) {
	cout << "Exception: " << e.what() << endl;

	return 1;
}
catch (...) {
	cout << "Unknonw problem" << endl;

	return 2;
}