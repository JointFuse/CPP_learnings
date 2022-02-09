#include "my_points.h"

using namespace Geometry;
using namespace Filesystem;

const int POINT_QUANT{ 7 };
const string MANUAL_FILL{ "manual" };

bool Geometry::Point::operator!= (const Point& p2)
{
	return x != p2.x || y != p2.y;
}

istream& Geometry::operator>> (istream& is, Point& p)
{
	char ch1, ch2;
	int x, y;

	is >> ch1;
	if (ch1 != '[') { is.unget(); is.clear(ios_base::failbit); return is; }
		
	is >> x >> ch1 >> y >> ch2;
	if (ch1 != ',' || ch2 != ']') { is.clear(ios_base::badbit); return is; }
	
	p.x = x;
	p.y = y;

	return is;
}

ostream& Geometry::operator<< (ostream& os, const Point& p)
{
	return os << "[ " << p.x << ", " << p.y << " ]";
}

void Filesystem::read_points(vector<Point>& points)
{
	cout << "\nPlease, write name of file or [manual] to fill points by yourself\n";

	string file_name;
	cin >> file_name;
	
	if (file_name == MANUAL_FILL) { fill_vpoint(points, POINT_QUANT); return; }

	fill_vpoint(points, file_name);
}

void Filesystem::write_points(vector<Point>& points)
{
	cout << "\nPlease, write name of file to store points\n";

	string file_name;
	cin >> file_name;

	fill_to_file(points, file_name);
}

void Filesystem::fill_vpoint(vector<Point>& points, const string& file_name)
{
	ifstream ist(file_name);
	if (!ist) error("Unable to open file -> ", file_name);

	for (Point p; ist >> p; ) points.push_back(p);
}

void Filesystem::fill_vpoint(vector<Point>& points, const int& quantity)
{
	cout << "Please, write " << POINT_QUANT << " points [ x, y ]\n";
	
	Point p;

	for (int i{ 0 }; i < POINT_QUANT; ++i) {
		cout << i + 1 << "'st point: ";
		cin >> p;
		points.push_back(p);
	}
}

void Filesystem::fill_to_file(vector<Point>& points, const string& file_name)
{
	ofstream ost(file_name);
	if (!ost) error("Unable to open file -> ", file_name);

	for (Point p : points) ost << ' ' << p;
	ost << endl;
}