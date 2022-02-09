#include "my_window.h"
#include "Simple_window.h"

int main()
try {
	Currency_converter conv({0, 0}, 500, 150);

	return gui_main();
}
catch (exception& e) {
	cout << "Exception: " << e.what() << endl;
	return 1;
}
catch (...) {
	cout << "Error" << endl;
	return 2;
}