#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <map>
#include <algorithm>

using namespace std;

//---------------------------------------------------------------------------------
/* First try it block */

template<typename In, typename T>
In find1(In first, In last, const T& val)
{
	while (first != last && *first != val)
		{ ++first; }
	return first;
}

template<typename In, typename T>
In find2(In first, In last, const T& val)
{
	for (auto p = first; p != last; ++p)
		if (*p == val) { return p; }
	return last;
}

void tryit1()
{
	cout << "Block Try It #1\n";
	vector<int> v{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	auto p1 = find1(v.begin(), v.end(), -5);
	auto p2 = find2(v.begin(), v.end(), -5);

	if (p1 != v.end()) { cout << "found1 = " << *p1 << '\n'; }
	if (p2 != v.end()) { cout << "found2 = " << *p2 << '\n'; }

	p1 = find1(v.begin(), v.end(), 5);
	p2 = find2(v.begin(), v.end(), 5);

	if (p1 != v.end()) { cout << "found1 = " << *p1 << '\n'; }
	if (p2 != v.end()) { cout << "found2 = " << *p2 << '\n'; }
}

//---------------------------------------------------------------------------------
/* Second try it block */

struct Record {
	double unit_price;
	int units;
};

double price(double v, const Record& r)
{
	return v + r.unit_price * r.units;
}

void tryit2()
{
	vector<Record> r{{12.99, 10}, {401.1, 3}, {0.99, 43}, {9.99, 15}};
	cout << "Block Try It #2\n";
	cout << "Total: " << accumulate(r.begin(), r.end(), 0.0, price) << '\n';
}

//---------------------------------------------------------------------------------
/* Third try it block */

double weighted_value(const pair<string, double>& a, 
					  const pair<string, double>& b)
{
	return a.second * b.second;
}

void tryit3()
{
	cout << "Block try it #3\n";
	map<string, double> dow_price = {
		{"MMM", 81.86},
		{"AA", 34.69},
		{"MO", 54.45},
		{"ITS", 98.01}
	};
	map<string, double> dow_weight = {
		{"MMM", 5.8549},
		{"AA", 2.4808},
		{"MO", 3.849},
		{"ITS", 5.9701}
	};
	map<string, string> dow_name = {
		{"MMM", "3m Co."},
		{"AA", "Alcoa Inc."},
		{"MO", "Altria Group Inc."},
		{"ITS", "International telephon security Co."}
	};
	double alcoa_price = dow_price["AA"];
	double somecompany_price = dow_price["MMM"];
	if (dow_price.find("ITS") != dow_price.end())
		{ cout << dow_name["ITS"] << " found!\n"; }
	for (const auto& p : dow_price) {
		const string& symbol = p.first;
		cout << symbol << '\t'
			 << p.second << '\t'
			 << dow_name[symbol] << '\n';
	}
	double dji_index = 
		inner_product(
			dow_price.begin(), dow_price.end(),
			dow_weight.begin(),
			0.0,
			plus<double>(),
			weighted_value);
	cout << "Dow Jones index = " << dji_index << '\n';
}

//---------------------------------------------------------------------------------
/* Four try it block */

void tryit4()
{
	ifstream is{"task_vecdat.txt"};
	ofstream os{"exercise1_outdat.txt"};
	
	vector<double> vd{istream_iterator<double>{is},
					  istream_iterator<double>{}};
	sort(vd.begin(), vd.end());
	copy(vd.begin(), vd.end(),
		 ostream_iterator<double>{os, "\n"});

	/* Here you catch runtime error "can't dereference out of vec iterator" or somesthing like it
	vector<double> wrong(10);
	copy(istream_iterator<double>{is},
		 istream_iterator<double>{},
		 wrong.begin());
	*/
}

//---------------------------------------------------------------------------------

int main()
{
	tryit1();
	tryit2();
	tryit3();
	tryit4();

	return 0;
}