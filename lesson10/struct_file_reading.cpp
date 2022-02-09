#include "struct_file_reading.h"

const vector<string> month_input_tbl = {
	"jan", "feb", "mar", "apr", "may", "jun",
	"jul", "aug", "sep", "oct", "nov", "dec"
};

const vector<string> month_print_tbl = {
	"January", "February", "March", "April",
	"May", "June", "July", "August", "September",
	"October", "November", "December"
};

istream& operator>> (istream& is, Reading& r)
{
	char ch1;
	if (is >> ch1 && ch1 != '(') {
		is.unget();
		is.clear(ios_base::failbit);
		return is;
	}

	char ch2;
	int d;
	int h;
	double t;
	is >> d >> h >> t >> ch2;
	if (!is || ch2 != ')')
		error("Bad writing down");

	r.day = d;
	r.hour = h;
	r.temp = t;

	return is;
}

istream& operator>> (istream& is, Month& m)
{
	char ch = 0;
	if (is >> ch && ch != '{') {
		is.unget();
		is.clear(ios_base::failbit);
		return is;
	}

	string month_marker;
	string mm;
	is >> month_marker >> mm;
	if (!is || month_marker != "month")
		error("Wrong begin of month");
	m.month = month_to_int(mm);

	Reading r;
	int duplicates{ 0 };
	int invalids{ 0 };
	for (Reading r; is >> r; ) {
		if (is_valid(r)) {
			if (m.day[r.day].hour[r.hour] != not_a_reading)
				++duplicates;
			m.day[r.day].hour[r.hour] = r.temp;
		}
		else ++invalids;
	}

	if (invalids) error("Invalid data in Month, quantity: ", invalids);
	if (duplicates) error("Duplicate data in Month, quantity: ", duplicates);
	end_of_loop(is, '}', "Wrong ending of Month");
	return is;
}

istream& operator>> (istream& is, Year& y)
{
	char ch;
	is >> ch;
	if (ch != '{') {
		is.unget();
		is.clear(ios_base::failbit);
		return is;
	}

	string year_marker;
	int yy;
	is >> year_marker >> yy;
	if (!is || year_marker != "year")
		error("Wrong begin of Year");
	y.year = yy;
	while (true) {
		Month m;
		if (!(is >> m)) break;
		y.month[m.month] = m;
	}

	end_of_loop(is, '}', "Wrong ending of Year");
	return is;
}

bool is_valid(const Reading& r)
{
	if (r.day < 1 || 31 < r.day) return false;
	if (r.hour < 0 || 23 < r.hour) return false;
	if (r.temp < implausible_min ||
		implausible_max < r.temp)
		return false;
	return true;
}

int month_to_int(string m)
{
	for (int i{ 0 }; i < 12; ++i)if (month_input_tbl[i] == m) return i;
	return not_a_month;
}

string int_to_month(int m)
{
	if (m < 0 || 12 < m)error("Wrong month index");
	return month_print_tbl[m];
}

void end_of_loop(istream& ist, char term, const string& message)
{
	if (ist.fail()) {
		ist.clear();
		char ch;
		if (ist >> ch && ch == term)return;
		error(message);
	}
}

void print_year(ostream& os, const Year& y)
{
	os << "{ year " << y.year;
	for (Month m : y.month)
		if (m.month != not_a_month) {
			os << " { month " << int_to_month(m.month);
			for (int i{ 0 }; i < 32; ++i)
				for (int j{ 0 }; j < 24; ++j)
					if (m.day[i].hour[j] != not_a_reading)
						os << "( " << i << ' ' << j << ' ' 
							 << m.day[i].hour[j] << " )";
			os << " }";
		}
	os << " }";
}