#include "concantinator.h"

string simple_concant(const string& f1, const string& f2)
{
	string f_new{ "" };
	f_new += "concant_" + f1;
	
	ofstream ofs(f_new);
	ifstream ifs1(f1);
	ifstream ifs2(f2);

	string buf{ "" };
	while (ifs1 >> buf)
		ofs << ' ' << buf;
	while (ifs2 >> buf)
		ofs << ' ' << buf;

	return f_new;
}

string vocab_concant(const string& f1, const string& f2)
{
	string f_new;
	f_new = "concant_" + f1;

	ofstream ofs(f_new);
	ifstream ifs1(f1);
	ifstream ifs2(f2);

	string buf;
	vector<string> vec_buf;
	while (ifs1 >> buf)
		vec_buf.push_back(buf);
	while (ifs2 >> buf)
		vec_buf.push_back(buf);

	sort(vec_buf.begin(), vec_buf.end());

	for (string s : vec_buf)
		ofs << s << ' ';

	return f_new;
}

double file_summ(const string& f)
{
	ifstream file(f);

	double sum{ 0 };
	double buf;

	for (char ch; file >> ch; ) {
		if (isdigit(ch) || ch == '-') {
			file.unget();
			file >> buf;
			sum += buf;
		}
	}

	return sum;
}