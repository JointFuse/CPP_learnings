#include"std_lib_facilities.h"

void error(string s);
double ctof(double c);
void qubesolve(double a, double b, double c);
void task1();

int main()
try {
	setlocale(LC_ALL, "Russian");

	task1();

	keep_window_open();
	return 0;
}
catch (exception& e) {
	cerr << "Ошибка:" << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...) {
	cerr << "Неизвестное исключение!\n";
	keep_window_open();
	return 2;
}

void error(string s)
{
	throw runtime_error(s);
}

double ctof(double c)
{
	if (c < -273.15) error("Значение температуры ниже минимально допустимого");
	double f = 9.0 / 5 * c + 32;
	return f;
}

void qubesolve(double a, double b, double c)
{
	double k;
	k = pow(b, 2) - 4 * a * c;
	if (k < 0) error("Действительных корней нет");
	cout << "Первый корень: " << (-b + sqrt(k)) / (2 * a) << "\nВторой корень: " << (-b - sqrt(k)) / (2 * a) << "\n";
}

void task1()
{
	cout << "Введите количество суммируемых значений:\n";
	int n;
	double sum;
	cin >> n;
	cout << "Введите несколько целых чисел (| для окончания ввода):\n";
	vector<int> v;
	while (cin >> sum) v.push_back(sum);
	if (n > v.size()) error("Введено недостаточно значений");
	sum = 0;
	cout << "Сумма первых " << n << " чисел (";
	for (int i = 0; i < n;++i) {
		sum += v[i];
		cout << v[i] << " ";
	}
	vector<double> w;
	if (sum < 0)error("Сумма не может быть представлена типом double");
	cout << ") равна " << sum << "\n";
	for (int i = 0; i < (n - 1);++i) w.push_back(v[i] - v[i + 1]);
	for (double i : w)cout << i << " ";
}