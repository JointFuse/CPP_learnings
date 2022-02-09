#include "my_graph.h"
#include "Simple_window.h"

int main()
try {
	const double pi{ 3.14159265 };

	Simple_window win(Point{ 50, 50 }, 800, 600, "exercise 13");
	Vector_ref<Right_triangle> moz;

	for (int i{ 0 }; i < 800; i += 20)
		for (int j{ 0 }; j < 600; j += 10) {
			moz.push_back(new Right_triangle(Point{ i, j }, Point{ i + 20, j + 10 }, -53.13));
			moz.push_back(new Right_triangle(Point{ i + 20, j + 10 }, Point{ i, j }, -53.13));
			win.attach(moz[moz.size() - 1]);
			win.attach(moz[moz.size() - 2]);
		}

	win.wait_for_button();
	return 0;
}
catch (exception& e) {
	cout << e.what() << endl;
	return 1;
}
catch (...) {
	return 2;
}