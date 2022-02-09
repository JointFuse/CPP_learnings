#include "temperature.h"

istream& operator>> (istream& is, Reading& obj)
{
	is >> obj.hour;

	char ch;
	is >> ch;
	if (ch != 'c' && ch != 'f') { is.unget(); is.clear(ios_base::failbit); return is; }
	obj.scale = ch;

	is >> obj.temperature;

	return is;
}

string temp_stats(const string& file_name)
{
	ifstream ist(file_name);
	if (!ist) error("Unable to open file -> ", file_name);

	vector<double> temps;
	double summ{ 0 };
	for (Reading r; ist >> r;) {
		if (r.scale == 'f') 
			r.temperature = (r.temperature - 32) * 5 * 1.0 / 9;
		temps.push_back(r.temperature);
		summ += r.temperature;
	}

	sort(temps.begin(), temps.end());

	ostringstream stats;
	stats << "Average: " << summ / temps.size() 
		  << "\nMedian: " << (temps[0] - temps[temps.size() - 1]) / 2;

	return stats.str();
}