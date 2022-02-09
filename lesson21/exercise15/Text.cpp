#include "Text.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <map>

using namespace Text_lib;

//------------------------------------------------------------------------------------

struct longest {
	string get{ "" };
	void operator() (const string& s)
	{ if (get.size() < s.size()) { get = s; } }
};

struct shortest {
	string get{ "" };
	void operator() (const string& s)
	{ if (get.size() == 0 || get.size() > s.size()) { get = s; } }
};

//------------------------------------------------------------------------------------

string Simplificator::operator() (string word) {
	if (word.size() == 0) { return ""; }

	for (auto p = word.begin(); p != word.end(); ++p) {
		if (*p < -1 || 255 < *p) { throw runtime_error("only Roman alphabet supported"); }
		if (isupper(*p)) { lowator(p, word.end()); break; }
	}

	for (auto p = word.begin(); p != word.end(); ++p) {
		if (*p == '\'') { shortuator(word, p); }
		if (ispunct(*p)) { punctuator(p, word.end()); }
	}

	auto a = word.begin();
	auto b = word.begin();
	while (a != word.end()) {
		while (b != word.end() && *b != ' ') 
			{ ++b; }
		singulator(a, b);
		if (b != word.end())
			{ ++b; }
		a = b;
	}

	return word;
}

//------------------------------------------------------------------------------------

void Simplificator::addsingle(string::iterator b, string::iterator e)
{
	string word{ b, e };
	singles.insert(word);
}

//------------------------------------------------------------------------------------

bool Simplificator::issingle(string::iterator b, string::iterator e)
{
	string word{b, e};
	if (singles.find(word) != singles.end())
		{ return true; }
	return false;
}

//------------------------------------------------------------------------------------

void Simplificator::lowator(string::iterator b, string::iterator e)
{
	while (b != e) {
		*b = tolower(*b);
		++b;
	}
}

//------------------------------------------------------------------------------------

void Simplificator::punctuator(string::iterator b, string::iterator e)
{
	while (b != e) {
		if (ispunct(*b))
			{ *b = ' '; }
		++b;
	}
}

//------------------------------------------------------------------------------------

void Simplificator::shortuator(string& word, string::iterator p)
{
	if (word.size() < 3 || p == word.begin() ||
		p == word.end() || p + 1 == word.end())
		{ return; }

	string pred{ "" };

	if (*(p - 1) == 'n' && *(p + 1) == 't') {
		if (2 < p - word.begin() && *(p - 3) == 'c' && *(p - 2) == 'a')
			{ pred = "no"; }
		else if (2 < p - word.begin() && *(p - 3) == 'w' && *(p - 2) == 'o')
			{ pred = "l no"; *(p - 1) = 'l'; *(p - 2) = 'i'; }
		else if (3 < p - word.begin() && *(p - 4) == 's' && *(p - 3) == 'h' && *(p - 2) == 'a')
			{ pred = "l no"; *(p - 1) = 'l'; *(p - 2) = 'a'; }
		else 
			{ pred = "no"; *(p - 1) = ' '; }
	}

	if (word.end() - p == 3) {
		if (*(p + 1) == 'l' && *(p + 2) == 'l') 
			{ pred = " wi"; }
		if (*(p + 1) == 'v' && *(p + 2) == 'e')
			{ pred = " ha"; }
		if (*(p + 1) == 'r' && *(p + 2) == 'e')
			{ pred = " a"; }
	}

	if (word.end() - p == 2) {
		if (*(p + 1) == 'm')
			{ pred = " a"; }
		if (*(p + 1) == 'd')
			{ pred = " ha"; }
		if (*(p + 1) == 's')
			{ pred = " i"; }
	}

	for (int i{ 1 }; i < pred.size(); ++i)
		{ p = word.insert(p, ' '); }
	for (char ch : pred)
		{ *p = ch; ++p; }
}

//------------------------------------------------------------------------------------

void Simplificator::singulator(string::iterator b, string::iterator e)
{
	if (e - b < 3)
		{ return; }

	if (issingle(b, e - 1)) {
		*(e - 1) = ' ';
		return;
	}

	if (*(e - 2) == 'e' && *(e - 1) == 's' && 
		(*(e - 3) == 'o' || *(e - 3) == 's' || *(e - 3) == 'x' || *(e - 3) == 'v'|| *(e - 3) == 'i' ||
		((e - b > 3) && *(e - 3) == 'h' && (*(e - 4) == 's' || *(e - 4) == 'c')))) {

		if (*(e - 3) == 'v')
			{ *(e - 3) = 'f'; }
		if (*(e - 3) == 'i')
			{ *(e - 3) = 'y'; }

		*(e - 2) = ' ';
		*(e - 1) = ' ';
		e = e - 2;
	}

	addsingle(b, e);
}

//------------------------------------------------------------------------------------

bool Text_lib::load_singles()
{
	ifstream dict{ sing_file };
	if (!dict) { return false; }

	for (auto p = istream_iterator<string>{dict};
		 p != istream_iterator<string>{}; ++p)
		{ singles.insert(*p); }

	return true;
}

//------------------------------------------------------------------------------------

bool Text_lib::store_singles(bool add)
{
	ofstream dict{ sing_file, add ? ios_base::app : ios_base::ate };
	if (!dict) { return false; }

	for (const string& s : singles) {
		auto p = singles.find(s + "s");
		if (p != singles.end())
			{ singles.erase(p); }
	}

	copy(singles.begin(), singles.end(),
		 ostream_iterator<string>{dict, "\n"});

	return true;
}

//------------------------------------------------------------------------------------

void Text_lib::make_dictionary(string file_name)
{
	ifstream orig{file_name + file_format};
	ofstream result{file_name + file_predicate + file_format};
	if (!orig)	
		{ throw runtime_error("can't open [" + 
							  file_name + file_format + "] to read"); }
	if (!result)
		{ throw runtime_error("can't open [" + 
							  file_name + file_predicate + file_format + "] to write"); }

	transform(istream_iterator<string>{orig},
			  istream_iterator<string>{},
			  ostream_iterator<string>{result, "\n"},
			  Simplificator());
}

//------------------------------------------------------------------------------------

int Text_lib::count_word(string file_name, string word)
{
	ifstream file{file_name + file_format};
	if (!file) { throw runtime_error("can't open [" +
									 file_name + file_format + "] to read"); }

	return count_if(istream_iterator<string>{file},
					istream_iterator<string>{},
					[&](const string& s)
					{ return s == word; });
}

//------------------------------------------------------------------------------------

string Text_lib::most_counted_word(string file_name)
{
	ifstream file{ file_name + file_format };
	if (!file) { throw runtime_error("can't open [" +
									 file_name + file_format + "] to read"); }

	map<string, int> cnt;
	for (auto p = istream_iterator<string>{file};
		 p != istream_iterator<string>{}; ++p)
		 { ++cnt[*p]; }

	if (cnt.begin() == cnt.end())
		{ throw runtime_error("file empty"); }

	auto high = cnt.begin();
	for (auto p = high; p != cnt.end(); ++p)
		if (high->second < p->second)
			{ high = p; }

	return high->first;
}

//------------------------------------------------------------------------------------

string Text_lib::longest_word(string file_name)
{
	ifstream file{ file_name + file_format };
	if (!file) { throw runtime_error("can't open [" +
									 file_name + file_format + "] to read"); }
	
	longest word = for_each(istream_iterator<string>{ file },
							istream_iterator<string>{}, 
							longest());

	return word.get;
}

//------------------------------------------------------------------------------------

string Text_lib::shortest_word(string file_name)
{
	ifstream file{ file_name + file_format };
	if (!file) { throw runtime_error("can't open [" +
									 file_name + file_format + "] to read"); }

	shortest word = for_each(istream_iterator<string>{ file },
							 istream_iterator<string>{},
							 shortest());

	return word.get;
}

//------------------------------------------------------------------------------------

vector<string> Text_lib::all_starting_by(string file_name, string begining)
{
	ifstream file{ file_name + file_format };
	if (!file) { throw runtime_error("can't open [" +
									 file_name + file_format + "] to read"); }

	vector<string> ret;
	copy_if(istream_iterator<string>{ file },
			istream_iterator<string>{},
			back_inserter(ret),
			[&](const string& s)
			{
				for (int i{0}; i < begining.size(); ++i)
					if (s.size() <= i || begining[i] != s[i])
					{ return false; }
				return true;
			});

	return ret;
}

//------------------------------------------------------------------------------------

vector<string> Text_lib::all_by_length(string file_name, int length)
{
	ifstream file{ file_name + file_format };
	if (!file) { throw runtime_error("can't open [" +
									 file_name + file_format + "] to read"); }

	vector<string> ret;
	copy_if(istream_iterator<string>{ file },
			istream_iterator<string>{},
			back_inserter(ret),
			[&](const string& s)
			{
				if (s.size() == length)
					{ return true; }
				return false;
			});

	return ret;
}

//------------------------------------------------------------------------------------
