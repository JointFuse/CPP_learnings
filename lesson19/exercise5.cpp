#include "Lesson19.h"

using namespace MyLib;

int main()
{
	Number<double> x{12};
	Number<double> y = 3.32;
	Number<double> z = (7.68);
	cout << "x + y = " << x + y << '\n'
		 << "x - z = " << x - z << '\n'
		 << "z * y = " << z * y << '\n'
		 << "x / y = " << x / y << '\n'
		 << "z % y = " << z % y << '\n';
 
	
	return 0;
}