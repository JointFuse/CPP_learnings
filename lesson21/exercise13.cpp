#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "Text.h"

using namespace std;

int main()
try{
	/*
	Text_lib::load_singles();
	Text_lib::make_dictionary("shorts");
	Text_lib::make_dictionary("letter");
	Text_lib::make_dictionary("big_text");
	Text_lib::store_singles();
	*/

	cout << "Total 'myth' in big_text = " << Text_lib::count_word("big_text" + Text_lib::file_predicate, "myth") << '\n';
	cout << "Total 'you' in big_text = " << Text_lib::count_word("big_text" + Text_lib::file_predicate, "you") << '\n';
	cout << "Most counted word in big_text: " << Text_lib::most_counted_word("big_text" + Text_lib::file_predicate) << '\n';
	cout << "Most counted word in letter: " << Text_lib::most_counted_word("letter" + Text_lib::file_predicate) << '\n';
	cout << "Longest word in big_text: " << Text_lib::longest_word("big_text" + Text_lib::file_predicate) << '\n';
	cout << "Longest word in letter: " << Text_lib::longest_word("letter" + Text_lib::file_predicate) << '\n';
	cout << "Shortest word in big_text: " << Text_lib::shortest_word("big_text" + Text_lib::file_predicate) << '\n';
	cout << "Shortest word in letter: " << Text_lib::shortest_word("letter" + Text_lib::file_predicate) << '\n';

	const string _pred_{ "comp" };
	cout << "All words starting by '" << _pred_ << "' from big_text: {" << '\n';
	vector<string> _pred {Text_lib::all_starting_by("big_text" + Text_lib::file_predicate, _pred_)};
	sort(_pred.begin(), _pred.end());
	auto p_pred = unique(_pred.begin(), _pred.end());
	for_each(_pred.begin(), p_pred,
			 [](const string& s)
			 { cout << '\t' << s << '\n'; });
	cout << "};\n";

	const int _length_{ 12 };
	cout << "All words that length equal to " << _length_ << " from big_text: {" << '\n';
	vector<string> _length {Text_lib::all_by_length("big_text" + Text_lib::file_predicate, _length_)};
	sort(_length.begin(), _length.end());
	auto p_len = unique(_length.begin(), _length.end());
	for_each(_length.begin(), p_len,
			 [](const string& s)
			 { cout << '\t' << s << '\n'; });
	cout << "};\n";

	return 0;
}
catch (runtime_error& err) {
	cerr << "Runtime error: " << err.what() << endl;
	return 1;
}
catch (exception& e) {
	cerr << "Exception: " << e.what() << endl;
	return 2;
}