#include "lesson8.h"

vector<int> my_vector{ 0, 1, 2, 3, 4, 50 };
vector <string> my_string{ "one", "two", "three", "four", "five" };

namespace PWS {
	vector<double> weight{ 21,2324 };
	vector<double> price{ 4314,74 };
	
	double sum(const vector<double>& weight, const vector<double>& price)
	{
		if (weight.size() != price.size())
			error("Vectors sizes doesn't coincide");
		double sum{ 0 };

		for (int i = 0; i < price.size(); ++i)
			sum += price[i] * weight[i];

		return sum;
	}
}

namespace NAS {
	vector<string> name{};
	vector<double> age{};

	void main()
	{
		{
			cout << "Enter names\n" << "1's name: ";
			int i{ 2 };
			string name_buf;
			cin >> name_buf;
			while (name_buf != "end") {
				name.push_back(name_buf);
				cout << i << "'s name: ";
				++i;
				cin >> name_buf;
			}
		}

		cout << "Enter ages\n";
		for (int i = 0; i < name.size(); ++i) {
			cout << name[i] << ": ";
			double age_buf;
			cin >> age_buf;
			age.push_back(age_buf);
		}

		for (int i = 0; i < name.size(); ++i)
			cout << name[i] << " age: " << age[i] << '\n';

		{
			vector<string> name_copy = name;
			sort(name.begin(), name.end());
			int i{ 0 };

			while (name != name_copy) {
				for(int j = i; j < name.size(); ++j)
					if (name[j] == name_copy[i]) {
						if (j == i) ++i;
						else {
							swap(name_copy[i], name_copy[j]);
							swap(age[i], age[j]);
						}
					}
			}
		}

		for (int i = 0; i < name.size(); ++i)
			cout << name[i] << " age: " << age[i] << '\n';
	}
}

namespace Math {
	int maxv(const vector<int>& v)
	{
		int max{ v[0] };

		for (int i : v)
			if (i > max) max = i;

		return max;
	}

	result fourm(const vector<int>& v)
	{
		result x;

		x.max = maxv(v);
		x.min = v[0];
		for (int i : v) {
			if (i < x.min) x.min = i;
			x.mean += i;
		}
		x.mean /= v.size();
		x.median = v[v.size() / 2];

		return x;
	}
}

void positive(vector<int>& v, const int& l)
{
	for (int i = 0; i < l; i++)
		v.push_back(v[i] + 1);
}

void fibonacci(const int& x, const int& y, vector<int>& v, const int& n)
{
	switch (v.size()) {
	case 0: {
		v.push_back(x);
		v.push_back(y);
	} break;
	case 1: {
		v.push_back(y);
		v[0] = x;
	} break;
	case 2: {
		v[0] = x;
		v[1] = y;
	}break;
	default:
		return;
	}

	for (int i = 0; i < n; i++) {
		v.push_back(v[i] + v[i + 1]);
	}
}

vector<int> swap_create(const vector<int>& v)
{
	vector<int> v2;

	for (int i = v.size() - 1; i >= 0; i--) {
		v2.push_back(v[i]);
	}

	return v2;
}

void swap_clear(vector<int>& v)
{
	int s = v.size();
	for (int i = 0; i < s; i++)
		for (int j = s - 1; j > i; j--)
			swap(v[j - 1], v[j]);
}

vector<string> swap_create_str(const vector<string>& v)
{
	vector<string> v2;

	for (int i = v.size() - 1; i >= 0; i--) {
		v2.push_back(v[i]);
	}

	return v2;
}

void swap_clear_str(vector<string>& v)
{
	int s = v.size();
	for (int i = 0; i < s; i++)
		for (int j = s - 1; j > i; j--)
			swap(v[j - 1], v[j]);
}

void print(ostream& monitor, vector<int>& my_vector)
{
	//fibonacci(1, 2, my_vector, 44);
	//positive(my_vector, 30);

	monitor << "Vector of numbers:" << '\n';
	for (int i : my_vector) {
		monitor << '\t' << i << '\n';
	}
}

void print_str(ostream& monitor, const vector<string>& my_string)
{
	monitor << "Vector of string's:" << '\n';
	for (int i = 0; i < my_string.size(); i++) {
		monitor << '\t' << my_string[i] << '\n';
	}
}

void print_until_s(const vector<string>& v, const string& quit)
{
	for (string s : v) {
		if (s == quit) return;
		cout << s << '\n';
	}
}

void print_until_ss(const vector<string>& v, const string& quit)
{
	bool second{ false };
	for (string s : v) {
		if (s == quit && second) return;
		else if (s == quit) second = true;
		cout << s << '\n';
	}
}

vector<int> string_analize(vector<string>& vs)
{
	vector<int> vs_char_size;

	for (int i = 0; i < vs.size(); ++i)
		vs_char_size.push_back(vs[i].length());

	int max{ 0 }, min{ 0 };
	for (int i = 0; i < vs_char_size.size(); ++i) {
		if (vs_char_size[i] > vs_char_size[max]) max = i;
		if (vs_char_size[i] < vs_char_size[min]) min = i;
	}
	cout << "Most long string: " << vs[max] << '\n'
		<< "Most short string: " << vs[min] << '\n';

	sort(vs.begin(), vs.end());
	cout << "First string: " << vs[0]
		<< "\nLast string: " << vs[vs.size() - 1] << '\n';
	return vs_char_size;
}

void f(const int i)
{
	int b = 2 * i;
	i += b;
}