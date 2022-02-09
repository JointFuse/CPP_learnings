#include <string>
#include <vector>
#include <iostream>

using namespace std;

template<typename T> struct S { 
	S(T v) : val{v} { }

	const T& get() const { return val; }
	T& get() { return val;}
	
	S<T>& operator= (const T& v)
	{
		if (this = &v) return *this;

		this->val = v.val;
		return *this;
	}
private:
	T val;
};

template<typename T>
const T& get(S<T>& obj) { return obj.get(); }

template<typename T>
istream& operator>> (istream& is, S<T>& s)
{
	return is >> s.get();
}

template<typename T>
istream& operator>> (istream& is, vector<T>& v)
{
	char ch;
	is >> ch;
	if (ch != '{') {
		is.clear(ios_base::badbit);
		return is;
	}
	for (T buf; is >> buf; ) {
		is >> ch;
		if (ch != ',' && ch != '}') {
			is.clear(ios_base::badbit);
			return is;
		}
		v.push_back(buf);
		if (ch == '}') { return is; }
	}
}

template<typename T>
ostream& operator<< (ostream& os,const vector<T>& v)
{
	os << "{ ";
	for (int i{ 0 }; i < v.size(); ++i) {
		os << v.at(i);
		if (i != v.size() - 1)
			{ os << ", "; }
	}
	return os << " }";
}

template<typename T>
void read_val(T& v)
{
	cin >> v;
	if(cin.rdstate())	{
		cin.clear(); 
		string ss;
		cin >> ss;
		return;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	S<int> s_int(1);
	S<char> s_char(' ');
	S<double> s_dbl(1.0);
	S<string> s_str(" ");
	S<vector<int>> s_vec({});
	
	cout << "Введите целое число: ";
	read_val(s_int.get());
	cout << "Введите знак: ";
	read_val(s_char.get());
	cout << "Введите число с плавающей точкой: ";
	read_val(s_dbl.get());
	cout << "Введите строку: ";
	read_val(s_str.get());
	cout << "Введите несколько целых чисел для заполнения вектора: ";
	read_val(s_vec.get());

	cout << "Целое число: " << get(s_int)
		 << "\nЗнак: " << get(s_char)
		 << "\nЧисло с плавающей точкой: " << get(s_dbl)
		 << "\nСтрока: " << get(s_str)
		 << "\nВектор целых чисел: " << get(s_vec);

	return 0;
}