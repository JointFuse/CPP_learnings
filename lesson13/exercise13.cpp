#include "my_graph.h"
#include "Simple_window.h"

int main()
try {
	Simple_window win(Point{ 50, 50 }, 800, 600, "exercise 13");

	Vector_ref<Rectangle> matrix;

	for (int i{ 0 }; i < 16;++i)
		for (int j{ 0 }; j < 16; ++j) {
			matrix.push_back(new Rectangle(Point{ 20 * i, 20 * j }, 20, 20));
			matrix[matrix.size() - 1].set_fill_color(16 * i + j);
			matrix[matrix.size() - 1].set_color(Color::invisible);
			win.attach(matrix[matrix.size() - 1]);
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