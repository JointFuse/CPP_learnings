/*
	������� �����������

	������� ������:

	����������� ������� �����������  � ������ 2020�.
	����������� ������ ������������ � ��� 2007�.
	����������� ������ ������������ � ������� 2006�.
	����������� ������ ������������ � ������� 2004�.
	���������� ������ ������������ (bs@cs.tamu.edu) ������ 2004�.

	��� ��������� ��������� �������� ��������� ������������.
	���� �������������� �� ������ cin; ����� - � ����� cout.

	���������� ��� �����:

	����������:
		���������
		����������_����������
		�������_�����
		������_����������
		������
		�����
		�����

	�����:
		;

	�����:
		quit

	������:
		help

	������_����������:
		sqrt( ��������� )

	�������_�����:
		pow( ��������� , ��������� )

	����������_����������:
		# ���_���������� = ���������
		# const ���_���������� = ���������

	���_����������:
		�������
		���_���������� '_'
		���_���������� �����

	���������:
		����
		��������� + ����
		��������� - ����

	����:
		���������_���������
		���� * ���������_���������
		���� / ���������_���������
		���� % ���������_���������

	���������_���������:
		�����
		���_����������
		���_���������� = ���������
		( ��������� )
		- ���������_���������

	�����:
		�������_�_���������_������

	���� �� ������ cin ����� Token_stream � ������ ts.
	������ � ����������� ����� Symbol_stream � ������ st.
*/

#include <std_lib_facilities.h>

void print_help()
{
	cout << "\t���������� �� ������������:"
		<< "\n\n\t� ������ ������ ������� ������ �� ����������� ����������."
		<< "\n\t�������� ��������� �� ��������������� ����������.\n";
}

// �������, ����� ��� � �������� (�����/���)
class Token {
public:
	char kind;
	double value;
	string name;

	// ������������� ��� �������� ��������
	Token(char ch) :kind(ch), value(0) { }

	// ������������� ��� �����
	Token(char ch, double val) :kind(ch), value(val) { }

	// ������������� ��� ���� ����������
	Token(char ch, string n) :kind(ch), name(n) { }
};

// ����� ������ � �������� � ���������, ������������
// ����������� ���������, �������� � �������� ������
class Token_stream {
public:
	Token get();										// ��������� �������
	void unget(Token t) { buffer = t; full = true; }	// ���������� ������� � �����
	void ignore(char c);								// ����������� ������� ��
														// ������� � ������������

	// ������������� ������� ������ �� ���������
	Token_stream() :full(0), buffer(0) { }
private:
	bool full;				// ���������� ��������� ������
	Token buffer;			// ������ ������ ������
};

const char let = 'L';		// ����������� ������� ���� �������� ����������
const char quit = 'Q';		// ����������� ������� ���� ������ �� ����������
const char print = ';';		// ����������� ������� ���� ������ ������
const char number = '8';	// ����������� ������� ���� �����
const char name = 'a';		// ����������� ������� ���� ����� ����������
const char sqr = 'S';		// ����������� ������� ���� ������ ����������
const char pw = 'P';		// ����������� ������� ���� ���������� � �������
const char cnst = 'c';		// ����������� ������� ���� ���������
const char help = 'H';		// ����������� ������� ���� ���������
const char lg = 'l';		// ����������� ������� ���� ��������
const string declquit = "quit";		// �������� ����� ��� ������
const string decllet = "#";			// �������� ����� ��� ���������� let
const string declconst = "const";	// �������� ����� ��� ���������
const string declhelp = "help";		// �������� ����� ��� ���������
const string decllog = "log";		// �������� ����� ��� ���������� ���������

// ��������� ������� �� ������
Token Token_stream::get()
{
	if (full) { full = false; return buffer; }			// �������� ������� ������ � ������
	char ch;
	cin >> ch;
	switch (ch) {				// �������� ���� �������
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
		return Token(ch);		// ������� �������������� ��������
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
	{	cin.unget();			// ����������� ������� ����� ����� � ����� cin
	double val;
	cin >> val;					// ������ ����� �� ������ cin
	return Token(number, val);	// ������� ������� ���� �����
	}
	default:
		if (isalpha(ch) || (ch == '#')) {		// ���� ������ ���� ����� - ������ ����������
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch)||(ch == '_'))) s += ch;	// ���������� ������� �� ���� � '_'
																						// ���������� ����� ��������� ������
																						// ����������, ������� ����������� � �����
			cin.unget();
			if (s == decllet) return Token(let);						// ���������� let - �������� ���������
			if (s == declquit) return Token(quit);						// ���������� quit - �����
			if (s == "sqrt") return Token(sqr);							// ���������� sqr - ������ ����������
			if (s == "pow") return Token(pw);							// ���������� pw - ���������� � �������
			if (s == declconst) return Token(cnst);						// ����������� ���������
			if (s == declhelp) return Token(help);						// ��������� ���������
			if (s == decllog) return Token(lg);						// ���������� ���������
			return Token(name, s);										// ����������� �������� ���� �����
		}
		error("Bad token");
	}
}

// ������� �������� �� ������� �
void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind) {	// �������� ����������� ������
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin >> ch)				// ������� �������� �� �������
		if (ch == c) return;
}

// ����� ��� �������� ����������
class Variable {
public:
	string name;
	double value;
	bool isconst;

	// ������ ������������� ���������� � ������������� ���������
	Variable(string n, double v, bool b) :name(n), value(v), isconst(b) { }
};

// ����� ��� �������� ����������
class Symbol_table {
public:
	vector<Variable> names;

	double get(string s);
	void set(string s, double d);
	bool is_declared(string s);
	void define(string n, double v, bool b) { names.push_back(Variable(n, v, b)); }
};

// ����� ���������� � �������
double Symbol_table::get(string s)
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return names[i].value;	// ���� ���� ������� ����������
														// ���������� �� ��������
	error("get: undefined name ", s);					// ���� ��� - ������
}

// ������������ ������ �������� ����������
void Symbol_table::set(string s, double d)
{
	for (int i = 0; i <= names.size(); ++i)
		if (names[i].name == s) {						// ���� ���� ������ ��� - ������ ��������
			if (names[i].isconst) error("const cant be redefined");
			names[i].value = d;
			return;
		}
	error("set: undefined name ", s);					// ���� ��� - ������
}

// �������� ���������� �� ���������� � ����� ������
bool Symbol_table::is_declared(string s)
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

Token_stream ts;
Symbol_table st;

double expression();

// ��������� �����, ���������� � ��������� � �������
double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':							// ��������� ��������� � �������
	{	
		double d = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;
	}
	case '-':							// ��������� �������� ������
		return -primary();
	case number:						// ��������� �����
		return t.value;
	case name:							// ��������� ����������
	{
		Token k = ts.get();
		if (k.kind == '=') {			// ��������������� ����������
			k = ts.get();
			if (k.kind != number) error("need number to set");
			st.set(t.name, k.value);
			return st.get(t.name);	// �������� ������ ��������
		}
		ts.unget(k);
		return st.get(t.name);		// ������� �������� ��������
	}
	default:
		error("primary expected");
	}
}

// ��������� �������� ��������������� ����������
double term()
{
	double left = primary();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':				// ���������
			left *= primary();
			break;
		case '/':				// �������
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

// ��������� �������� �������������� ��������
double expression()
{
	double left = term();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':				// ��������
			left += term();
			break;
		case '-':				// ���������
			left -= term();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

// ��������� �������� ����������
double declaration()
{
	Token t = ts.get();
	bool b{ false };
	if (t.kind == cnst) { b = true; t = ts.get(); }						// �������� ������������ ���������
	if (t.kind != name) error("name expected in declaration");			// �������� ���������� ���������� � �����
	string name = t.name;
	if (st.is_declared(name)) error(name, " declared twice");			// ������ ������� ��� ���������� � ����� ������
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);	// ����� ����� ������ ���� ���� '='
	double d = expression();
	st.define(name, d, b);												// ���������� ���������� � ������
	return d;															// ���������� ����� ���� ������ ���������
}

// ����� ����������
double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:						// ���������� ����������
		return declaration();
	case help:						// ������
		print_help();
		return 69;
	case sqr:						// ���������� ����� �����������
	{
		double d = expression();
		if (d < 0) error("sqrt(x): x must be positive");
		return sqrt(d);
	}
	case pw:						// ���������� ������� �����
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
	default:						// ������ � �����������
		ts.unget(t);
		return expression();
	}
}

// ������� ������ cin �� ����� '=' ����� ������
void clean_up_mess()
{
	ts.ignore(print);
}

const string prompt = "> ";		// ����������� � �����
const string result = "= ";		// ����������� ������

// ������ ������ ������������
void calculate()
{
	while (true) try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();	// ������������ ';'
		if (t.kind == quit) return;
		ts.unget(t);
		cout << result << statement() << endl;
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;				// ����� ��������� �� ������
		clean_up_mess();						// ���������� � ����������� ������
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