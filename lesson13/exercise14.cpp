#include "my_graph.h"
#include "Simple_window.h"

int main()
try {
	const double pi{ 3.14159265 };

	Simple_window win(Point{ 50, 50 }, 800, 600, "exercise 13");
	
	Point O{ 400, 300 };
	Vector_ref<Right_triangle> octet;
	int rad{ 100 };

	for (int i{ 0 }; i < 8; ++i) {
		Point h1{ O.x + int(rad * cos(2 * i * pi / 8)),
				  O.y + int(rad * sin(2 * i * pi / 8)) };
		Point h2{ O.x + int(rad * cos(2 * i * pi / 8 + pi)),
				  O.y + int(rad * sin(2 * i * pi / 8 + pi)) };

		octet.push_back(new Right_triangle(h1, h2, 45));

		octet[octet.size() - 1].set_color(i);
		win.attach(octet[octet.size() - 1]);
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