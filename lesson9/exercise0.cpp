#include "exercise0.h"

void is_date(int y, Month m, int d)
{
	if (d < 1) throw runtime_error("Day can't be negative or zero!");
	if (m < Month::jan || m > Month::dec) throw runtime_error("Month must be below 1 and 12!");

	int day_in_month = 31;
	switch (m) {
	case Month::feb:
		day_in_month = 28;
		break;
	case Month::apr: case Month::jun:
	case Month::sep: case Month::nov:
		day_in_month = 30;
		break;
	}
	if (day_in_month < d) throw runtime_error("Too many days!");
}

void Version1::init_day(Date& dd, int y, int m, int d)
{
	is_date(y, Month(m), d);

	dd.d = d;
	dd.m = m;
	dd.y = y;
}

void Version1::add_day(Date& dd, int n)
{
	for (int i = 0; i < n; ++i) {
		switch (dd.m) {
		case 1: case 3: case 5:	case 7:
		case 8:	case 10: case 12:
			if (dd.d < 31) { dd.d += 1; break; }
		case 4: case 6:
		case 9: case 11:
			if (dd.d < 30) { dd.d += 1; break; }
		case 2:
			if (dd.d < 28) { dd.d += 1; break; }
		default:
			if (dd.m == 12) { dd.m = 0; }
			dd.d = 1;
			dd.m += 1;
		}
	}
}

Version2::Date::Date(int yy, int mm, int dd)
	: y{ yy }, m{ mm }, d{ dd }
{
	is_date(yy, Month(mm), dd);
}

void Version2::Date::add_day(int n)
{
	for (int i = 0; i < n; ++i) {
		switch (m) {
		case 1: case 3: case 5:	case 7:
		case 8:	case 10: case 12:
			if (d < 31) { d += 1; break; }
		case 4: case 6:
		case 9: case 11:
			if (d < 30) { d += 1; break; }
		case 2:
			if (d < 28) { d += 1; break; }
		default:
			if (m == 12) { m = 0; }
			d = 1;
			m += 1;
		}
	}
}

Version3::Date::Date(int yy, Month mm, int dd)
	: y{ yy }, m{ mm }, d{ dd }
{
	is_date(yy, mm, dd);
}

void Version3::Date::add_day(int n)
{
	for (int i = 0; i < n; ++i) {
		switch (m) {
		case Month::jan: case Month::mar: case Month::may:	case Month::jul:
		case Month::aug:	case Month::oct: case Month::dec:
			if (d < 31) { d += 1; break; }
		case Month::apr: case Month::jun:
		case Month::sep: case Month::nov:
			if (d < 30) { d += 1; break; }
		case Month::feb:
			if (d < 28) { d += 1; break; }
		default:
			d = 1;
			++m;
		}
	}
}

void Version3::Date::add_month()
{
	++m;
}

void Version3::Date::add_year(int n)
{
	y += n;
}

Month& operator++ (Month& m)
{
	return m = (m == Month::dec) ? Month::jan : Month(int(m) + 1);
}

ostream& operator<< (ostream& os, const Version1::Date& d)
{
	return os << '(' << d.y << ',' << d.m << ',' << d.d << ')';
}

ostream& operator<< (ostream& os, const Version2::Date& d)
{
	return os << '(' << d.y << ',' << d.m << ',' << d.d << ')';
}

ostream& operator<< (ostream& os, const Version3::Date& d)
{
	return os << '(' << d.year() << ',' << int(d.month()) << ',' << d.day() << ')';
}