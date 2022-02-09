#include <map>
#include <iostream>
#include <string>
#include <numeric>

using namespace std;

template<typename Elem1, typename Elem2>
istream& operator>> (istream& is, pair<Elem1, Elem2>& p)
{
	char ch;
	is >> ch;
	if (ch != ':') {
		is.unget();
		is.clear(ios_base::failbit);
		return is;
	}
	is >> p.first >> p.second;
	return is;
}

template<typename Elem1, typename Elem2>
ostream& operator<< (ostream& os, const pair<const Elem1, Elem2>& p)
{
	return os << "Key: [" << p.first << "]; Value: [" << p.second << "].";
}

int main()
{
	map<string, int> msi;
	msi["lecture"] = 21;
	msi["bool"] = 1010;
	msi["apple"] = 100;
	msi["tree"] = 98;
	msi["rainbow"] = 76;
	msi["clean"] = 117;
	msi["rule"] = 77;
	msi["fair"] = 1;
	msi["plumbum"] = 96;
	msi["inyan"] = 69;
	
	for (auto p = msi.begin(); p != msi.end(); ++p)
		{ cout << *p << '\n'; }

	msi.clear();
	cout << "(msi) size = [" << msi.size() << "]\n";

	for (pair<string, int> p; cin >> p; )
		{ msi[p.first] = p.second; }
	for (auto p = msi.begin(); p != msi.end(); ++p)
		{ cout << *p << '\n'; }

	cout << "map.value summ = " << accumulate(msi.begin(), msi.end(), 0, 
											  [](int v, const pair<string, int>& p) 
											  { return v + p.second; }) << '\n';
	
	map<int, string> mis;
	
	for (auto p = msi.begin(); p != msi.end(); ++p)
		{ mis[p->second] = p->first; }
	for (auto p = mis.begin(); p != mis.end(); ++p)
		{ cout << *p << '\n'; }

	return 0;
}