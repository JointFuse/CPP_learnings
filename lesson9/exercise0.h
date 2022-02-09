#include "std_lib_facilities.h"

enum class Month {
	jan = 1, feb, mar, apr, may, jun,
	jul, aug, sep, oct, nov, dec
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

namespace Version3 {
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
}

Month& operator++ (Month&);

ostream& operator<< (ostream&, const Version1::Date&);
ostream& operator<< (ostream&, const Version2::Date&);
ostream& operator<< (ostream&, const Version3::Date&);