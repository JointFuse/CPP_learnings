#include "temperature.h"

ostream& operator<< (ostream& os, const Reading& r)
{
	return os << r.hour << ' ' << r.scale << r.temperature;
}

void store_temps(const vector<Reading>& data, const string& file_name)
{
	ofstream ost(file_name);
	if (!ost) error("Unable to open file -> ", file_name);

	for (const Reading& r : data) ost << r << '\n';
}