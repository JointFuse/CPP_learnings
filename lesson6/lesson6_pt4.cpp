#include "std_lib_facilities.h"

bool isnew{ false };
vector<bool> bulls(4);
vector<bool> cows(4);
vector<char> chars(4);
vector<char> user(4);
vector<char> alphabet{ 'q','w','e','r','t','y','u','i','o','p','a','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m' };

class engine_error {};
class setrand_error{};

bool userchars();
void engine();
void setrand();

int main()
try {
	setlocale(LC_ALL, "Russian");
	system("chcp 1251");

	char c;
	bool b{ true };

	while (b) {
		c = ' ';
		setrand();
		engine();
		cout << "Сыграть еще раз? (y/n)\n";
		while ((c != 'y') && (c != 'n')) {
			cout << "y/n?\n";
			cin >> c;
		}
		if (c == 'n') b = false;
	}
}
catch (engine_error) {
	cerr << "Ошибка: вы ввели не букву\n";
	engine();
}
catch (setrand_error) {
	cerr << "Ошибка: число должно быть больше 0\n";
	setrand();
}

void engine()
/*Логика игры, отдельно вводятся 4 цифры,
  если на вход поступает не цифра,
  функция создает исключение с ошибкой
  и обратным вызовом движка*/
{
	if (!isnew) {								//Глобальная переменная isnew принимает значение true
		for (int i = 0; i < 4; ++i) {			//после стартовой инициализации всех данных и перед стартом игры
			bulls[i] = false;					//значение false записывается после того, как пользователь угадал число
			cows[i] = false;
		}
		for (int i = 0; i < 4; ++i)
			chars[i] = alphabet[rand() % 25];
		isnew = true;
	}

	while (isnew) {
		if (userchars())
			throw engine_error();

		for (int i = 0; i < 4; ++i)
			if (chars[i] == user[i]) bulls[i] = true;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				if ((chars[i] == user[j]) && (bulls[j] != true) && (bulls[i] != true)) cows[j] = true;

		if ((bulls[0] == true) && (bulls[1] == true) && (bulls[2] == true) && (bulls[3] == true)) isnew = false;
		else {
			int count{ 0 };
			for (bool i : bulls)
				if (i) ++count;
			cout << "Быков: " << count;
			count = 0;
			for (bool i : cows)
				if (i) ++count;
			cout << " Коров: " << count << "\n";
			for (int i = 0; i < 4; ++i) {								//После вывода информации о быках и коровах
				bulls[i] = false;										//обнуляем значения векторов
				cows[i] = false;
			}
		}
	}

	cout << "Ура, вы отгадали число!\n";
}

void setrand()
/*Установка первого числа
 для функции рандомайзера,
 вводимое число должно
 быть положительным*/
{
	cout << "Введите любое число\n";
	int n;
	cin >> n;
	if (n < 0) throw setrand_error();
	srand(n);
}

bool userchars()
{
	cout << "Введите 4 буквы\n";

	for (int i = 0; i < 4; ++i) {
		char ch;
		cin >> ch;

		switch (ch) {
		case 'q': case 'w': case 'e': case 'r': case 't': case 'y': case 'u': case 'i': case 'o': case 'p': case 'a': case 's': case 'd':
		case 'f': case 'g': case 'h': case 'j': case 'k': case 'l': case 'z': case 'x': case 'c': case 'v': case 'b': case 'n': case 'm':
			user[i] = ch;
			break;
		default:
			return 1;
		}
	}
	return 0;
}