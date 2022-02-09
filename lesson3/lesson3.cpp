#include "std_lib_facilities.h"

int translator(double age) 
{
	int mounth = 0;
	while (age >= 1) {
		if (age == 0) break;
		age--;
		mounth += 12;
	}
	if (age != 0 && age < 1) {
		age *= 10;
		while (age >= 1) {
			if (age == 0) break;
			age--;
			mounth++;
		}
	}
	return mounth;
}

void task1()
{
	cout << "Пожалуйста, введите свое имя и возраст\n";
	string first_name = "???";
	double age = 3.6;
	int month = -1;
	cin >> first_name >> age;
	month = translator(age);
	cout << "Привет, " << first_name << " (возраст " << age << " в месяцах: " << month << ")\n";
}

void task2()
{
	cout << "Пожалуйста, введите значение с плаввающей точкой: ";
	double n;
	cin >> n;
	cout << "n == " << n
		<< "\nn+1 == " << n + 1
		<< "\nn*2 == " << n * 2
		<< "\nn*3 == " << n * 3
		<< "\nn^2 == " << n * n
		<< "\nn/2 == " << n / 2
		<< "\nsqrt(n) == " << sqrt(n)
		<< "\n";
}

void task3()
{
	cout << "Вводите слова для поиска повторяющихся, для выхода введите exit\n";
	string previous = " ";
	string current;
	while (cin >> current) {
		if (current == "exit") break;
		if (previous == current)
			cout << "Повторяющеейся слово: " << current << "\n";
		previous = current;
	}
}

void task4()
{
	cout << "Введите число с плавающей запятой, для выхода введите 666\n";
	double d = 0;
	while (cin >> d) {
		if (d == 666) break;
		int i = d;
		char c = i;
		int i2 = c;
		cout << " d==" << d
			<< " i==" << i
			<< " i2==" << i2
			<< " char(" << c << ")\n";
	}
}

void task5()
{
	cout << "Введите значение в милях\n";
	double mil = 0;
	cin >> mil;
	cout << mil << " миль = " << mil * 1.609 << " километров\n";
}

void task6()
{
	cout << "Введите два числа с плавающей точкой\n";
	double val1 = 0;
	double val2 = 0;
	cin >> val1 >> val2;
	if (val1 > val2) cout << val1 << " > " <<val2 << "\n";
	else if (val1 < val2) cout << val1 << " < " << val2<< "\n";
	else cout << val1 << " = " << val2 << "\n";
	cout << "сумма = " << val1 + val2
		<< "\nразность = " << val1 - val2
		<< "\nпроизведение = " << val1 * val2
		<< "\nчастное = " << val1 / val2;
}

void task7()
{
	cout << "Введите три целых числа\n";
	int x1, x2, x3;
	cin >> x1 >> x2 >> x3;
	while (x1 > x2) {
		int b = x1;
		x1 = x2;
		x2 = b;
		if (x2 > x3) {
			int b = x2;
			x2 = x3;
			x3 = b;
		}
	}
	if (x2 > x3) {
		int b = x2;
		x2 = x3;
		x3 = b;
		while (x1 > x2) {
			int b = x1;
			x1 = x2;
			x2 = b;
			if (x2 > x3) {
				int b = x2;
				x2 = x3;
				x3 = b;
			}
		}
	}
	cout << x1 << ", " << x2 << ", " << x3 << "\n";
}

void task8()
{
	cout << "Введите три слова\n";
	string x1, x2, x3;
	cin >> x1 >> x2 >> x3;
	while (x1 > x2) {
		string b = x1;
		x1 = x2;
		x2 = b;
		if (x2 > x3) {
			string b = x2;
			x2 = x3;
			x3 = b;
		}
	}
	if (x2 > x3) {
		string b = x2;
		x2 = x3;
		x3 = b;
		while (x1 > x2) {
			string b = x1;
			x1 = x2;
			x2 = b;
			if (x2 > x3) {
				string b = x2;
				x2 = x3;
				x3 = b;
			}
		}
	}
	cout << x1 << ", " << x2 << ", " << x3 << "\n";
}

void task9()
{
	cout << "Введите челое число\n";
	int x;
	cin >> x;
	if (x % 2 == 1) cout << "Число " << x << " является нечетным\n";
	else cout << "Число " << x << " является четным\n";
}

void task10()
{
	cout << "Введите слово для перевода в число\n";
	string x;
	cin >> x;
	if (x == "нуль") cout << "0\n";
	else if (x == "один") cout << "1\n";
	else if (x == "два") cout << "2\n";
	else if (x == "три") cout << "3\n";
	else if (x == "четыре") cout << "4\n";
	else cout << "Я не знаю такого числа\n";
}

void task11()
{
	cout << "Введите символ операции с двумя операндами\n";
	string d;
	double x;
	double y;
	cin >> d >> x >> y;
	if (d == "+" || d == "plus") cout << x + y << "\n";
	else if (d == "-" || d == "minus") cout << x - y << "\n";
	else if (d == "*" || d == "mul") cout << x * y << "\n";
	else if (d == "/" || d == "div") cout << x / y << "\n";
}

void task12()
{
	cout << "Введите количество 1-, 5-, 10-, 25-, 50- центовых монет\n";
	int x[5];
	string m[10];
	m[0] = " одноцентовая монета";
	m[1] = " пятицентовая монета";
	m[2] = " десятицентовая монета";
	m[3] = " двадцатипятицентовая монета";
	m[4] = " пятидесятицентовая монета";
	m[5] = " одноцентовых монет";
	m[6] = " пятицентовых монет";
	m[7] = " десятицентовых монет";
	m[8] = " двадцатипятицентовых монет";
	m[9] = " пятидесятицентовых монет";
	cin >> x[0] >> x[1] >> x[2] >> x[3] >> x[4];
	for (int i = 0; i < 5; i++) {
		if (x[i] == 1) cout << "У вас " << x[i] << m[i] << "\n";
		else cout << "У вас " << x[i] << m[i + 5] << "\n";
	}
	int y = x[0] + 5 * x[1] + 10 * x[2] + 25 * x[3] + 50 * x[4];
	int a = y % 100;
	int b = (y - a) / 100;
	if (b == 1) cout << "У вас " << b << " доллар ";
	else cout << "У вас " << b << " долларов ";
	if (a == 1) cout << a << " цент\n";
	else cout << a << " центов\n";
}

int main()
{
	setlocale(LC_ALL, "Russian");
	system("chcp 1251");
	while (1) {
		cout << "Введите целое число от 1 до 12\n";
		int k = NULL;
		cin >> k;
		switch (k) {
		case 1: task1();
			break;
		case 2: task2();
			break;
		case 3: task3();
			break;
		case 4: task4();
			break;
		case 5: task5();
			break;
		case 6: task6();
			break;
		case 7: task7();
			break;
		case 8: task8();
			break;
		case 9: task9();
			break;
		case 10: task10();
			break;
		case 11: task11();
			break;
		case 12: task12();
			break;
		default: cout << "ЦЕЛОЕ ЧИСЛО ОТ 1 ДО 12, НЕ ТУПИ!!!\n";
		}
	}
 }