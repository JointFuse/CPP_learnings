#include "Simple_window.h"
#include "my_graph.h"

int main()
try {
	constexpr int xmax{ 1000 };
	constexpr int ymax{ 600 };

	constexpr int xorig{ xmax / 2 };
	constexpr int yorig{ ymax / 2 };
	const Point orig{ xorig, yorig };

	constexpr int xoffset{ 100 };
	constexpr int yoffset{ 50 };

	constexpr int xspace{ 100 };
	constexpr int yspace{ 50 };

	constexpr int xlength{ xmax - xoffset - xspace };
	constexpr int ylength{ ymax - yoffset - yspace };

	constexpr double xscale{ 40 };
	constexpr double yscale{ 40 };

	Simple_window win({ 50, 50 }, xmax, ymax, "lesson 15");
	Scale xs(xorig, 0, xscale);
	Scale ys(yorig, 0, yscale);

	Axis Ox(Axis::x, { orig.x - xlength / 2, orig.y + ylength / 2}, xlength, xlength / xscale, "Îñü X");
	Axis Oy(Axis::y, { orig.x - xlength / 2, orig.y + ylength / 2 }, ylength, ylength / yscale, "Îñü Y");
	Ox.set_color(Graph_lib::Color::red);
	Oy.set_color(Graph_lib::Color::red);
	Ox.label.move( xlength / 1.3, 0);
	win.attach(Ox);
	win.attach(Oy);

	Histogram test({ orig.x - xlength / 2, orig.y + ylength / 2 }, xlength, ylength);
	win.attach(test);
	test.mark_on();
	histogram_load(&test, "data.txt");

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