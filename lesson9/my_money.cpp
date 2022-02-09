#include "my_money.h"

using namespace Finance;

const string usd{ "USD" };
const string eur{ "EUR" };
const string aud{ "AUD" };
const string gbp{ "GBP" };
const string gnf{ "GNF" };
const string hkd{ "HKD" };
const string rub{ "RUB" };
const string cny{ "CNY" };
const string chf{ "CHF" };

//--in-out-stream------------------------------------------

ostream& Finance::operator<< (ostream& os, const Money& m)
{
	switch (m.current()) {
	case USD:
		os << "USD";
		break;
	case EUR:
		os << "EUR";
		break;
	case AUD:
		os << "AUD";
		break;
	case GBP:
		os << "GBP";
		break;
	case GNF:
		os << "GNF";
		break;
	case HKD:
		os << "HKD";
		break;
	case RUB:
		os << "RUB";
		break;
	case CNY:
		os << "CNY";
		break;
	case CHF:
		os << "CHF";
		break;
	default:
		os << "default";
	}

	return os << m.dollar();
}

istream& Finance::operator>> (istream& is, Money& m)
{
	char ch;
	cin >> ch;
	if (isdigit(ch)) {
		double d;
		cin.putback(ch);
		cin >> d;
		m.set(USD, d);
		return is;
	}

	if (!isalpha(ch)) throw runtime_error("incorrect money input");
	
	string str{ "" };
	cin.putback(ch);
	for (int i = 0; i < 3; ++i) { cin >> ch; str += ch;	}
	
	cin >> ch;
	if (!isdigit(ch)) throw runtime_error("incorrect summ input");
	cin.putback(ch);

	double d;
	cin >> d;
	if (str == usd) { m.set(USD, d); return is; }
	if (str == eur) { m.set(EUR, convert(EUR, d)); return is; }
	if (str == aud) { m.set(AUD, convert(AUD, d)); return is; }
	if (str == gbp) { m.set(GBP, convert(GBP, d)); return is; }
	if (str == gnf) { m.set(GNF, convert(GNF, d)); return is; }
	if (str == hkd) { m.set(HKD, convert(HKD, d)); return is; }
	if (str == rub) { m.set(RUB, convert(RUB, d)); return is; }
	if (str == cny) { m.set(CNY, convert(CNY, d)); return is; }
	if (str == chf) { m.set(CHF, convert(CHF, d)); return is; }
	
	throw runtime_error("incorrect current");
}

//--quick-math---------------------------------------------

Money& Money::operator= (const Money& m)
{
	cur = m.current();
	cent = m.cent;
	return *this;
}

Money& Money::operator= (const double& x)
{
	set(USD, x);
	return *this;
}

//---------------------------------------------------------

Money Money::operator+ (const Money& m)
{
	Money mbuf;
	mbuf.cent = cent + m.cent;
	return mbuf;
}

Money Money::operator- (const Money& m)
{
	Money mbuf;
	mbuf.cent = cent - m.cent;
	return mbuf;
}

Money Money::operator/ (const Money& m)
{
	Money mbuf;
	mbuf.cent = cent / m.cent;
	return mbuf;
}

//---------------------------------------------------------

Money Money::operator+ (const double& x)
{
	Money mbuf;
	mbuf.cent = cent + (long int(x * 1000) % 10 >= 5 ? 1 : 0) + long int(x * 100);
	return mbuf;
}

Money Money::operator- (const double& x)
{
	Money mbuf;
	mbuf.cent = cent - (long int(x * 1000) % 10 >= 5 ? 1 : 0) - long int(x * 100);
	return mbuf;
}

Money Money::operator* (const double& x)
{
	Money mbuf;
	double buf{ cent * 10 * x };
	mbuf.cent = long int(buf);
	mbuf.cent = (mbuf.cent % 10 >= 5 ? 1 : 0) + mbuf.cent / 10;
	return mbuf;
}

Money Money::operator/ (const double& x)
{
	Money mbuf;
	double buf{ cent * 10 / x };
	mbuf.cent = long int(buf);
	mbuf.cent = (mbuf.cent % 10 >= 5 ? 1 : 0) + mbuf.cent / 10;
	return mbuf;
}

//--bool-math----------------------------------------------

bool Money::operator== (const Money& m)
{
	return cent == m.cent;
}

bool Money::operator!= (const Money& m)
{
	return cent != m.cent;
}

bool Money::operator> (const Money& m)
{
	return cent > m.cent;
}

bool Money::operator< (const Money& m)
{
	return cent < m.cent;
}

//--Help-functions-----------------------------------------

double Finance::convert(Current cur, double sum)
{
	switch (cur) {
	case USD:
		break;
	case EUR:
		sum *= 1.176;
		break;
	case AUD:
		sum *= 0.743;
		break;
	case GBP:
		sum *= 1.378;
		break;
	case GNF:
		sum *= 1.217;
		break;
	case HKD:
		sum *= 0.128;
		break;
	case RUB:
		sum *= 0.014;
		break;
	case CNY:
		sum *= 0.149;
		break;
	case CHF:
		sum *= 1.095;
		break;
	default:
		throw runtime_error("uneccaptable current");
	}

	return sum;
}

//--Money-class-realization--------------------------------

Money::Money(Current cur, double sum)
	:cent{ 0 }, cur{ cur }
{
	if (sum < 0) sum *= -1;
	set(cur, convert(cur, sum));
}

Money::Money(double sum)
	:cent{ 0 }, cur{ USD }
{
	if (sum < 0) sum *= -1;
	set(cur, convert(cur, sum));
}

void Money::set(Current c, double d)
{
	cur = c;
	cent = d * 1000;
	cent = (cent % 10 >= 5 ? 1 : 0) + cent / 10;
}