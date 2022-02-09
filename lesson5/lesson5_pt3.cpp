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
	cerr << "������:" << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...) {
	cerr << "����������� ����������!\n";
	keep_window_open();
	return 2;
}

void error(string s)
{
	throw runtime_error(s);
}

double ctof(double c)
{
	if (c < -273.15) error("�������� ����������� ���� ���������� �����������");
	double f = 9.0 / 5 * c + 32;
	return f;
}

void qubesolve(double a, double b, double c)
{
	double k;
	k = pow(b, 2) - 4 * a * c;
	if (k < 0) error("�������������� ������ ���");
	cout << "������ ������: " << (-b + sqrt(k)) / (2 * a) << "\n������ ������: " << (-b - sqrt(k)) / (2 * a) << "\n";
}

void task1()
{
	cout << "������� ���������� ����������� ��������:\n";
	int n;
	double sum;
	cin >> n;
	cout << "������� ��������� ����� ����� (| ��� ��������� �����):\n";
	vector<int> v;
	while (cin >> sum) v.push_back(sum);
	if (n > v.size()) error("������� ������������ ��������");
	sum = 0;
	cout << "����� ������ " << n << " ����� (";
	for (int i = 0; i < n;++i) {
		sum += v[i];
		cout << v[i] << " ";
	}
	vector<double> w;
	if (sum < 0)error("����� �� ����� ���� ������������ ����� double");
	cout << ") ����� " << sum << "\n";
	for (int i = 0; i < (n - 1);++i) w.push_back(v[i] - v[i + 1]);
	for (double i : w)cout << i << " ";
}