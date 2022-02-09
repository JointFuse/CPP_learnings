#ifndef Text_h
#define Text_h

#include <string>
#include <vector>
#include <set>

namespace Text_lib {
	using namespace std;

	const string sing_file{ "singles_dictionary" };
	const string file_predicate{ "_dictionaried" };
	const string file_format{ ".txt" };
	static set<string> singles;

	class Simplificator {
		void addsingle(string::iterator b, string::iterator e);
		bool issingle(string::iterator b, string::iterator e);

		void lowator(string::iterator b, string::iterator e);
		void punctuator(string::iterator b, string::iterator e);
		void shortuator(string& word, string::iterator p);
		void singulator(string::iterator b, string::iterator e);
	public:
		string operator() (string word);
	};

	extern bool load_singles();
	extern bool store_singles(bool add = false);

	extern int count_word(string file_name, string word);
	extern string most_counted_word(string file_name);
	extern string longest_word(string file_name);
	extern string shortest_word(string file_name);
	extern vector<string> all_starting_by(string file_name, string begining);
	extern vector<string> all_by_length(string file_name, int length);

	extern void make_dictionary(string file_name);
}
#endif // !Text_h
