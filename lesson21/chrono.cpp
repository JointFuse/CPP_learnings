#include "chrono.h"

using namespace Chrono;

//--helpfull-functions---------------------------------------------------------------------------------

void is_date(Chrono::date d)
{
	if (d.y < 1970) throw runtime_error("Date below zero day!");
	if (d.d < 1) throw runtime_error("Day can't be negative or zero!");
	if (d.m < Month::jan || d.m > Month::dec) throw runtime_error("Month must be below 1 and 12!");

	int day_in_month = 31;
	switch (d.m) {
	case Month::feb:
		day_in_month = 28;
		break;
	case Month::apr: case Month::jun:
	case Month::sep: case Month::nov:
		day_in_month = 30;
		break;
	}
	if (day_in_month < d.d) throw runtime_error("Too many days!");
}

int days_in_year(int y, Month m, int d)
{
	int days{ 0 };

	switch (m) {
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
		if (Chrono::leapyear(y)) ++days;
	case Month::feb:
		days += 31;
	default:
		days += d;
		break;
	}

	return days;
}

int Chrono::days_in_date(date d)
{
	int sum{ 0 };
	for (int i = 0; i < (d.y - 1970); ++i) {
		if (leapyear(i)) sum += 366;
		else sum += 365;
	}

	return sum += days_in_year(d.y, d.m, d.d);
}

//---------------------------------------------------------------------------------------------------------------

Chrono::date::date(int yy, Month mm, int dd)
	: y{ yy }, m{ mm }, d{ dd }, sum{ 0 }
{
	for (int i = 0; i < (y - 1970); ++i) {
		if (leapyear(i)) sum += 366;
		else sum += 365;
	}

	sum += days_in_year(y, m, d);
}

bool Chrono::leapyear(int y)
{
	if (y % 4 == 0) return true;
	return false;
}

int Chrono::month_to_days(Month m, int y)
{
	switch (m) {
	case Month::jan: case Month::mar: case Month::may:	case Month::jul:
	case Month::aug:	case Month::oct: case Month::dec:
		return 31;
	case Month::apr: case Month::jun:
	case Month::sep: case Month::nov:
		return 30;
	case Month::feb:
		if (Chrono::leapyear(y)) return 29;
		else return 28;
	default:
		throw runtime_error("Wrong month!");
	}
}

Day Chrono::day_of_week(Chrono::Date d)
{
	int day{ 0 };
	for (int i = 1970; i < d.year(); ++i)
		day += days_in_year(i, Month::dec, 31);

	day += days_in_year(d.year(), d.month(), d.day()) + 3;
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


//--Date-class-realization-----------------------------------------------------------------------------

Chrono::Date::Date(date d)
	: d{ d.sum }
{
	is_date(d);
}

Chrono::date Chrono::Date::convert() const
{
	int n{ 0 };
	long int days{ d };
	date dat;

	while (days > (leapyear(1970 + n) ? 366 : 365)) {
		days -= (leapyear(1970 + n) ? 366 : 365);
		++n;
	}

	dat.y += n;
	n = 1;

	while (days > month_to_days(Month(n), dat.y)) {
		days -= month_to_days(Month(n), dat.y);
		++n;
	}

	dat.m = Month(n);
	dat.d = (days == 0 ? 1 : days);

	return dat;
}

void Chrono::Date::add_month()
{
	date today{ convert() };
	d += month_to_days(today.m, today.y);
}

void Chrono::Date::add_year()
{
	date today{ convert() };
	d += (leapyear(today.y) ? 366 : 365);
}

//--operators-overloading-----------------------------------------------------------------------------------------

ostream& Chrono::operator<< (ostream& os, const Chrono::Date& d)
{
	return os << '(' << d.year() << ',' << int(d.month()) << ',' << d.day() << ')';
}

ostream& Chrono::operator<< (ostream& os, const Day& d)
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

istream& Chrono::operator>> (istream& is, Chrono::date& dat)
{
	char ch1, ch2, ch3, ch4;
	int y, m, d;
	is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
	if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')' ||
		m < 1 || 12 < m || y < 1970) {
		is.clear(ios_base::failbit);
		return is;
	}

	dat.d = d;
	dat.m = Month(m);
	dat.y = y;
	dat.sum = Chrono::days_in_date(dat);

	return is;
}