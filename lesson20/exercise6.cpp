#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <exception>

using namespace std;
using Line = vector<char>;

extern class Document;
extern class Text_iterator;
extern int line(Document& d, Text_iterator curr);
extern int column(const Line& l, Text_iterator curr);
extern bool isbelong(const string& s, char ch);

//-----------------------------------------------------------------------

class Text_iterator {
	list<Line>::iterator ln;
	Line::iterator pos;
public:
	Text_iterator(list<Line>::iterator ll, Line::iterator pp)
		: ln{ll}, pos{pp} { }
	
	auto line() const { return ln; }
	auto column() const { return pos; }

	char& operator*() { return *pos; }
	Text_iterator& operator++();

	bool operator==(const Text_iterator& other) const
		{ return ln == other.ln && pos == other.pos; }
	bool operator!=(const Text_iterator& other) const
		{ return !(*this==other); }
};

Text_iterator& Text_iterator::operator++()
{
	++pos;
	if (pos == ln->end()) {
		++ln;
		pos = ln->begin();
	}
	return *this;
}

//-----------------------------------------------------------------------

struct Document {
	Document() { line.push_back(Line{}); }
	list<Line> line;

	Text_iterator begin()
	{
		return Text_iterator(line.begin(),
			(*line.begin()).begin());
	}
	Text_iterator end()
	{
		return Text_iterator(--line.end(),
			(--line.end())->end());
	}
};

//-----------------------------------------------------------------------

bool match(Text_iterator first, Text_iterator last, const string& s)
{
	for (char ch : s) {
		if (first == last || *first != ch)
			{ return false; }
		++first;
	}
	return true;
}

//-----------------------------------------------------------------------

Text_iterator Find(Text_iterator first, Text_iterator last, const char& ch)
{
	if (first == last) { return last; }
	while (first != last) {
		if (*first == ch)
			{ return first; }
		++first;
	}
	return last;
}

Text_iterator find_txt(Text_iterator first, Text_iterator last, const string& s)
{
	if (s.size() == 0) return last;
	char first_char = s[0];
	while (true) {
		auto p = Find(first, last, first_char);
		if (p==last || match(p, last, s)) { return p; }
		first = ++p;
	}
}

//-----------------------------------------------------------------------

Text_iterator find_replace(Text_iterator first, Text_iterator last, const string& orig, const string& s)
{
	if (orig.size() != s.size()) { return last; }
	first = find_txt(first, last, orig);
	if (first == last) { return last; }
	Text_iterator p = first;
	for (char ch : s) {
		*p = ch;
		++p;
	}
	return first;
}

void find_replace(Document& d, const string& orig, const string& s)
{
	if (orig == s) { return; }
	const Text_iterator first = d.begin();
	const Text_iterator last = d.end();
	
	for (Text_iterator pos{ find_txt(first, last, orig) }; pos != last; ) {
		auto line_iter = d.line.begin();
		const int line_index = line(d, pos);
		advance(line_iter, line_index);

		auto column_iter = line_iter->begin();
		const int column_index = column(*line_iter, pos);
		advance(column_iter, column_index);
		const int oversize = int(orig.size()) - int(s.size());

		for (int i{ 0 }; i < oversize; ++i) 
			{ line_iter->erase(column_iter + s.size()); }
		for (int i{ 0 }; oversize < i; --i) { 
			line_iter->insert(column_iter + orig.size(), '#');

			line_iter = d.line.begin();
			advance(line_iter, line_index);
			column_iter = line_iter->begin();
			advance(column_iter, column_index);
		}

		for (char ch : s) {
			*column_iter = ch;
			++column_iter;
		}
		pos = find_txt(first, last, orig);
	}
}

//-----------------------------------------------------------------------

void print(Document& d)
{
	for (auto p : d)
		{ cout << p; }
	cout << '\n';
}

/* Exercise 7 */
template<typename Iter>
Iter lastest(Iter begin, Iter end)
{
	Iter last = begin;
	while (begin != end) {
		if (*last < *begin)
		{
			last = begin;
		}
		++begin;
	}
	return last;
}

/* Exercise 8 */
int symblen(const Document& d)
{
	int size{ 0 };
	for (auto l : d.line)
	{
		size += l.size();
	}
	return size;
}

/* Exercise 8 */
int symblen(Text_iterator begin, Text_iterator end)
{
	int size{ 0 };
	while (begin != end)
	{
		++size; ++begin;
	}
	return size;
}

/* Exercise 9 */
int symb_wordsize(Text_iterator begin, Text_iterator end)
{
	int size{ 0 };
	while (true) {
		if (begin == end)
			{ return size; }

		char prev{ *begin };
		++begin;

		if (begin == end) {
			if (prev < -1 || prev != ' ')
				{ ++size; }
			return size;
		}

		if ((prev < -1 || prev != ' ') && *begin == ' ')
			{ ++size; }
	}
}

/* Exercise 9 */
int alpha_wordsize(Text_iterator begin, Text_iterator end)
{
	int size{ 0 };
	while (true) {
		if (begin == end)
			{ return size; }

		char prev{ *begin };
		++begin;

		if (begin == end) {
			if (prev < -1 || isalpha(prev))
				{ ++size; }
			return size;
		}

		if ((prev < -1 || isalpha(prev)) &&
			!(*begin < -1 || isalpha(*begin)))
			{ ++size; }
	}
}

/* Exercise 10 */
int user_wordsize(Text_iterator begin, Text_iterator end, const string& sep)
{
	int size{ 0 };
	while (true) {
		if (begin == end)
			{ return size; }

		char prev{ *begin };
		++begin;

		if (begin == end) {
			if (!isbelong(sep, prev))
				{ ++size; }
			return size;
		}

		if (!isbelong(sep, prev) && isbelong(sep, *begin))
			{ ++size; }
	}
}

//-----------------------------------------------------------------------

void erase_line(Document& d, int n)
{
	if (n<0 || d.line.size()-1<=n) return;
	auto p = d.line.begin();
	advance(p, n);
	d.line.erase(p);
}

void pushb_line(Document& d, const string& s)
{
	auto p = --d.line.end();
	for (char ch : s)
		{ p->push_back(ch); }
	d.line.push_back(Line{});
}

int line(Document& d, Text_iterator curr)
{
	auto p = d.line.begin();
	int pos{ 0 };
	while (p != curr.line())
		{ ++p; ++pos; }
	return pos;
}

int column(const Line& l, Text_iterator curr)
{
	auto p = l.begin();
	int pos{ 0 };
	while (p != curr.column()) {
		++pos;
		++p;
		if (pos == l.size())
			{ throw exception("bad column"); }
	}
	return pos;
}

//-----------------------------------------------------------------------

bool isbelong(const string& s, char ch)
{
	for (char s_ch : s)
		if ( s_ch == ch)
			{ return true; }
	return false;
}

//-----------------------------------------------------------------------

int main()
{
	ifstream file("doc.txt");
	if (!file) throw exception("can't open file");
	
	Document dd;
	for (string ss; getline(file, ss); )
		{ pushb_line(dd, ss); }
	print(dd);
	find_replace(dd.begin(), dd.end(), "this", "xxxx");
	find_replace(dd, "data", "information");
	find_replace(dd, "mode", "^_^");
	print(dd);

	vector<string> lines{ "first", "second", "apple", "wednesday", "tree" };
	cout << "Lexicography last string: " << *lastest(lines.begin(), lines.end())
		 << "\nSymblen of doc: " << symblen(dd.begin(), dd.end())
		 << "\nWordsize of doc: " << user_wordsize(dd.begin(), dd.end(), ". \"") << endl;


	return 0;
}