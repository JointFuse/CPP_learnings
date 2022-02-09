#include "my_graph.h"
#include "Simple_window.h"

int main()
try {
	const double pi{ 3.14159265 };

	Simple_window win(Point{ 50, 50 }, 800, 600, "exercise 12");
	
	Circle cr(Point{ 400, 300 }, 200);
	cr.set_color(Color::dark_cyan);
	win.attach(cr);
	
	Mark dot(Point{ 400, 300 }, '$');
	win.attach(dot);

	for (int i{ 0 }; true; ++i) {
		int x = 400 + 200 * cos(pi * i / 36);
		int y = 300 + 200 * sin(pi * i / 36);

		dot.set_point(0, Point{ x, y });
		win.wait_for_button();
	}
	return 0;
}
catch (exception& e) {
	cout << "Exception: " << e.what() << endl;
	return 1;
}
catch (...) {
	cout << "Error" << endl;
	return 2;
}