#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <vector>
#include <string>

using namespace std;

template<typename N, typename V>
class Pair {
	vector<N> nm;
	vector<V> vl;
	N void_nm;
	V void_vl;
public:
	Pair(N def_name = N(0), V def_value = V(0)) 
		: nm{}, vl{}, void_nm{def_name}, void_vl{def_value} { }
	Pair(initializer_list<N> names, initializer_list<V> values, N def_name = N(0), V def_value = V(0)) 
		: nm{names}, vl{values}, void_nm{def_name}, void_vl{def_value}
	{ 
		if (names.size() < values.size()) throw exception("names isn't complete values");
		if (values.size() < names.size()) throw exception("values isn't complete names");
	}
	explicit Pair(int n, N def_name = N(0), V def_value = V(0)) : nm(n), vl(n) { }

	void add(const N& name, const V& value)
	{
		nm.push_back(name);
		vl.push_back(value);
	}
	N& name(const V&);
	V& value(const N&);
	const N& name(const V& val) const { return name(val); }
	const V& value(const N& nam)const { return value(nam); }
};

int main()
{
	Pair<string, char> calc_tab{{ "quit", "#", "const", "help", "log", "from", "to" }, 
								{ 'Q', 'L', 'c', 'H', 'l', 'r', 'w' }, "none"};
	cout << calc_tab.name('Q') << " = " << calc_tab.value("quit") << '\n'
		 << calc_tab.name('H') << " = " << calc_tab.value("help") << '\n';

	return 0;
}

template<typename N, typename V>
N& Pair<N, V>::name(const V& val)
{
	for (int i{0}; i < vl.size(); ++i)
		if (val == vl.at(i)) 
			{ return nm.at(i); }
	return void_nm;
}

template<typename N, typename V>
V& Pair<N, V>::value(const N& nam)
{
	for (int i{0}; i < nm.size(); ++i)
		if (nam == nm.at(i))
			{ return vl.at(i); }
	return void_vl;
}