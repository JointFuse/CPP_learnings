#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
//#include <algorithm>

using namespace std;

struct Item {
	string name;
	int iid;
	double value;
	/* ... */
};

struct case_name {
	bool operator() (const Item& x, const Item& y) const
	{
		return x.name < y.name;
	}
};

struct case_iid {
	bool operator() (const Item& x, const Item& y) const
	{
		return x.iid < y.iid;
	}
};

struct case_value {
	bool operator() (const Item& x, const Item& y) const
	{
		return x.value < y.value;
	}
};

istream& operator>> (istream& is, Item& item)
{
	char ch1, ch2, ch3, ch4;
	string name;
	int iid;
	double value;
	is >> ch1 >> name >> ch2 >> iid >> ch3 >> value >> ch4;
	if (ch1 != '{' || ch2 != ',' || ch3 != ',' || ch4 != '}') 
		{ is.clear(ios_base::failbit); return is; }
	item.name = name;
	item.iid = iid;
	item.value = value;
	return is;
}

ostream& operator<< (ostream& os, const Item& item)
{
	return os << "{ " << item.name << ", " << item.iid << ", "
			  << ", " << item.value << " }";
}

template<typename Iter, typename Compare>
void sort(typename Iter b, typename Iter e, Compare comp)
{
	auto ee = e;
	--ee;
	for (auto checked = b; checked != e; ++checked) {
		auto* chosen = &*checked;
		for (auto verifiable = ee; verifiable != checked; --verifiable)
			if (!comp(*chosen, *verifiable)) 
				{ chosen = &*verifiable; }
		if (&*checked != chosen) {
			auto buf = *checked;
			*checked = *chosen;
			*chosen = buf;
		}
	}
}

template<typename Container, typename Elem = Item>
int vector_task()
{
	ifstream file{ "task_dat.txt" };
	if (!file) { cout << "Unable to open file!" << endl; return 1; }

	istream_iterator<Elem> fbegin{ file };
	istream_iterator<Elem> eos;
	ostream_iterator<Elem> outstream{ cout, "\n" };

	Container v{ fbegin, eos };

	cout << "\t [ SORTED BY NAME ]\n";
	sort(v.begin(), v.end(), case_name());
	copy(v.begin(), v.end(), outstream);

	cout << "\t [ SORTED BY IID ]\n";
	sort(v.begin(), v.end(), case_iid());
	copy(v.begin(), v.end(), outstream);

	cout << "\t [ SORTED BY VALUE ]\n";
	sort(v.begin(), v.end(), case_value());
	for (auto p = --v.end(); true; --p) {
		cout << *p << '\n';
		if (p == v.begin())
			{ break; }
	}

	v.push_back({ "horse shoe", 99, 12.34 });
	cout << "\t [ EDDED <horse shoe> ]\n";
	copy(v.begin(), v.end(), outstream);

	v.push_back({ "Canon S400", 9988, 499.95 });
	cout << "\t [ EDDED <Canon S400> ]\n";
	copy(v.begin(), v.end(), outstream);

	v.erase(find_if(v.begin(), v.end(), [](Item x) {return x.name == "lastname"; }));
	cout << "\t [ DELETED BY NAME <lastname> ]\n";
	copy(v.begin(), v.end(), outstream);

	v.erase(find_if(v.begin(), v.end(), [](Item x) {return x.iid == 123456; }));
	cout << "\t [ DELETED BY IID <123456> ]\n";
	copy(v.begin(), v.end(), outstream);

	return 0;
}

int main()
{
	return vector_task<list<Item>>();
}