#include </Users/tony/source/repos/libs/std_lib_facilities.h>

struct Reading {
	Reading() :hour{ 0 }, temperature{ 22.8 }, scale{ 'c' } { }
	int hour;
	double temperature;
	char scale;
};

void store_temps(const vector<Reading>& data, const string& file_name);
string temp_stats(const string& file_name);

ostream& operator<< (ostream&, const Reading&);
istream& operator>> (istream&, const Reading&);