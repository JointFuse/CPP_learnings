#include </Users/tony/source/repos/libs/std_lib_facilities.h>

namespace Geometry {

	/*--Some-helpfull-functions-and-data-structures---------------------------------*/

	struct Point {
		Point() :x{ 0 }, y{ 0 } {}
		
		int x;
		int y;
		
		bool operator!= (const Point&);
	};

	istream& operator>> (istream&, Point&);
	ostream& operator<< (ostream&, const Point&);
}

namespace Filesystem {

	/*--Functions-to-process-data-with-point-structure-------------------------------*/

	void read_points(vector<Geometry::Point>& points);
	void write_points(vector<Geometry::Point>& points);

	void fill_to_file(vector<Geometry::Point>& points, const string& file_name);
	void fill_vpoint(vector<Geometry::Point>& points, const string& file_name);
	void fill_vpoint(vector<Geometry::Point>& points, const int& quantity);
}