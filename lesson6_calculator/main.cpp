#include "calculator.h"

int main()
try {
	setlocale(LC_ALL, "Russian");
	system("chcp 1251");

	Calculator::st.define("k", 1000, true);

	Calculator::calculate();

	return 0;
}
catch (exception& e) {
	*Calculator::my_ostream << "exception: " << e.what() << endl;
	char c;
	while (*Calculator::my_istream >> c && c != ';');
	return 1;
}
catch (...) {
	*Calculator::my_ostream << "exception\n";
	char c;
	while (*Calculator::my_istream >> c && c != ';');
	return 2;
}