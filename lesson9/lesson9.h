#include "std_lib_facilities.h"

enum class Month {
	jan = 1, feb, mar, apr, may, jun,
	jul, aug, sep, oct, nov, dec
};

enum class Day {
	mon = 1, tue, wed,
	thu, fri, sat, sun
};

namespace Version1 {
	struct Date {
		int y;
		int m;
		int d;
	};

	void init_day(Date&, int yy, int mm, int dd);
	void add_day(Date&, int);
}

namespace Version2 {
	struct Date {
		int y, m, d;
		Date(int yy, int mm, int dd);

		void add_day(int);
	};
}

namespace Chrono {
	class Date {
		int y, d;
		Month m;
	public:
		Date(int yy, Month mm, int dd);

		void add_day(int n);
		void add_month();
		void add_year(int n);

		int day()		const	{ return d; }
		Month month()	const	{ return m; }
		int year()		const	{ return y; }
	};

	bool leapyear(int year);
	int days_in_year(Date);
	int week_of_year(Date);
	Date next_workday(Date);
	Day day_of_week(Date);
	Date next_sunday(Date);
	Day next_weekday(Date);
}

Month& operator++ (Month&);

ostream& operator<< (ostream&, const Version1::Date&);
ostream& operator<< (ostream&, const Version2::Date&);
ostream& operator<< (ostream&, const Chrono::Date&);
ostream& operator<< (ostream& os, const Day& d);