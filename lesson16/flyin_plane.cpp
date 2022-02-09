#include "my_window.h"
#include "Simple_window.h"

int main()
try {
	Fly_plane win({ 0, 0 }, 800, 600);

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