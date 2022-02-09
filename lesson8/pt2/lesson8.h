#include "std_lib_facilities.h"

namespace NAS {
	void main();
}

namespace PWS {
	extern vector<double> weight;
	extern vector<double> price;

	double sum(const vector<double>&, const vector<double>&);
}

namespace Math {
	struct result {
		int max{ 0 };
		int min{ 0 };
		int mean{ 0 };
		int median{ 0 };
	};

	int maxv(const vector<int>&);
	result fourm(const vector<int>&);
}

extern vector<int> my_vector;
extern vector<string> my_string;

void print(ostream&, vector<int>&);
void print_str(ostream&, const vector<string>&);

void swap_clear(vector<int>&);
void swap_clear_str(vector<string>&);

vector<int> swap_create(const vector<int>&);
vector<string> swap_create_str(const vector<string>&);

void print_until_s(const vector<string>&, const string&);
void print_until_ss(const vector<string>&, const string&);

vector<int> string_analize(vector<string>&);

void f(const int);