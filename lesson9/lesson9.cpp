#include "lesson9.h"

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

Chrono::Date::Date(int yy, Month mm, int dd)
	: y{ yy }, m{ mm }, d{ dd }
{
	is_date(yy, mm, dd);
}

void Chrono::Date::add_day(int n)
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

void Chrono::Date::add_month()
{
	++m;
}

void Chrono::Date::add_year(int n)
{
	y += n;
}

bool Chrono::leapyear(int y)
{
	if (y % 4 == 0) return true;
	return false;
}

int Chrono::days_in_year(Chrono::Date d)
{
	int days{ 0 };

	switch (d.month()) {
	case Month::dec:
		days += 30;
	case Month::nov:
		days += 31;
	case Month::oct:
		days += 30;
	case Month::sep:
		days += 31;
	case Month::aug:
		days += 31;
	case Month::jul:
		days += 30;
	case Month::jun:
		days += 31;
	case Month::may:
		days += 30;
	case Month::apr:
		days += 31;
	case Month::mar:
		days += 28;
		if (leapyear(d.year())) ++days;
	case Month::feb:
		days += 31;
	default:
		days += d.day();
		break;
	}

	return days;
}

Chrono::Date Chrono::next_workday(Date d)
{
	if (day_of_week(d) == Day::fri) d.add_day(2);
	if (day_of_week(d) == Day::sat) d.add_day(1);
	d.add_day(1);
	return d;
}

int Chrono::week_of_year(Date d)
{
	int n{ 0 };
	n = days_in_year(d);

	if (n % 7 != 0) n += 7;
	n /= 7;

	return n;
}

Day Chrono::day_of_week(Chrono::Date d)
{
	int day{ 0 };
	for (int i = 0; i < (d.year() < 1990 ? d.year() : (d.year() - 1990)); ++i)
		day += days_in_year(Date{ i, Month::dec, 31 });

	day += days_in_year(d);
	day %= 7;

	return Day(day);
}

Chrono::Date Chrono::next_sunday(Chrono::Date d)
{
	d.add_day(7 - int(day_of_week(d)));
	return d;
}

Day Chrono::next_weekday(Chrono::Date d)
{
	d.add_day(1);
	return day_of_week(d);
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

ostream& operator<< (ostream& os, const Chrono::Date& d)
{
	return os << '(' << d.year() << ',' << int(d.month()) << ',' << d.day() << ')';
}

ostream& operator<< (ostream& os, const Day& d)
{
	switch (d) {
	case Day::mon:
		return os << "monday";
	case Day::tue:
		return os << "tuesday";
	case Day::wed:
		return os << "wednesday";
	case Day::thu:
		return os << "thursday";
	case Day::fri:
		return os << "friday";
	case Day::sat:
		return os << "saturday";
	default:
		return os << "sunday";
	}
}