#include "finance.h"
#include <iostream>

//------------------------------------------------------------------

using namespace Finance;

//------------------------------------------------------------------

void Money_converter::add_name(const string& name)
{
	for(auto i : Names)
		if(i[0] == name)
			return;

	vector<string> new_name;
	vector<double> new_pair;
	Names.push_back(new_name);
	Pairs.push_back(new_pair);
	Names[Names.size() - 1].push_back(name);
	Pairs[Pairs.size() - 1].push_back(1);
}

//------------------------------------------------------------------

void Money_converter::add_pair(const string& name, const string& pair, double ratio)
{
	for (int i{0}; i < Names.size(); ++i)
		if (Names[i][0] == name) {

			for(int j{1}; j < Names[i].size(); ++j)
				if (Names[i][j] == pair) {
					if (override_ratio) {
						Pairs[i][j] = ratio;
						return;
					}
					else return;
				}

			Names[i].push_back(pair);
			Pairs[i].push_back(ratio);

			return;
		}

	add_name(name);
	add_pair(name, pair, ratio);
}

//------------------------------------------------------------------

double Money_converter::convert(const string& name, const string& pair, double sum)
{
	bool has_name{ false };

	for (int i{0}; i < Names.size(); ++i)
		if (Names[i][0] == name) {
			for (int j{ 0 }; j < Names[i].size(); ++j) {
				if (Names[i][j] == pair)
					return sum * Pairs[i][j];
			}

			has_name = true;
		}
	
	if(has_name) throw convert_error(name + " hasn't pair with " + pair);
	throw convert_error("no such currency as " + name);
}

//------------------------------------------------------------------

istream& Finance::operator>> (istream& is, Money_converter& conv)
{
	char ch1, ch2;
	vector<char> names(6);
	double ratio;

	is >> ch1;

	if (is.eof()) return is;

	for (int i{ 0 }; i < 6; ++i)
		is >> names[i];

	for(auto ch : names)
		if (islower(ch) || !isalpha(ch)) {
			is.clear(ios_base::failbit);
			return is;
		}

	is >> ch2;
	if (!isdigit(ch2)) {
		is.clear(ios_base::failbit);
		return is;
	}

	is.unget();
	is >> ratio >> ch2;
	if (ch1 != '(' || ch2 != ')') {
		is.clear(ios_base::failbit);
		return is;
	}

	string cur1, cur2;
	for (int i{ 0 }; i < 3; ++i) {
		cur1.push_back(names[i]);
		cur2.push_back(names[i + 3]);
	}

	conv.add_pair(cur1, cur2, ratio);
	return is;
}

//------------------------------------------------------------------
