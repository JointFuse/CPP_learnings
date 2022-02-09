#include "my_graph.h"
#include "Simple_window.h"

int main()
try {
	Simple_window win(Point{ 50, 50 }, 800, 600, "exercise 18");
	
	Star test(Point{ 100, 400 }, 3, 50);
	test.point_search();
	test.set_fill_color(Color::cyan);
	test.set_color(Color::dark_green);
	Star test1(Point{ 200, 200 }, 7, 70);
	test1.point_search();
	test1.set_fill_color(Color::yellow);
	test1.set_color(Color::dark_magenta);
	Star test2(Point{ 300, 400 }, 13, 90);
	test2.point_search();
	test2.set_fill_color(Color::red);
	test2.set_color(Color::dark_blue);

	win.attach(test);
	win.attach(test1);
	win.attach(test2);

	win.wait_for_button();
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