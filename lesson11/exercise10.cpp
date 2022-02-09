#include "/Users/tony/source/repos/libs/std_lib_facilities.h"

vector<string> split(const string& s, const string& w);

int main()
{
	string in{ "dsf sdfdsgs dfsgfs dsfsfsdthj dsfks fgsb ikjdfig" };
	vector<string> out;
	out = split(in, "qadr.asx/");
	for (string s : out)cout << s << '\n';
	return 0;
}

vector<string> split(const string& s, const string& w)
{
	string redact{ s };
	for (char& ch : redact)
		for (char space : w)
			if (ch == space)ch = ' ';

	vector<string> split;
	stringstream line{ redact };
	for (string buf; line >> buf; split.push_back(buf));
	return split;
}