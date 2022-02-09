#include "my_graph.h"
#include "Simple_window.h"

int main()
try {
	Simple_window win(Point{ 100, 100 }, 400, 386, "Exercise 7");
	Circle green(Point{ 250, 150 }, 100);
	Circle red(Point{ 150, 150 }, 100);
	Circle blue(Point{ 200, 236 }, 100);
	Arc yel_red(Point{ 150, 150 }, 100, 100, 0, 60);
	Arc yel_grn(Point{ 250, 150 }, 100, 100, 120, 180);
	Arc mgn_red(Point{ 150, 150 }, 100, 100, 240, 300);
	Arc mgn_blu(Point{ 200, 236 }, 100, 100, 120, 180);
	Arc cyn_grn(Point{ 250, 150 }, 100, 100, 240, 300);
	Arc cyn_blu(Point{ 200, 236 }, 100, 100, 0, 60);
	Arc wht_red(Point{ 150, 150 }, 100, 100, 300, 360);
	Arc wht_grn(Point{ 250, 150 }, 100, 100, 180, 240);
	Arc wht_blu(Point{ 200, 236 }, 100, 100, 60, 120);
	yel_red.set_color(Color::invisible);
	yel_red.set_fill_color(Color::yellow);
	yel_grn.set_color(Color::invisible);
	yel_grn.set_fill_color(Color::yellow);
	mgn_red.set_color(Color::invisible);
	mgn_red.set_fill_color(Color::magenta);
	mgn_blu.set_color(Color::invisible);
	mgn_blu.set_fill_color(Color::magenta);
	cyn_grn.set_color(Color::invisible);
	cyn_grn.set_fill_color(Color::cyan);
	cyn_blu.set_color(Color::invisible);
	cyn_blu.set_fill_color(Color::cyan);
	wht_red.set_color(Color::invisible);
	wht_red.set_fill_color(Color::white);
	wht_grn.set_color(Color::invisible);
	wht_grn.set_fill_color(Color::white);
	wht_blu.set_color(Color::invisible);
	wht_blu.set_fill_color(Color::white);
	blue.set_color(Color::invisible);
	blue.set_fill_color(Color::blue);
	red.set_color(Color::invisible);
	red.set_fill_color(Color::red);
	green.set_color(Color::invisible);
	green.set_fill_color(Color::green);
	win.attach(green);
	win.attach(red);
	win.attach(blue);
	win.attach(yel_red);
	win.attach(yel_grn);
	win.attach(mgn_red);
	win.attach(mgn_blu);
	win.attach(cyn_grn);
	win.attach(cyn_blu);
	win.attach(wht_red);
	win.attach(wht_grn);
	win.attach(wht_blu);
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