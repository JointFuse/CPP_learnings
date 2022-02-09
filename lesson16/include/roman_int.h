#include <std_lib_facilities.h>

class Roman_int {
	int num;
public:
	Roman_int() :num{ 0 } { }
	Roman_int(int x);

	void set(int nn) { num = nn; }
	int as_int() const { return num; }
	string as_string() const;
};

bool is_roman(const int&);

ostream& operator<< (ostream&, const Roman_int&);
istream& operator>> (istream&, Roman_int&);