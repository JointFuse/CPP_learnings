/*
	Простой калькулятор

	История версий:

	Переработан Майским Александром  в январе 2020г.
	Переработан Бьярне Страуструпом в мае 2007г.
	Переработан Бьярне Страуструпом в августе 2006г.
	Переработан Бьярне Страуструпом в августе 2004г.
	Разработан Бьярне Страуструпом (bs@cs.tamu.edu) весной 2004г.

	Эта программа реализует основные выражения калькулятора.
	Ввод осуществляется из потока cin; вывод - в поток cout.

	Грамматика для ввода:

	Инструкция:
		Выражение
		Добавление_переменной
		Степень_числа
		Корень_квадратный
		Помощь
		Вывод
		Выход

	Вывод:
		;

	Выход:
		quit

	Помощь:
		help

	Корень_квадратный:
		sqrt( Выражение )

	Степень_числа:
		pow( Выражение , Выражение )

	Добавление_переменной:
		# Имя_переменной = Выражение
		# const Имя_переменной = Выражение

	Имя_переменной:
		символы
		Имя_переменной '_'
		Имя_переменной цифры

	Выражение:
		Терм
		Выражение + Терм
		Выражение - Терм

	Терм:
		Первичное_выражение
		Терм * Первичное_выражение
		Терм / Первичное_выражение
		Терм % Первичное_выражение

	Первичное_выражение:
		Число
		Имя_переменной
		Имя_переменной = Выражение
		( Выражение )
		- Первичное_выражение

	Число:
		Литерал_с_плавающей_точкой

	Ввод из потока cin через Token_stream с именем ts.
	Работа с переменнымы через Symbol_stream с именем st.
*/

#include <std_lib_facilities.h>

void print_help()
{
	cout << "\tИнструкция по эксплуатации:"
		<< "\n\n\tВ данный момент ведутся работы по составлению инструкции."
		<< "\n\tПриносим извенения за предоставленные неудобства.\n";
}

// Лексема, имеет тип и значение (число/имя)
class Token {
public:
	char kind;
	double value;
	string name;

	// Инициализация для символов операций
	Token(char ch) :kind(ch), value(0) { }

	// Инициализация для чисел
	Token(char ch, double val) :kind(ch), value(val) { }

	// Инициализация для имен переменных
	Token(char ch, string n) :kind(ch), name(n) { }
};

// Поток лексем с буффером и функциями, реализующими
// возможности получения, возврата и пропуска лексем
class Token_stream {
public:
	Token get();										// Считывает лексему
	void unget(Token t) { buffer = t; full = true; }	// Возвращает лексему в поток
	void ignore(char c);								// Отбрасывает символы до
														// символа с включительно

	// Инициализация пустого буфера по умолчанию
	Token_stream() :full(0), buffer(0) { }
private:
	bool full;				// Показывает состояние буфера
	Token buffer;			// Хранит данные буфера
};

const char let = 'L';		// Обозначение лексемы типа создания переменной
const char quit = 'Q';		// Обозначение лексемы типа выхода из приложения
const char print = ';';		// Обозначение лексемы типа вывода ответа
const char number = '8';	// Обозначение лексемы типа число
const char name = 'a';		// Обозначение лексемы типа имени переменной
const char sqr = 'S';		// Обозначение лексемы типа корень квадратный
const char pw = 'P';		// Обозначение лексемы типа возведение в степень
const char cnst = 'c';		// Обозначение лексемы типа константа
const char help = 'H';		// Обозначение лексемы типа подсказка
const char lg = 'l';		// Обозначение лексемы типа логарифм
const string declquit = "quit";		// Ключевое слово для выхода
const string decllet = "#";			// Ключевое слово для инструкции let
const string declconst = "const";	// Ключевое слово для константы
const string declhelp = "help";		// Ключевое слово для подсказки
const string decllog = "log";		// Ключевое слово для инструкции логарифма

// Получение лексемы из потока
Token Token_stream::get()
{
	if (full) { full = false; return buffer; }			// Проверка наличия лесемы в буфере
	char ch;
	cin >> ch;
	switch (ch) {				// Проверка типа лексемы
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ';':
	case '=':
	case ',':
		return Token(ch);		// Лексемы математических символов
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{	cin.unget();			// Возвращение первого знака числа в поток cin
	double val;
	cin >> val;					// Чтение числа из потока cin
	return Token(number, val);	// Возврат лексемы типа число
	}
	default:
		if (isalpha(ch) || (ch == '#')) {		// Если первый знак буква - чтение инструкции
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch)||(ch == '_'))) s += ch;	// Инструкции состоят из букв и '_'
																						// инструкция может оказаться именем
																						// переменной, поэтому считываются и цифры
			cin.unget();
			if (s == decllet) return Token(let);						// Инструкция let - создание перменной
			if (s == declquit) return Token(quit);						// Инструкция quit - выход
			if (s == "sqrt") return Token(sqr);							// Инструкция sqr - корень квадратный
			if (s == "pow") return Token(pw);							// Инструкция pw - возведение в степень
			if (s == declconst) return Token(cnst);						// Модификатор константы
			if (s == declhelp) return Token(help);						// Инструция подсказки
			if (s == decllog) return Token(lg);						// Инструкция логарифма
			return Token(name, s);										// Возвращение литерала типа число
		}
		error("Bad token");
	}
}

// Пропуск символов до символа с
void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind) {	// Проверка содержимого буфера
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin >> ch)				// Пропуск символов до нужного
		if (ch == c) return;
}

// Класс для хранения переменных
class Variable {
public:
	string name;
	double value;
	bool isconst;

	// Пресет инициализации переменной с модификатором константы
	Variable(string n, double v, bool b) :name(n), value(v), isconst(b) { }
};

// Класс для хранения переменных
class Symbol_table {
public:
	vector<Variable> names;

	double get(string s);
	void set(string s, double d);
	bool is_declared(string s);
	void define(string n, double v, bool b) { names.push_back(Variable(n, v, b)); }
};

// Поиск переменной в векторе
double Symbol_table::get(string s)
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return names[i].value;	// Если есть искомая переменная
														// возвращает ее значение
	error("get: undefined name ", s);					// Если нет - ошибка
}

// Присваивание нового значения переменной
void Symbol_table::set(string s, double d)
{
	for (int i = 0; i <= names.size(); ++i)
		if (names[i].name == s) {						// Если есть нужное имя - замена значения
			if (names[i].isconst) error("const cant be redefined");
			names[i].value = d;
			return;
		}
	error("set: undefined name ", s);					// Если нет - ошибка
}

// Проверка существует ли переменная с таким именем
bool Symbol_table::is_declared(string s)
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

Token_stream ts;
Symbol_table st;

double expression();

// Обработка чисел, переменных и выражений в скобках
double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':							// Обработка выражения в скобках
	{	
		double d = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;
	}
	case '-':							// Обработка унарного минуса
		return -primary();
	case number:						// Обработка числа
		return t.value;
	case name:							// Обработка переменной
	{
		Token k = ts.get();
		if (k.kind == '=') {			// Переопределение переменной
			k = ts.get();
			if (k.kind != number) error("need number to set");
			st.set(t.name, k.value);
			return st.get(t.name);	// Возварат нового значения
		}
		ts.unget(k);
		return st.get(t.name);		// Возврат текущего значения
	}
	default:
		error("primary expected");
	}
}

// Обработка действий первостепенного приоритета
double term()
{
	double left = primary();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':				// Умножение
			left *= primary();
			break;
		case '/':				// Деление
		{	
			double d = primary();
			if (d == 0) error("/: divide by zero");
			left /= d;
			break;
		}
		case '%':
		{
			int i1 = narrow_cast<int>(left);
			int i2 = narrow_cast<int>(primary());
			if (i2 == 0) error("%: divide by zero");
			left = i1 % i2;
			break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}

// Обработка действий второстепенной важности
double expression()
{
	double left = term();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':				// Сложение
			left += term();
			break;
		case '-':				// Вычитание
			left -= term();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

// Обработка создания переменной
double declaration()
{
	Token t = ts.get();
	bool b{ false };
	if (t.kind == cnst) { b = true; t = ts.get(); }						// Проверка модификатора константы
	if (t.kind != name) error("name expected in declaration");			// Создание переменной начинается с имени
	string name = t.name;
	if (st.is_declared(name)) error(name, " declared twice");			// Нельзя создать две переменных с одним именем
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);	// После имени должен идти знак '='
	double d = expression();
	st.define(name, d, b);												// Добавление переменной в вектор
	return d;															// Объявление может быть частью выражения
}

// Поиск инструкций
double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:						// Добавление переменной
		return declaration();
	case help:						// Помощь
		print_help();
		return 69;
	case sqr:						// Вычисление корня квадратного
	{
		double d = expression();
		if (d < 0) error("sqrt(x): x must be positive");
		return sqrt(d);
	}
	case pw:						// Вычисление степени числа
	{
		t = ts.get();
		if (t.kind != '(') error("pow(x,y): '(' expected");
		double d = expression();

		t = ts.get();
		if (t.kind != ',') error("pow(x,y): ',' expected");

		double b = expression();
		int i = narrow_cast<int>(b);

		t = ts.get();
		if (t.kind != ')') error("pow(x,y): ')' expected");
		return pow(d, b);
	}
	case lg:
		return log(expression());
	default:						// Работа с выражениями
		ts.unget(t);
		return expression();
	}
}

// Очистка потока cin до знака '=' после ошибки
void clean_up_mess()
{
	ts.ignore(print);
}

const string prompt = "> ";		// Приглашение к вводу
const string result = "= ";		// Обозначение вывода

// Логика работы калькулятора
void calculate()
{
	while (true) try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();	// Отбрасывание ';'
		if (t.kind == quit) return;
		ts.unget(t);
		cout << result << statement() << endl;
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;				// Вывод сообщения об ошибке
		clean_up_mess();						// Подготовка к продолжению работы
	}
}

int main()

try {
	setlocale(LC_ALL, "Russian");
	system("chcp 1251");

	st.define("k", 1000, true);

	calculate();
	return 0;
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
	char c;
	while (cin >> c && c != ';');
	return 1;
}
catch (...) {
	cerr << "exception\n";
	char c;
	while (cin >> c && c != ';');
	return 2;
}