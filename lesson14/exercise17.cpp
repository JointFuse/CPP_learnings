#include "Simple_window.h"
#include "my_graph.h"

int main()
try {
	Simple_window win({ 20, 20 }, 1000, 700, "lesson 14");

	Binary_tree tree({ 50, 50 }, 6, 30, 30);
	win.attach(tree);
	Color_control tree_contur(&tree);
	tree_contur.set_level(9798304142);
	tree_contur.off();
	tree_contur.show();

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