#include "/Users/tony/source/repos/libs/std_lib_facilities.h"

struct Multi_num {
	int num;
	char base;
};

istream& operator>> (istream&, Multi_num&);
ostream& operator<< (ostream&, const Multi_num&);


int main()
{
	vector<Multi_num> nums;
	for (Multi_num buf; cin >> buf; nums.push_back(buf)) { }
	for (Multi_num mn : nums) cout << mn;
	return 0;
}

istream& operator>> (istream& is, Multi_num& mn)
{
	char ch;
	is >> ch;
	if (ch == '0') {
		is >> ch;
		if (isdigit(ch)) {
			is.unget();
			is >> oct >> mn.num;
			mn.base = 'o';
			return is;
		}
		else if (ch == 'x') {
			is >> hex >> mn.num;
			mn.base = 'h';
			return is;
		}
		is.clear(ios_base::failbit);
		return is;
	}
	if (!isdigit(ch)) {
		is.clear(ios_base::failbit);
		return is;
	}
	is.unget();
	is >> dec >> mn.num;
	mn.base = 'd';
	return is;
}

ostream& operator<< (ostream& os, const Multi_num& mn)
{
	switch (mn.base) {
	case 'd':
		cout << dec << showbase << mn.num << '\t' << "[decimal]" << '\t' 
			<< "turns into decimal" << '\t' << noshowbase << mn.num << '\n';
		break;
	case 'o':
		cout << oct << showbase << mn.num << '\t' << "[octal]" << "\t\t"
			<< "turns into decimal" << '\t' << noshowbase << dec << mn.num << '\n';
		break;
	case 'h':
		cout << hex << showbase << mn.num << '\t' << "[heximal]" << '\t' 
			<< "turns into decimal" << '\t' << noshowbase << dec << mn.num << '\n';
		break;
	default:
		break;
	}
	return os;
}