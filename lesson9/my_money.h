#include "std_lib_facilities.h"

namespace Finance {
	enum Current {
		USD, EUR, AUD, 
		GBP, GNF, HKD, 
		RUB, CNY, CHF
	};

	class Money {
	private:
		long int cent;
		Current cur;
	public:
		Money() :cent{ 0 }, cur{ USD } { }
		Money(long int c) : cent{ c }, cur{ USD } { }

		Money(double);
		Money(Finance::Current, double);

		double dollar()		const { return cent * 1.0 / 100; }
		Current current()	const { return cur; }

		void set(Current, double);

		Money& operator= (const Money&);
		Money& operator= (const double&);

		Money operator+ (const Money&);
		Money operator- (const Money&);
		Money operator/ (const Money&);

		Money operator+ (const double&);
		Money operator- (const double&);
		Money operator* (const double&);
		Money operator/ (const double&);

		bool operator== (const Money&);
		bool operator!= (const Money&);
		bool operator> (const Money&);
		bool operator< (const Money&);
	};

	double convert(Current, double);

	ostream& operator<< (ostream&, const Money&);
	istream& operator>> (istream&, Money&);
}