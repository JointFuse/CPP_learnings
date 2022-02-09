#include "Simple_window.h"
#include "my_graph.h"

int main()
try {
	Simple_window win(Point{ 50, 50 }, 800, 600, "lesson 14");

	Striped_closed_polyline sr;
	win.attach(sr);
	sr.add({ 20, 20 });
	sr.add({ 20, 40 });
	sr.add({ 50, 10});
	sr.set_fill_color(Color::blue);
	//sr.set_color(Color::invisible

	Octagon oct(Point{ -30, 40 }, 1050);
	win.attach(oct);
	
	oct.set_center(Point{ 400, 300 });
	oct.set_radius(150);
	oct.move(50, 50);
	oct.set_color(Color::red);
	oct.set_fill_color(Color::yellow);
	oct.set_style(Graph_lib::Line_style(Graph_lib::Line_style::Line_style_type::dashdotdot, 4));

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