#include "my_graph.h"
#include "Simple_window.h"

int main()
try{
	Simple_window win(Point{ 20, 20 }, 800, 600, "Lesson 13");
 	Text_box wind(Point{ 90, 50 }, "Window");
	Text_box linest(Point{ 310, 50 }, "Line_style");
	Text_box col(Point{ 500, 50 }, "Color");
	Text_box swind(Point{ 60, 150 }, "Simple_window");
	Arrow sw_w(Point{ 130, 150 }, Point{ 130, 90 }, 8, 4);
	Text_box shp(Point{ 340, 130 }, "Shape");
	Text_box pnt(Point{ 540, 150 }, "Point");
	Text_box ln(Point{ 20, 300 }, "Line");
	Text_box lns(Point{ 100, 300 }, "Lines");
	Text_box plg(Point{ 190, 300 }, "Polygon");
	Text_box axs(Point{ 300, 300 }, "Axis");
	Text_box rect(Point{ 390, 300 }, "Rectangle");
	Text_box tex(Point{ 520, 300 }, "Text");
	Text_box img(Point{ 620, 300 }, "Image");
	Arrow q(Point{ 40, 300 }, Point{ 350, 170 }, 8, 4);
	Arrow w(Point{ 120, 300 }, Point{ 358, 170 }, 8, 4);
	Arrow e(Point{ 210, 300 }, Point{ 366, 170 }, 8, 4);
	Arrow r(Point{ 320, 300 }, Point{ 374, 170 }, 8, 4);
	Arrow t(Point{ 450, 300 }, Point{ 382, 170 }, 8, 4);
	Arrow y(Point{ 540, 300 }, Point{ 390, 170 }, 8, 4);
	Arrow u(Point{ 630, 300 }, Point{ 398, 170 }, 8, 4);
	win.attach(wind);
	win.attach(linest);
	win.attach(col);
	win.attach(swind);
	win.attach(sw_w);
	win.attach(shp);
	win.attach(pnt);
	win.attach(ln);
	win.attach(lns);
	win.attach(plg);
	win.attach(axs);
	win.attach(rect);
	win.attach(tex);
	win.attach(img);
	win.attach(q);
	win.attach(w);
	win.attach(e);
	win.attach(r);
	win.attach(t);
	win.attach(y);
	win.attach(u);
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