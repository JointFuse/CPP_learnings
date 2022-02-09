#include "Order.h"
#include <iomanip>
#include <sstream>
#include <numeric>
#include <algorithm>

using namespace Order_lib;

//---------------------------------------------------------------------------------------------------

double Order::get_total() const 
{
	return accumulate(check.begin(), check.end(), 0.0,
					  [](double v, const Purchase& p)
					  { return v + p.sum(); });
}

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
		<< "summ = " << get_total();
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

vector<Order> Order_lib::search_byname(string name, ifstream& orders)
{
	vector<Order> searched;
	copy_if(istream_iterator<Order>(orders),
			istream_iterator<Order>(),
			back_inserter(searched), 
			[&](const Order& ord)
			{ return ord.get_name() == name; });
	return searched;
}

//---------------------------------------------------------------------------------------------------

vector<Order> Order_lib::search_byproduct(string product, ifstream& orders)
{
	vector<Order> searched;
	copy_if(istream_iterator<Order>(orders),
			istream_iterator<Order>(),
			back_inserter(searched),
			[&](const Order& ord) { 
				for (int i{0}; i < ord.check_size(); ++i)
					if (ord[i].name() == product)
						{ return true; }
				return false; 
			});
	return searched;
}

//---------------------------------------------------------------------------------------------------

double Order_lib::total_cost(ifstream& orders)
{
	vector<Order> searched;
	return accumulate(istream_iterator<Order>(orders),
					  istream_iterator<Order>(), 0.0,
					  [](double v, const Order& ord)
					  { return v + ord.get_total(); });
}

//---------------------------------------------------------------------------------------------------

void Order_lib::all_from_file(ostream& os, ifstream& orders)
{
	copy(istream_iterator<Order>(orders),
		 istream_iterator<Order>(),
		 ostream_iterator<Order>(os));
}

//---------------------------------------------------------------------------------------------------
