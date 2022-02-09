#include "Order.h"
#include <iomanip>
#include <sstream>
#include <numeric>
#include <algorithm>

using namespace Order_lib;

//---------------------------------------------------------------------------------------------------

string Order::customer_info() const
{
	ostringstream out;
	out << name << " " << brthd << " from: " << addr;
	return out.str();
}

//---------------------------------------------------------------------------------------------------

string Order::check_info() const
{
	ostringstream out;
	out << "Total purchases: " << check_size() << " differents, "
		<< "summ = " << accumulate(check.begin(), check.end(), 0.0,
								   [](double v, const Purchase& p)
								   { return v + p.sum(); });
	return out.str();
}

//---------------------------------------------------------------------------------------------------

ostream& Order_lib::operator<< (ostream& os, const Purchase& p)
{
	return os << p.name() << ' ' << p.price() << ' ' << p.count();
}

//---------------------------------------------------------------------------------------------------

istream& Order_lib::operator>> (istream& is, Purchase& p)
{
	char ch1, ch2;
	string name;
	double pr;
	int c;
	is >> ch1 >> name >> pr >> c >> ch2;
	if (ch1 != '[' || ch2 != ']') {
		is.clear(ios_base::failbit);
		return is;
	}
	p.n = name;
	p.uprice = pr;
	p.cnt = c;
	return is;
}

//---------------------------------------------------------------------------------------------------

ostream& Order_lib::operator<< (ostream& os, const Order& ord)
{
	os << ord.customer_info() << '\n';
	for (int i{ 0 }; i < ord.check_size(); ++i) {
		ostringstream cnt_and_price;
		cnt_and_price << ord[i].count() << " x " << ord[i].price();
		os << '\t' << setw(check_namew) << ord[i].name()
		   << setw(check_pricew) << cnt_and_price.str()
		   << setw(check_sumw) << ord[i].sum() << '\n';
	}
	os << ord.check_info() << '\n';
	for (int i{ 0 }; i < 55; ++i)
		{ os << '_'; }
	return os << '\n';
}

//---------------------------------------------------------------------------------------------------

istream& Order_lib::operator>> (istream& is, Order& ord)
{
	char ch;
	is >> ch;
	if (ch != '{') {
		is.clear(ios_base::failbit);
		return is;
	}

	string name, addr;
	Chrono::date brthd;
	is >> name >> brthd >> addr;
	if (is.rdstate() || addr != "from:") {
		is.clear(ios_base::failbit);
		return is;
	}

	addr = "";
	for (string buf{ "" }; buf != ":"; is >> buf) {
		if (is.rdstate()) {
			is.clear(ios_base::failbit);
			return is;
		}
		buf += " ";
		addr += buf;
	}

	Order buf{ name, brthd, addr };

	is >> ch;
	while (ch != '}') {
		is.unget();
		Purchase pur;
		is >> pur;
		if (is.rdstate()) {
			is.clear(ios_base::failbit);
			return is;
		}
		buf.add_purch(pur);
		is >> ch;
	}
	ord = buf;
	return is;
}

//---------------------------------------------------------------------------------------------------
