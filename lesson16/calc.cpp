#include "my_window.h"

int main()
try {
	Func_graphics fgr({ 150, 150 }, 300, 308);

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