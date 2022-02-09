#include "Lesson19.h"

using namespace MyLib;

Int& Int::operator= (const Int& right)
{
	val = right.val;
	return *this;
}

Int Int::operator+ (const Int& right)
{
	return val + right.val;
}

Int Int::operator- (const Int& right)
{
	return val - right.val;
}

Int Int::operator* (const Int& right)
{
	return val * right.val;
}

Int Int::operator/ (const Int& right)
{
	return val / right.val;
}

ostream& MyLib::operator<< (ostream& os, const Int& obj)
{
	return os << obj.val;
}

istream& MyLib::operator>> (istream& is, const Int& obj)
{
	return is >> obj.val;
}