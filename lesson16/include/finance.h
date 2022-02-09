#ifndef Finance_h
#define	Finance_h

#include <vector>
#include <string>
#include <stdexcept>

namespace Finance {
	using namespace std;

	struct convert_error : runtime_error {
		convert_error(const string& what) : runtime_error(what) { }
	};

	class Money_converter {
		vector<vector<string>> Names;	// Store [ Name, Pair1, ..., Pairn ]
		vector<vector<double>> Pairs;	// Store [ 1, X1, ..., Xn ], where Xn = Name / Pairn
		bool override_ratio{ false };	// Rewrite repetitive courses when adding pair if true
	public:
		// Adding functions
		void add_name(const string& name);
		void add_pair(const string& name, const string& pair, double ratio);

		// Using function
		double convert(const string& name, const string& pair, double sum);

		void override_on() { override_ratio = true; }
		void override_off(){ override_ratio = false; }
		bool is_override() { return override_ratio; }
	};

	istream& operator>> (istream&, Money_converter&);
}

#endif // !Finance_h
