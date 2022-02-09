#include "Simple_window.h"
#include "my_window.h"

int main()
try {
	Lines_window win({100, 100}, 700, 500, "Lines");

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