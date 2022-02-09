#include "Simple_window.h"
#include "my_graph.h"

double leb(double x, int n) 
{ 
	return n > 1 ? pow(-1.0, n) * pow(x, 2 * n - 1) / (2 * n + 1) + leb(x, n-1) : 1; 
}

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

	const double xscale{ xlength  / 2 / pi };
	constexpr double yscale{ 40 };

	Simple_window win({ 50, 50 }, xmax, ymax, "lesson 15");
	Scale xs(xorig, 0, xscale);
	Scale ys(yorig, 0, yscale);

	Axis Ox(Axis::x, { orig.x - xlength / 2, orig.y }, xlength, xlength / xscale, "Ось X");
	Axis Oy(Axis::y, { orig.x, orig.y + ylength / 2 }, ylength, ylength / yscale, "Ось Y");
	Ox.set_color(Graph_lib::Color::red);
	Oy.set_color(Graph_lib::Color::red);
	Ox.label.move(-xlength / 4, 0);
	win.attach(Ox);
	win.attach(Oy);

	const double A{ -pi };
	const double B{ pi };
	constexpr int resol{ 400 };

	Function sinus(sin, A, B, orig, resol, xscale, yscale);
	Function cosinus(cos, A, B, orig, resol, xscale, yscale);
	Function trigsum([](double x) {return sin(x) + cos(x); }, A, B, orig, resol, xscale, yscale);
	Function something([](double x) {return sin(x) * sin(x) + cos(x) * cos(x); }, A, B, orig, resol, xscale, yscale);
	cosinus.set_color(Graph_lib::Color::blue);
	trigsum.set_color(Graph_lib::Color::green);
	something.set_color(Graph_lib::Color::magenta);
	win.attach(sinus);
	win.attach(cosinus);
	win.attach(trigsum);
	win.attach(something);

	win.wait_for_button();

	win.detach(sinus);
	win.detach(cosinus);
	win.detach(trigsum);
	win.detach(something);

	for (int n = 0; n < 9; ++n) {
		ostringstream label;
		label << "ряд Лейбница, n = " << n;
		win.set_label(label.str());

		Func lebn([n](double x) {return leb(x, n); }, A, B, orig, resol, xscale, yscale, 100);
		win.attach(lebn);
		win.wait_for_button();
		win.detach(lebn);
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