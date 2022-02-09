#include "std_lib_facilities.h"

void main()
{
	setlocale(LC_ALL, "Russian");
	system("chcp 1251");

	vector<string> d1{ "понедельник", "Понедельник", "пон", "Пон", "понед", "Понед", "пн", "Пн", "ПН", "пнд", "Пнд", "ПНД" };
	vector<string> d2{ "вторник", "Вторник", "втор", "Втор", "вт", "ВТ", "Вт", "вторн", "Вторн", "вто", "Вто", "втр", "Втр", "ВТР", "втрн", "Втрн", "ВТРН" };
	vector<string> d3{ "среда", "Среда", "ср", "Ср", "СР", "сред", "Сред", "сре", "Сре", "срд", "Срд", "СРД" };
	vector<string> d4{ "четверг", "Четверг", "чт", "ЧТ", "Чт", "чет", "Чет", "четв", "Четв", "чтв", "Чтв", "ЧТВ" };
	vector<string> d5{ "пятница", "Пятница", "пятн", "Пятн", "пт", "Пт", "ПТ", "птн", "Птн", "ПТН" };
	vector<string> d6{ "суббота", "Суббота", "сб", "Сб", "СБ", "суб", "Суб", "СУБ", "сбт", "Сбт", "СБТ", "субт", "Субт", "СУБТ" };
	vector<string> d7{ "воскресенье", "Воскресенье", "вс", "Вс", "ВС", "воскр", "Воскр", "вскр", "Вскр" };

	vector<int> dt1;
	vector<int> dt2;
	vector<int> dt3;
	vector<int> dt4;
	vector<int> dt5;
	vector<int> dt6;
	vector<int> dt7;

	string usd{ " " };
	int usdt;
	bool b{ false };
	int count{ 0 };

	cout << "\nВводите день недели и данные\n";

	while (usd != "zero") {
		cin >> usd >> usdt;
		for (string i : d1)
			if (usd == i) {
				dt1.push_back(usdt);
				b = true;
			}
		for (string i : d2)
			if (usd == i) {
				dt2.push_back(usdt);
				b = true;
			}
		for (string i : d3)
			if (usd == i) {
				dt3.push_back(usdt);
				b = true;
			}
		for (string i : d4)
			if (usd == i) {
				dt4.push_back(usdt);
				b = true;
			}
		for (string i : d5)
			if (usd == i) {
				dt5.push_back(usdt);
				b = true;
			}
		for (string i : d6)
			if (usd == i) {
				dt6.push_back(usdt);
				b = true;
			}
		for (string i : d7)
			if (usd == i) {
				dt7.push_back(usdt);
				b = true;
			}
		if (!b) ++count;
		b = false;
	}

	cout << "\tКоличество ошибок ввода:\t" << count << "\n\n"
		<< "\tПонедельник\tВторник\tСреда\tЧетверг\tПятница\tСуббота\tВоскресенье\n";

	count = dt1.size();
	if (dt2.size() > count)count = dt2.size();
	if (dt3.size() > count)count = dt3.size();
	if (dt4.size() > count)count = dt4.size();
	if (dt5.size() > count)count = dt5.size();
	if (dt6.size() > count)count = dt6.size();
	if (dt7.size() > count)count = dt7.size();

	for (int i = 0; i < count; ++i) {
		if (i < dt1.size()) cout << "\t" << dt1[i];
		else cout << "\t";
		if (i < dt2.size()) cout << "\t\t" << dt2[i];
		else cout << "\t\t";
		if (i < dt3.size()) cout << "\t" << dt3[i];
		else cout << "\t";
		if (i < dt4.size()) cout << "\t" << dt4[i];
		else cout << "\t";
		if (i < dt5.size()) cout << "\t" << dt5[i];
		else cout << "\t";
		if (i < dt6.size()) cout << "\t" << dt6[i];
		else cout << "\t";
		if (i < dt7.size()) cout << "\t" << dt7[i];
		else cout << "\t";
		cout << "\n";
	}

	cout << "\tСуммы:\n\n";
	count = 0;
	for (int i : dt1)count += i;
	cout << "\t" << count;
	count = 0;
	for (int i : dt2)count += i;
	cout << "\t\t" << count;
	count = 0;
	for (int i : dt3)count += i;
	cout << "\t" << count;
	count = 0;
	for (int i : dt4)count += i;
	cout << "\t" << count;
	count = 0;
	for (int i : dt5)count += i;
	cout << "\t" << count;
	count = 0;
	for (int i : dt6)count += i;
	cout << "\t" << count;
	count = 0;
	for (int i : dt7)count += i;
	cout << "\t" << count;
}