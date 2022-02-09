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
	constexpr int yoffset{ 150 };

	constexpr int xspace{ 100 };
	constexpr int yspace{ 50 };

	constexpr int xlength{ xmax - xoffset - xspace };
	constexpr int ylength{ ymax - yoffset - yspace };

	constexpr double xscale{ 66.667 };
	constexpr double yscale{ 20 };

	Simple_window win({ 50, 50 }, xmax, ymax, "lesson 15");
	Scale xs(xorig - xlength / 2, 0, xscale);
	Scale ys(yorig + ylength / 2, 0, -yscale);

	Text OXY({ xs(0), ys(0) }, "1");
	win.attach(OXY);
	OXY.move(-15, 15);
	Text OX12({ xs(12), ys(0) }, "12");
	win.attach(OX12);
	OX12.move(-15, 15);

	Axis Ox(Axis::x, { orig.x - xlength / 2, orig.y + ylength / 2 }, xlength, xlength / xscale, "месяц");
	Axis Oy(Axis::y, { orig.x - xlength / 2 , orig.y + ylength / 2 + int(4 * ylength / yscale) },
							ylength + int(4 * ylength / yscale), ylength / yscale, "температура");
	Ox.set_color(Graph_lib::Color::red);
	Oy.set_color(Graph_lib::Color::red);
	Ox.label.move(-xlength / 4.8, 0);
	win.attach(Ox);
	win.attach(Oy);

	Open_polyline eng;
	win.attach(eng);
	eng.add({ xs(0), ys(4) });
	eng.add({ xs(1), ys(5) });
	eng.add({ xs(2), ys(7) });
	eng.add({ xs(3), ys(9) });
	eng.add({ xs(4), ys(12) });
	eng.add({ xs(5), ys(15) });
	eng.add({ xs(6), ys(18) });
	eng.add({ xs(7), ys(17) });
	eng.add({ xs(8), ys(15) });
	eng.add({ xs(9), ys(12) });
	eng.add({ xs(10), ys(8) });
	eng.add({ xs(11), ys(5) });

	Open_polyline usa;
	win.attach(usa);
	usa.add({ xs(0), ys(-3) });
	usa.add({ xs(1), ys(-2) });
	usa.add({ xs(2), ys(2) });
	usa.add({ xs(3), ys(8) });
	usa.add({ xs(4), ys(14) });
	usa.add({ xs(5), ys(19) });
	usa.add({ xs(6), ys(23) });
	usa.add({ xs(7), ys(22) });
	usa.add({ xs(8), ys(18) });
	usa.add({ xs(9), ys(12) });
	usa.add({ xs(10), ys(6) });
	usa.add({ xs(11), ys(1) });

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