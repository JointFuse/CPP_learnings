#include "std_lib_facilities.h"

namespace Math {
	class Rational {
	private:
		int top;
		int bottom;
	public:
		Rational(int b) : top{ 1 }, bottom{ b } { }
		Rational(int t, int b) : top{ t }, bottom{ b } { }

		int get_top()	const { return top; }
		int get_bot()	const { return bottom; }

		double get_double() const;

		Rational& operator= (const Rational&);
		Rational& operator+ (const Rational&);
		Rational& operator- (const Rational&);
		Rational& operator* (const Rational&);
		Rational& operator/ (const Rational&);

		bool operator== (const Rational&);
	};

	ostream& operator<< (ostream&, const Rational&);
}