#include "my_math.h"

using namespace Math;

double Rational::get_double() const
{
	double d{ 0 };
	return d = top * 1.0 / bottom;
}

Rational& Rational::operator= (const Rational& right)
{
	top = right.top;
	bottom = right.bottom;

	return *this;
}

Rational& Rational::operator+ (const Rational& right)
{
	top = top + right.top;
	bottom = bottom + right.bottom;

	return *this;
}

Rational& Rational::operator- (const Rational& right)
{
	top = top - right.top;
	bottom = bottom - right.bottom;

	return *this;
}

Rational& Rational::operator* (const Rational& right)
{
	top = top * right.top;
	bottom = bottom * right.bottom;

	return *this;
}

Rational& Rational::operator/ (const Rational& right)
{
	int buf{ right.top };
	top = top * right.bottom;
	bottom = bottom * buf;

	return *this;
}

bool Rational::operator== (const Rational& right)
{
	if (top == right.top && bottom == right.bottom)
		return true;

	return false;
}

ostream& Math::operator<< (ostream& os, const Rational& r)
{
	return os << r.get_top() << '/' << r.get_bot();
}