#ifndef Chrono_h
#define Chrono_h

#include <stdexcept>
#include <iostream>

enum class Month {
	jan = 1, feb, mar, apr, may, jun,
	jul, aug, sep, oct, nov, dec
};

enum class Day {
	mon = 1, tue, wed,
	thu, fri, sat, sun
};

namespace Chrono {
	struct date {
		date(int y, Month m, int d);
		date() : y{ 1970 }, m{ Month::jan }, d{ 1 }, sum{ 1 } {}

		int y, d, sum;
		Month m;
	};

	class Date {
	private:
		long int d;
	public:
		Date(date d);

		void add_day(int n) { d += n; }
		void add_month();
		void add_year();

		date convert()	const;
		int day()		const { date d{ convert() }; return d.d; }
		Month month()	const { date d{ convert() }; return d.m; }
		int year()		const { date d{ convert() }; return d.y; }
	};

	bool leapyear(int y);
	int month_to_days(Month m, int y);
	Day day_of_week(Date);
	Date next_sunday(Date);
	Day next_weekday(Date);
}

ostream& operator<< (ostream&, const Chrono::Date&);
ostream& operator<< (ostream& os, const Day& d);

#endif	// !Chrono_h