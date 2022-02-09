#include "std_lib_facilities.h"

class Name_pairs {
private:
	vector<string> name;
	vector<double> age;
public:
	void read_names();
	void read_ages();

	void print();
	void sort();

	string get_name(int i)	const { return name[i]; }
	double get_age(int i)	const { return age[i]; }

	int get_size()			const;
};

ostream& operator<< (ostream&, const Name_pairs&);
bool operator== (const Name_pairs&, const Name_pairs&);
bool operator!= (const Name_pairs&, const Name_pairs&);