#include "exercise2.h"

void Name_pairs::read_names()
{
	cout << "\nEnter names, to end print '#'\n";

	string buf{ " " };
	cin >> buf;
	while (buf != "#") {
		name.push_back(buf);
		cin >> buf;
	}
}

void Name_pairs::read_ages()
{
	cout << "\nEnter ages to known names\n";

	double buf{ 0 };
	for (string s : name) {
		cout << s << ": ";
		cin >> buf;
		age.push_back(buf);
	}
}

void Name_pairs::sort()
{
	if (name.size() != age.size()) throw runtime_error("Vector's sizes isn't compare");

	vector<string> buf{ name };
	std::sort(name.begin(), name.end());

	int i{ 0 };
	while (name != buf) {
		for (int j = i; j < name.size(); ++j)
			if (buf[i] == name[j]) {
				swap(buf[i], buf[j]);
				swap(age[i], age[j]);
				if (i == j) ++i;
			}
	}

	cout << "\n\nNames sorted\n";
}

void Name_pairs::print()
{
	if (name.size() != age.size()) throw runtime_error("Vector's sizes isn't compare");

	for (int i = 0; i < name.size(); ++i)
		cout << "\nName: " << name[i] << "\tAge: " << age[i];
}

int Name_pairs::get_size() const
{
	unsigned int size{ name.size() };
	if (size != age.size()) throw runtime_error("Vector's size isn't compare");

	return int(size);
}

ostream& operator<< (ostream& os, const Name_pairs& obj)
{
	stringstream out;
	out << "\n\nNames\tAges\n";
	for (int i = 0; i < obj.get_size(); ++i)
		out << obj.get_name(i) << '\t' << obj.get_age(i) << '\n';

	return os << out.str();
}

bool operator== (const Name_pairs& left, const Name_pairs& right)
{
	if (left.get_size() != right.get_size()) return false;

	for (int i = 0; i < left.get_size(); ++i)
		if (left.get_name(i) != right.get_name(i) 
			|| left.get_age(i) != right.get_age(i))
			return false;
	
	return true;
}

bool operator!= (const Name_pairs& left, const Name_pairs& right)
{
	if (left.get_size() != right.get_size()) return true;
	
	for (int i = 0; i < left.get_size(); ++i)
		if (left.get_name(i) != right.get_name(i)
			|| left.get_age(i) != right.get_age(i))
			return true;

	return false;
}