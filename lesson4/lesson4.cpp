#include "std_lib_facilities.h"

void task1()
{
	cout << "Please, print a number to multiply\n";
	int x, y = 0;
	cin >> x;
	for (int i = 0; i < x ; ++i) {
		y += x;
	}
	cout << "x^2 = " << y << "\n";
}

void task2()
{
	cout << "Please, print words to store\n";
	vector<string> words;
	vector<string> wrongs = {"Broccoli", "Potato", "Putin"};
	for (string temp; cin >> temp; ) {
		if (temp == "exit") break;
		words.push_back(temp);
	}
	sort(words.begin(), words.end());
	for (int i = 0; i < words.size(); ++i) {
		for (int j = 0; j < wrongs.size(); ++j)
			if (words[i] == wrongs[j])
				words[i] = "BLEEP";
		cout << words[i] << "\n";
	}
	delete[] & words;
}

double razn(double x, double y)
{
	if ((x - y) >= 0) return x - y;
	else return y - x;
}

void task3()
{
	cout << "Print two numbers, to cancel print: |\n";
	vector<double> buf = {0, 0};
	while (cin >> buf[0] >> buf[1]) {
		if (buf[0] == '|' || buf[1] == '|') break;
		if (razn(buf[0], buf[1]) < 0.01)
			cout << "Числа почти равны\n";
		else if (buf[0] > buf[1])
			cout << "Наибольшее значение равно: " << buf[0] << "\n"
			<< "Наименьшее значение равно: " << buf[1] << "\n";
		else if (buf[0] < buf[1])
			cout << "Наибольшее значение равно: " << buf[1] << "\n"
			<< "Наименьшее значение равно: " << buf[0] << "\n";
		else cout << "Числа равны: " << buf[0] << ", " << buf[1] << "\n";
	}
	delete[] &buf;
}

double cm(double l, string u)							//Преобразование в сантиметры
{
	if (u == "cm") return l;
	else if (u == "m") return l * 100;
	else if (u == "in") return l * 2.54;
	else if (u == "ft") return l * 30.48;
}

void task4()
{
	cout << "Вводите растояния с единицей измерения\n";
	vector<string> stand = {"cm", "m", "in", "ft"};		//Список допустимых единиц измерения
	vector<double> tempv;								//Список значений (хранятся в см)
	string unit;										//Последняя единица измерения
	double max;											//Максимальное значение (хранится в см)
	double min;											//Минимальное значение (хранится в см)
	string umax;										//Единица изм. макс. значения
	string umin;										//Единица изм. мин. значения
	double temp;										//Последнее значение
	bool b = 1;											//Булева переменная, используемая при проверке единиц измерения на допустимость

	while (b) {											//Цикл не завершится, пока введенная единица измерения не будет допустимой
		cin >> temp >> unit;
		for (string i : stand) {						//Проверка единицы измерения
			if (unit == i) b = 0;						//Если совпадает, выходим из цикла
		}
		if (b == 1) cout << "Неправильная единица измерения!\nВведите новые значения\n";
	}

	tempv.push_back(cm(temp, unit));					//Сохраняем значение
	double sum = cm(temp, unit);						//Инициализируем сумму
	int kol = 1;										//Инициализируем количество значений
	umax = unit;										//Первое значение указываем максимальным и минимальным
	umin = unit;
	max = temp;											//То же для единицы измерения первого значения
	min = temp;
	cout << temp << unit << "\n";						//Выводим первое знач.
	while (cin >> temp >> unit) {						//Цикл, принимающий знач.
		b = 1;											//Для входа в цикл проверки един. изм. на допустимость меняем b
		for (string i : stand) {						//Перебираем все допустимые един. изм.
			if (unit == i) {							//Если совпадает, переходим к проверке на мин\макс знач и 
				b = 0;									//обновлению нужных переменных
				if (cm(temp, unit) > cm(max, umax)) {
					max = temp;
					umax = unit;
					cout << "Наибольшее среди всех введенных: ";
				}
				else if (cm(temp, unit) < cm(min, umin)) {
					min = temp;
					umin = unit;
					cout << "Наименьшее среди всех введенных: ";
				}
				tempv.push_back(cm(temp, unit));
				sum += cm(temp, unit);
				++kol;
				cout << temp << unit << "\n";
			}
		}
		if (b == 1) cout << "Неправильная единица измерения!\nВведите новые значения\n";
	}
	sort(tempv.begin(), tempv.end());					//Сортируем накопленные значения
	for (double i : tempv)								//Цикл для вывода всех значений
		cout << i / 100 << " ";

	cout << "\nНаибольшее значение: " << max << umax << "; "
		<< "Наименьшее значение: " << min << umin << "\n"
		<< "Сумма: " << sum/100 << "m; Всего значений: " << kol << "\n";
}

void task5()
{
	cout << "Введите несколько значений для поиска медианы\n";
	vector<double> temps;
	for (double temp; cin >> temp; )
		temps.push_back(temp);
	sort(temps.begin(), temps.end());
	if (temps.size() % 2 == 0)
		temps[0] = (temps[temps.size() / 2 - 1] + temps[temps.size() / 2 ]) / 2;
	else
		temps[0] = temps[temps.size() / 2];
	cout << "Медианная температура: "
		<< temps[0] << "\n";
}

void task6()
{
	cout << "Вы открыли бонусную игру, загадайте целое число от 1 до 100 и введите его\n";
	int x;
	int a = 0;
	int c = 100;
	string yn;
	cin >> x;
	for (int i = 0; i < 7; ++i) {
		cout << "Ваше число больше " << (a + c) / 2 << "?\n";
		int b = 1;
		while (b) {
			cin >> yn;
			if (yn == "да") {
				a = (a + c) / 2;
				b = 0;
			}
			else if (yn == "нет") {
				c = (a + c) / 2;
				b = 0;
			}
			else cout << "Введите да или нет\n";
		}
		if (i == 6) {
			cout << "Ваше число: ";
			if (yn == "да")
				cout << c << "\n";
			else
				cout << a << "\n";
		}
		if ((a + c) / 2 == x) {
			cout << "Ваше число: " << (a + c) / 2 << "\n";
			i = 6;
		}
	}
}

int slv(string str)
{
	vector<string> stnd = { "1", "one", "2", "two", "3", "three", "4", "four", "5", "five", "6", "six", "7", "seven", "8", "eight", "9", "nine", "0", "zero" };
	vector<int> cifr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	for (int i = 0; i < stnd.size(); ++i)
		if (str == stnd[i])
			return cifr[(i) / 2];
}

void task7()
{
	string X, Y;
	int x, y;
	char z = ' ';
	cout << "Это простой калькулятор, для выхода введите '|' вместо символа\nВведите две цифры и один из символов операций (+, -, *, /)\n";
	while (z != '|') {
		int b = 1;
		while (b == 1) {
			b = 0;
			cin >> X;
			x = slv(X);
			cin >> Y;
			y = slv(Y);
			cin >> z;
			if (!((z == '+') || (z == '-') || (z == '*') || (z == '/') || (z == '|'))) {
				b = 1;
				cout << "Вы ввели неверный символ операции (допустимые символы +, -, *, /)\n";
			}
		}
		if (z == '+')
			cout << "Сумма " << x << " и " << y << " равна " << x + y << "\n";
		if (z == '-')
			cout << "Разность " << x << " и " << y << " равна " << x - y << "\n";
		if (z == '*')
			cout << "Произведение " << x << " и " << y << " равно " << x * y << "\n";
		if (z == '/')
			cout << "Частное " << x << " и " << y << " равно " << x / y << "\n";

	}
}

void task8()
{
	vector<string> slova = { "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять", "ноль" };
	vector<int> cifri = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	string slovo;
	int cifra = 0;
	cin >> slovo;
	for (string i : slova) {
		if (slovo == slova[cifra])
			cout << cifri[cifra] << "\n";
		++cifra;
	}
}

void task9()
{
	double sum = 0;
	for (int i = 0; i < 666; ++i) {
		if ((sum += pow(2, i)) < 0) {
			cout << "MAX: " << i << "\n";
			break;
		}
		cout << "Клетка: " << i + 1 << "\nрисинок:" << sum << "\n";
	}
}

void task10()
{
	int size = 0;
	int p;
	int len = 2;
	int max;
	cout << "Введите число, до которого требуется найти все простые числа\n";
	cin >> max;
	while (size < max) {
		vector<int> primes;
		vector<int> flag;
		for (int i = 2; i <= len; ++i) {
			flag.push_back(1);
		}
		for (int i = 0; i < len - 1; ++i) {
			if (flag[i] == 1) {
				primes.push_back(p = i + 2);
				for (int j = 2; (p * j) <= len; ++j) {
					flag[(p * j) - 2] = 0;
				}
			}
		}
		if (primes.size() == max) {
			for (int i : primes)
				cout << i << "; ";
			cout << "\n";
		}
		size = primes.size();
		++len;
	}
}

void task12()
{
	vector<int> nums;
	int max;
	int u = 0;
	while (u >= 0) {
		++u;
		nums.push_back(0);
	}
	for (int i = 0; i < (nums.size() - 1); ++i)
		for (int j = 0; j < (nums.size() - 1); ++j)
			if (i == j)
				++nums[i];
	max = nums[0];
	for (int i = 0; i < (nums.size() - 1); ++i)
		if (nums[i] > max)
			max = i;
	cout << max;
}

void task13()
{
	vector<string> buf;
	vector<int> mode;
	int num;
	cout << "Вводите слова, для выхода введите конец\n";
	string inter;
	cin >> inter;
	while (inter != "конец") {
		buf.push_back(inter);
		mode.push_back(1);
		cin >> inter;
	}
	for (int i = 0; i < (buf.size() - 1); ++i)
		for (int j = 0; j < (buf.size() - 1); ++j)
			if (buf[i] == buf[j])
				++mode[i];
	num = 0;
	for (int i = 0; i < (mode.size() - 1); ++i)
		if (mode[i] > mode[num])
			num = i;
	inter = buf[num];
	sort(buf.begin(), buf.end());
	cout << "Минимальное слово: " << buf[0] << "; Мода: " << inter << "; Максимальное слово: " << buf[buf.size() - 1] << "\n";
}

void task14()
{
	double a, b, c, d, x1, x2;
	cout << "Введите коэффициенты a, b, c квадратного уравнения\n";
	cin >> a >> b >> c;
	cout << "Уравнение: " << a << "x^2 + " << b << "x + " << c << " = 0\n";
	d = pow(b, 2) - 4 * a * c;
	if (d == 0) {
		x1 = (-1) * b / (2 * a);
		cout << "Единственный корень: " << x1 << "\n";
	}
	else if (d > 0) {
		x1 = (sqrt(d) - b) / (2 * a);
		x2 = (-1) * (sqrt(d) + b) / (2 * a);
		cout << "Первый корень: " << x1 << " второй корень: " << x2 << "\n";
	}
	else
		cout << "Корней нет\n";
}

void task15()
{
	vector<string> names;
	vector<int> scores;
	string name;
	int score;
	cout << "Вводите имена и баллы, в конце введите NoName 0\n";
	cin >> name >> score;
	while ((name != "NoName") && (score != 0)) {
		names.push_back(name);
		scores.push_back(score);
		cin >> name >> score;
	}
	for (string i : names) {
		score = 0;
		for (string j : names)
			if (i == j) {
				++score;
			}
		if (score > 1)
			cout << "ОШИБКА (имя " << i << " повторяется)\n";
	}
	cout << "Введите имя чтобы узнать баллы\n\tИмена\tБаллы\n";
	name = "NULL";
	score = NULL;
	cin >> score;
	while (score != -1) {
		int b = 1;
		for (int i = 0; i < scores.size(); ++i)
			if (scores[i] == score) {
				cout << "\t" << names[i] << "\n";
				b = 0;
			}
		if (b)
			cout << "Баллы не найдены\n";
		cin >> score;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	system("chcp 1251");
	char i;
	while (1) {
		cout << "Please, print a number\n";
		cin >> i;
		switch (i) {
		case '1': task1();
			break;
		case '2': task2();
			break;
		case '3': task3();
			break;
		case '4': task4();
			break;
		case '5': task5();
			break;
		case '$': task6();
			break;
		case 'k': task7();
			break;
		case 'c': task8();
			break;
		case 'h': task9();
			break;
		case 'p': task10();
			break;
		case 'g': task12();
			break;
		case 't': task13();
			break;
		case 'r': task14();
			break;
		case 'e': task15();
		default: cout << "Wrong number\n";
			break;
		}
	}
}