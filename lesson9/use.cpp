#include "my_money.h"

using namespace Finance;
int main()
try{
	Money my;
	cin >> my;
	cout << my << '\n';

	return 0;
}
catch (exception& e) {
	cout << "Exception: " << e.what() << endl;
	return 1;
}
catch (...) {
	cout << "Unknown exception!" << endl;
	return 2;
}