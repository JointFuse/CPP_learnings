#include "my_graph.h"
#include "Simple_window.h"

int main()
try {
	const double pi{ 3.14159265 };
	Point el1{ 400 + int(150 * cos(pi / 3)), 300 + int(100 * sin(pi / 3)) };
	Point el2{ 400 + int(150 * cos(pi * 3 / 5)), 300 + int(100 * sin(pi * 3 / 5)) };
	Simple_window win(Point{ 50, 50 }, 800, 600, "Exercise 11");
	Ellipse elps(Point{ 400, 300 }, 150, 100);
	Line elf1(elps.focus1(), el1);
	Line elf2(elps.focus2(), el2);
	Axis x(Axis::Orientation::x, Point{ 200, 300 }, 400, 16, "x");
	Axis y(Axis::Orientation::y, Point{ 400, 450 }, 300, 12, "y");
	Marks focus("o");
	focus.add(elps.focus1());
	focus.add(elps.focus2());
	win.attach(elps);
	win.attach(x);
	win.attach(y);
	win.attach(focus);
	win.attach(elf1);
	win.attach(elf2);
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