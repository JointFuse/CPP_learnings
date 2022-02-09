#include </Users/tony/source/repos/libs/std_lib_facilities.h>

const int not_a_reading{ -7777 };
const int not_a_month{ -1 };
constexpr int implausible_min{ -200 };
constexpr int implausible_max{ 200 };

struct Day {
	vector<double> hour{ vector<double>(24,not_a_reading) };
};

struct Month {
	int month{ not_a_month };
	vector<Day> day{ 32 };
};

struct Year {
	int year;
	vector<Month> month{ 12 };
};

struct Reading {
	int day;
	int hour;
	double temp;
};

istream& operator>> (istream&, Reading&);
istream& operator>> (istream&, Month&);
istream& operator>> (istream&, Year&);

bool is_valid(const Reading&);
int month_to_int(string);
string int_to_month(int);
void end_of_loop(istream&, char, const string&);
void print_year(ostream&, const Year&);
