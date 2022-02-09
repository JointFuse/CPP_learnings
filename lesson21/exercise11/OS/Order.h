#ifndef Order_h
#define Order_h

#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>
#include "chrono.h"

namespace Order_lib {
	using namespace std;

	constexpr int check_namew{ 20 };
	constexpr int check_pricew{ 15 };
	constexpr int check_sumw{ 10 };

	class Purchase {
		string n{ "" };
		double uprice{ NULL };
		int cnt{ NULL };
	public:
		Purchase() { }
		Purchase(string what, double price, int how_mach)
			: n{ what }, uprice{ price }, cnt{ how_mach }
		{
			if (price < 0 || how_mach < 0)
				{ throw exception("wrong purchase info"); }
		}

		double sum()	const { return cnt * uprice; }
		string name()	const { return n; }
		int count()		const { return cnt; }
		double price()	const { return uprice; }

		friend istream& operator>> (istream&, Purchase&);
	};

	class Order {
		vector<Purchase> check;
		Chrono::Date brthd{ Chrono::date() };
		string name{ "default" };
		string addr{ "default" };
	public:
		Order() { }
		Order(string Who, Chrono::Date Birthday, string Addr)
			: brthd{ Birthday }, name{ Who }, addr{ Addr } { }

		double get_total()		const;
		string get_name()		const { return name; }
		string get_addr()		const { return addr; }
		string customer_info()	const;
		string check_info()		const;

		typename vector<Purchase>::size_type check_size() const
		{ return check.size(); }

		void clear() { check.clear(); }
		void add_purch(const Purchase& p) { check.push_back(p); }
		Purchase operator[] (int i) const { return check[i]; }

		friend istream& operator>> (istream&, Order&);
	};

	istream& operator>> (istream&, Purchase&);
	istream& operator>> (istream&, Order&);
	ostream& operator<< (ostream&, const Purchase&);
	ostream& operator<< (ostream&, const Order&);

	template<typename Container>
	extern void order_upload(const Container& ord, string file_name, bool add = true);

	template<typename Container>
	extern void order_download(Container& ord, string file_name);

	template<typename Iter, typename Compare>
	extern void Sort(typename Iter b, typename Iter e, Compare comp);

	template<typename Container>
	extern void sort_and_safe(Container& ords, string file);

	extern vector<Order> search_byname(string name, ifstream&);
	extern vector<Order> search_byproduct(string product, ifstream&);
	extern double total_cost(ifstream&);
	extern void all_from_file(ostream&, ifstream&);

#include "otl.inl"
}
#endif // !Order_h