#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template<typename T>
istream& operator>> (istream& is, vector<T>& v)
{
	for (T buf; is >> buf; )
		{ v.push_back(buf); }
	return is;
}

template<typename T>
ostream& operator<< (ostream& os, const vector<T>& v)
{
	os << "{ ";
	for (T& i : v)
		{ os << i << (&i == &v[v.size() - 1] ? " }" : ", "); }

	return os;
}

double* get_from_jack(int* count)
{
	ifstream in{"jack_data.txt"};
	if (!in) { throw exception("can't open jack file"); }
	vector<double>* data = new vector<double>;
	in >> *data;
	*count = data->size();
	return &(*data)[0];
}

vector<double>* get_from_jill()
{
	ifstream in{ "jill_data.txt" };
	if (!in) { throw exception("can't open jill file"); }
	vector<double>* data = new vector<double>;
	in >> *data;
	return data;
}

template<typename Iterator>
Iterator highit(Iterator first, Iterator last)
{
	Iterator high = first;
	for (Iterator p = first; p != last; ++p)
		if (*high < *p) { high = p; }
	return high;
}

double* high(double* first, double* last)
{
	double h = -1;
	double* high{nullptr};
	for (double* p = first; p != last; ++p)
		if (h < *p) {
			high = p;
			h = *p;
		}
	return high; 
}

double* high1(double* first, double* last)
{
	if (first == last) { return last; }
	--last;
	double* high{first};
	while (first <= last) {
		double* higher = *first < *last ? last : first;
		if (*high < *higher)
			{ high = higher; }
		++first;
		--last;
	}
	return high;
}

double* high2(double* first, double* last)
{
	if (first == last) { return last; }
	double* high{ *first < *last ? last : first };
	if (first <= last) {
		double* next = high2(++first, --last);
		if (*high < *next) { high = next; }
	}
	return high;
}

int main()
try {
	int jack_count{0};
	double* jack_data = get_from_jack(&jack_count);
	vector<double>* jill_data = get_from_jill();
	vector<double>& v = *jill_data;
	double* jack_high = highit(jack_data, jack_data + jack_count);
	auto jill_high = highit(v.begin(), v.end());
	cout << "Jack maximum = " << *jack_high
		 << "; Jill maximum = " << *jill_high
		 << "\nJill data: " << *jill_data << endl;

	delete[] jack_data;
	delete jill_data;
	return 0;
}
catch (exception& e) {
	cout << "Exception: " << e.what() << endl;
}