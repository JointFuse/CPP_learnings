/*
	Простой калькулятор

	История версий:

	Переработан Майским Александром в январе 2020г.
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

#include "calculator.h"

//-----------------------------------------------------------------------------------

using namespace Calculator;

// Переменные, используемые программой
namespace calc {
	char ch;
}

//-----------------------------------------------------------------------------------

void print_help()
{
	ifstream help_text("help.txt", ios_base::binary);
	if (!help_text) {
		cout << "\tQuick tutorial:"
			 << "\n\n\tThe instruction is not available at the moment,"
			 << "\n\tcheck if [ help.txt ] in program folder."
			 << "\n\tWe apologise for the inconvenience.\n";
	}

	string out{ "" };
	for(char ch; help_text.read(as_bytes(ch), sizeof(char));)
	{
		out += ch;
	}

	system("chcp 65001");
	cout << out << endl;
}

//-----------------------------------------------------------------------------------

// Получение лексемы из потока
Token Token_stream::get()
{
	if (full) { full = false; return buffer; }	// Проверка наличия лесемы в буфере
	char ch;
	*my_istream >> ch;
	if (ch < char(-1)) { ch = ';'; }
	switch (ch) {					// Проверка типа лексемы
	case '(': case ')':
	case '+': case '-':
	case '*': case '/':
	case '%': case ';':
	case '=': case ',':
		return Token(ch);			// Лексемы математических символов
	case '.': case '0':
	case '1': case '2':
	case '3': case '4':
	case '5': case '6':
	case '7': case '8':
	case '9':
	{	my_istream->unget();		// Возвращение первого знака числа в поток cin
		double val;
		*my_istream >> val;			// Чтение числа из потока cin
		return Token(number, val);	// Возврат лексемы типа число
	}
	case 'I': case 'V':
	case 'X': case 'C': 
	case 'D': case 'M':
	{	my_istream->unget();		// Возвращение первого знака числа в поток cin
		Roman_int r;				// Создание переменной для чтения римского числа
		if (!(*my_istream >> r))	// Чтение римского числа
			error("Bad roman");				// Ошибка при неверном синтаксисе
		return Token(number, r.as_int());	// Возврат римского числа как int
	}
	default:
		if (isalpha(ch) || (ch == '#')) {	// Если первый знак буква - чтение инструкции
			string s;
			s += ch;
			while (my_istream->get(ch) && (isalpha(ch) || isdigit(ch)||(ch == '_'))) s += ch;	// Инструкции состоят из букв и '_'
																								// инструкция может оказаться именем
																								// переменной, поэтому считываются и цифры
			my_istream->unget();
			if (s == decllet) return Token(let);						// Инструкция let - создание перменной
			if (s == declquit) return Token(quit);						// Инструкция quit - выход
			if (s == "sqrt") return Token(sqr);							// Инструкция sqr - корень квадратный
			if (s == "pow") return Token(pw);							// Инструкция pw - возведение в степень
			if (s == declconst) return Token(cnst);						// Модификатор константы
			if (s == declhelp) return Token(help);						// Инструция подсказки
			if (s == decllog) return Token(lg);							// Инструкция логарифма
			if (s == declfread) return Token(fileread);					// Инструкция чтения файла
			if (s == declfwrite) return Token(filewrite);				// Инструкция записи файла
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
	while (*my_istream >> ch)// Пропуск символов до нужного
		if (ch == c) return;
}

//-----------------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------------

double Calculator::primary(Token_stream& ts)
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':							// Обработка выражения в скобках
	{	
		double d = expression(ts);
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;
	}
	case '-':							// Обработка унарного минуса
		return -primary(ts);
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

//-----------------------------------------------------------------------------------

double Calculator::term(Token_stream& ts)
{
	double left = primary(ts);
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':				// Умножение
			left *= primary(ts);
			break;
		case '/':				// Деление
		{	
			double d = primary(ts);
			if (d == 0) error("/: divide by zero");
			left /= d;
			break;
		}
		case '%':
		{
			int i1 = narrow_cast<int>(left);
			int i2 = narrow_cast<int>(primary(ts));
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

//-----------------------------------------------------------------------------------

double Calculator::expression(Token_stream& ts)
{
	double left = term(ts);
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':				// Сложение
			left += term(ts);
			break;
		case '-':				// Вычитание
			left -= term(ts);
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

//-----------------------------------------------------------------------------------

double Calculator::declaration(Token_stream& ts)
{
	Token t = ts.get();
	bool b{ false };
	if (t.kind == cnst) { b = true; t = ts.get(); }						// Проверка модификатора константы
	if (t.kind != name) error("name expected in declaration");			// Создание переменной начинается с имени
	string name = t.name;
	if (st.is_declared(name)) error(name, " declared twice");			// Нельзя создать две переменных с одним именем
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);	// После имени должен идти знак '='
	double d = expression(ts);
	st.define(name, d, b);												// Добавление переменной в вектор
	return d;															// Объявление может быть частью выражения
}

//-----------------------------------------------------------------------------------

double Calculator::statement(Token_stream& ts)
{
	Token t = ts.get();
	switch (t.kind) {
	case let:						// Добавление переменной
		return declaration(ts);
	case help:						// Помощь
		print_help();
		return 69;
	case fileread:
	{
		string file_name;
		for (char ch{' '}; my_istream->rdstate() != 3; *my_istream >> ch) {
			file_name += ch;
		}
		my_istream->unget();
		static ifstream new_ifs(file_name);
		if (!new_ifs) return 1;
		my_istream = &new_ifs;
		no_loop = false;
		return 0;
	}
	case filewrite:
	{
		string file_name;
		for (char ch{ ' ' }; my_istream->rdstate() != 3; *my_istream >> ch) {
			file_name += ch;
		}
		my_istream->unget();
		static ofstream new_ofs(file_name);
		if (!new_ofs) return 1;
		my_ostream = &new_ofs;
		result_enable = true;
		return 0;
	}
	case sqr:						// Вычисление корня квадратного
	{
		double d = expression(ts);
		if (d < 0) error("sqrt(x): x must be positive");
		return sqrt(d);
	}
	case pw:						// Вычисление степени числа
	{
		t = ts.get();
		if (t.kind != '(') error("pow(x,y): '(' expected");
		double d = expression(ts);

		t = ts.get();
		if (t.kind != ',') error("pow(x,y): ',' expected");

		double b = expression(ts);
		int i = narrow_cast<int>(b);

		t = ts.get();
		if (t.kind != ')') error("pow(x,y): ')' expected");
		return pow(d, b);
	}
	case lg:
		return log(expression(ts));
	default:						// Работа с выражениями
		ts.unget(t);
		return expression(ts);
	}
}

//-----------------------------------------------------------------------------------

void Calculator::clean_up_mess(Token_stream& ts)
{
	ts.ignore(print);
}

//-----------------------------------------------------------------------------------

bool Calculator::calculate()
{
	while (true) try {
		if (prom_enable)	{ *my_ostream << prompt; }

		if (ts.is_full())	{ ts.get(); }
		Token t = ts.get();
		if (!no_loop) 
			while (t.kind == print) 
							{ t = ts.get(); }	// Отбрасывание ';'
		if (t.kind == quit)	{ return 1; }
		ts.unget(t);

		if (result_enable)	{ *my_ostream << result; }
		*my_ostream << statement(ts);
		if (result_enable)	{ *my_ostream << endl; }

		if (no_loop)		{ return 0; }
	}
	catch (runtime_error& e) {
		if (result_enable)	{ *my_ostream << "Error: "; }
		*my_ostream << e.what();			// Вывод сообщения об ошибке
		if (result_enable)	{ *my_ostream << endl; }
		if (no_loop)		{ return 0; }
		clean_up_mess(ts);					// Подготовка к продолжению работы
	}
}

//-----------------------------------------------------------------------------------
