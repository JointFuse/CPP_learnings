#include "roman_int.h"

const vector<string> n0 = {
	"", "I", "II", "III", "IV",
	"V", "VI", "VII", "VIII", "IX"
};

const vector<string> n1 = {
	"", "X", "XX", "XXX", "XL",
	"L", "LX", "LXX", "LXXX", "XC"
};

const vector<string> n2 = {
	"", "C", "CC", "CCC", "CD",
	"D", "DC", "DCC", "DCCC", "CM"
};

const vector<string> n3 = {
	"", "M", "MM", "MMM"
};

Roman_int::Roman_int(int x) 
	:num{ x } 
{ 
	if (!is_roman(num)) error("out of range"); 
}

string Roman_int::as_string() const
{
	ostringstream roman;
	if (!is_roman(num)) roman << num;

	int buf{ num / 1000 };
	roman << n3[buf];
	buf = (num - num / 1000 * 1000) / 100;
	roman << n2[buf];
	buf = (num - num / 100 * 100) / 10;
	roman << n1[buf];
	buf = num - num / 10 * 10;
	roman << n0[buf];

	return roman.str();
}

int roman_digger(const vector<string> v, const string& roman)
{
	for (int i{ 0 }; i < v.size(); ++i)
		if (v[i] == roman) return i;
	return 9999;
}

bool is_roman(const int& num)
{
	if (num < 1 || 3999 < num)
		return false;
	return true;
}

ostream& operator<< (ostream& os, const Roman_int& roman)
{
	return os << roman.as_string();
}

istream& operator>> (istream& is, Roman_int& roman)
{
	int buf{ 0 };
	char ch;
	string s{ "" };
	is >> ch;
	while (ch == 'M' && ch != '.') {
		s += ch;
		is >> ch;
		if (s.size() == 3) break;
	}
	buf += roman_digger(n3, s) * 1000;
	s.clear();

	while (ch == 'C' || ch == 'D' || ch == 'M' 
			&& ch != '.') {
		s += ch;
		is >> ch;
		if (s.size() == 4) break;
	}
	buf += roman_digger(n2, s) * 100;
	s.clear();

	while (ch == 'X' || ch == 'L' || ch == 'C' 
			&& ch != '.') {
		s += ch;
		is >> ch;
		if (s.size() == 4) break;
	}
	buf += roman_digger(n1, s) * 10;
	s.clear();

	while (ch == 'I' || ch == 'V' || ch == 'X' 
			&& ch != '.') {
		s += ch;
		is >> ch;
		if (s.size() == 4) break;
	}
	buf += roman_digger(n0, s);
	is.unget();

	if (!is_roman(buf)) { is.clear(ios_base::failbit); return is; }
	roman.set(buf);

	return is;
}