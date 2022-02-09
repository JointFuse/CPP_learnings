#include "my_window.h"

int main()
try {
	constexpr int xmax{600};
	constexpr int ymax{500};
	constexpr int xoffset{100};
	constexpr int yoffset{50};
	constexpr int xspace{100};
	constexpr int yspace{50};
	constexpr int xlength{xmax - xoffset - xspace};
	constexpr int ylength{ymax - yoffset - yspace};

	Button_matrix mask({100, 50}, xmax, ymax, 100 );
	Moving_image mi;
	Figures fig({100, 100});
	Moving_figure mfig({100, 100});
	return gui_main();
}
catch (exception& e) {
	cout << "Exception: " << e.what() << endl;
	return 1;
}
catch (...) {
	cout << "Error" << endl;
	return 2;
}