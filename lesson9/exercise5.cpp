#include "exercise5.h"

string Book::date_get() const
{
	stringstream out;
	out << reg_date;

	return out.str();
}