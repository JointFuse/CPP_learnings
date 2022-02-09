#include "my_graph.h"
#include "Simple_window.h"

int main()
try {
	const double pi{ 3.14159265 };

	Simple_window win(Point{ 100, 100 }, 800, 600, "Exrecise 11");
	Vector_ref<Regular_hexagon> moz;

	int rad{ 10 };
	int hgt{ int(rad * sin(60 * pi / 180)) };

	for (int i{ 0 }; i < 60; ++i)
		for (int j{ 0 }; j < 60; ++j) {
			moz.push_back(new Regular_hexagon(Point{ int(rad * (i * 1.5 + (i % 2 != 0 ? 1 : 1))),
														 hgt * (j * 2 + (i % 2 != 0 ? 2 : 1)) }, rad));
			moz[moz.size() - 1].set_color(Color::invisible);
			moz[moz.size() - 1].set_fill_color(i * j % 255);
			win.attach(moz[moz.size() - 1]);
		}

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