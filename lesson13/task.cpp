#include "Graph.h"
#include "Simple_window.h"

int main()
try{
	Simple_window win{ Point{50, 50}, 1000, 800, "Task" };
	Lines grid;
	Vector_ref<Rectangle> diag_rec;
	for (int n{ 0 }; n < 9; ++n) {
		grid.add(Point{ 0 + 100 * n,0 }, Point{ 0 + 100 * n, 800 });
		grid.add(Point{ 0, 0 + 100 * n}, Point{ 800, 0 + 100 * n });
	}
	for (int n{ 0 }; n < 8; ++n) {
		diag_rec.push_back(new Rectangle(Point{ 100 * n, 100 * n },
										 Point{ 100 * (n + 1), 100 * (n + 1) }));
		diag_rec[diag_rec.size() - 1].set_fill_color(Color::red);
		win.attach(diag_rec[diag_rec.size() - 1]);
	}
	Image i1(Point{ 200, 0 }, "picture.jpg");
	Image i2(Point{ 100, 500 }, "picture.jpg");
	Image i3(Point{ 500, 300 }, "picture.jpg");
	i1.set_mask(Point{ 120, 10 }, 200, 200);
	i2.set_mask(Point{ 120, 10 }, 200, 200);
	i3.set_mask(Point{ 120, 10 }, 200, 200);
	win.attach(i1);
	win.attach(i2);
	win.attach(i3);
	win.attach(grid);
	Image muv(Point{ 0, 0 }, "muv_pic.jpg");
	muv.set_mask(Point{ 45, 38 }, 100, 100);
	win.attach(muv);
	int xy{ 100 };
	while (true) {
		win.wait_for_button();
		muv.set_point(0, Point{ xy, xy });
		xy += 100;
		if (xy == 800) xy = 0;
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