#include "/Users/tony/source/repos/libs/std_lib_facilities.h"

int main()
{
	ifstream ifs("dictinary.txt", ios_base::binary);
	ofstream ofs("output.txt");
	if (!ifs)return 1;
	if (!ofs)return 2;
	int space{ 0 };
	int alpha{ 0 };
	int digit{ 0 };
	int xdigit{ 0 };
	int upper{ 0 };
	int lower{ 0 };
	int alnum{ 0 };
	int cntrl{ 0 };
	int punct{ 0 };
	int print{ 0 };
	int graph{ 0 };
	for (char ch; ifs.read(as_bytes(ch), sizeof(char));) {
		if (isspace(ch))
			++space;
		if (isalpha(ch))
			++alpha;
		if (isdigit(ch))
			++digit;
		if (isxdigit(ch))
			++xdigit;
		if (isupper(ch))
			++upper;
		if (islower(ch))
			++lower;
		if (isalnum(ch))
			++alnum;
		if (iscntrl(ch))
			++cntrl;
		if (ispunct(ch))
			++punct;
		if (isprint(ch))
			++print;
		if (isgraph(ch))
			++graph;
	}
	int lw{ 6 };
	int rw{ 6 };
	ofs << setw(lw) << "Type:" << setw(rw) << "Count:" << '\n'
		<< setw(lw) << "space" << setw(rw) << space << '\n'
		<< setw(lw) << "alpha" << setw(rw) << alpha << '\n'
		<< setw(lw) << "digit" << setw(rw) << digit << '\n'
		<< setw(lw) << "xdigit" << setw(rw) << xdigit << '\n'
		<< setw(lw) << "upper" << setw(rw) << upper << '\n'
		<< setw(lw) << "lower" << setw(rw) << lower << '\n'
		<< setw(lw) << "alnum" << setw(rw) << alnum << '\n'
		<< setw(lw) << "cntrl" << setw(rw) << cntrl << '\n'
		<< setw(lw) << "punct" << setw(rw) << punct << '\n'
		<< setw(lw) << "print" << setw(rw) << print << '\n'
		<< setw(lw) << "graph" << setw(rw) << graph << '\n';
	return 0;
}