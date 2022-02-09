/*
	������� �����������

	������� ������:

	����������� ������� ����������� � ������ 2020�.
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

#include "calculator.h"

//-----------------------------------------------------------------------------------

using namespace Calculator;

// ����������, ������������ ����������
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

// ��������� ������� �� ������
Token Token_stream::get()
{
	if (full) { full = false; return buffer; }	// �������� ������� ������ � ������
	char ch;
	*my_istream >> ch;
	if (ch < char(-1)) { ch = ';'; }
	switch (ch) {					// �������� ���� �������
	case '(': case ')':
	case '+': case '-':
	case '*': case '/':
	case '%': case ';':
	case '=': case ',':
		return Token(ch);			// ������� �������������� ��������
	case '.': case '0':
	case '1': case '2':
	case '3': case '4':
	case '5': case '6':
	case '7': case '8':
	case '9':
	{	my_istream->unget();		// ����������� ������� ����� ����� � ����� cin
		double val;
		*my_istream >> val;			// ������ ����� �� ������ cin
		return Token(number, val);	// ������� ������� ���� �����
	}
	case 'I': case 'V':
	case 'X': case 'C': 
	case 'D': case 'M':
	{	my_istream->unget();		// ����������� ������� ����� ����� � ����� cin
		Roman_int r;				// �������� ���������� ��� ������ �������� �����
		if (!(*my_istream >> r))	// ������ �������� �����
			error("Bad roman");				// ������ ��� �������� ����������
		return Token(number, r.as_int());	// ������� �������� ����� ��� int
	}
	default:
		if (isalpha(ch) || (ch == '#')) {	// ���� ������ ���� ����� - ������ ����������
			string s;
			s += ch;
			while (my_istream->get(ch) && (isalpha(ch) || isdigit(ch)||(ch == '_'))) s += ch;	// ���������� ������� �� ���� � '_'
																								// ���������� ����� ��������� ������
																								// ����������, ������� ����������� � �����
			my_istream->unget();
			if (s == decllet) return Token(let);						// ���������� let - �������� ���������
			if (s == declquit) return Token(quit);						// ���������� quit - �����
			if (s == "sqrt") return Token(sqr);							// ���������� sqr - ������ ����������
			if (s == "pow") return Token(pw);							// ���������� pw - ���������� � �������
			if (s == declconst) return Token(cnst);						// ����������� ���������
			if (s == declhelp) return Token(help);						// ��������� ���������
			if (s == decllog) return Token(lg);							// ���������� ���������
			if (s == declfread) return Token(fileread);					// ���������� ������ �����
			if (s == declfwrite) return Token(filewrite);				// ���������� ������ �����
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
	while (*my_istream >> ch)// ������� �������� �� �������
		if (ch == c) return;
}

//-----------------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------------

double Calculator::primary(Token_stream& ts)
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':							// ��������� ��������� � �������
	{	
		double d = expression(ts);
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;
	}
	case '-':							// ��������� �������� ������
		return -primary(ts);
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

//-----------------------------------------------------------------------------------

double Calculator::term(Token_stream& ts)
{
	double left = primary(ts);
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':				// ���������
			left *= primary(ts);
			break;
		case '/':				// �������
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
		case '+':				// ��������
			left += term(ts);
			break;
		case '-':				// ���������
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
	if (t.kind == cnst) { b = true; t = ts.get(); }						// �������� ������������ ���������
	if (t.kind != name) error("name expected in declaration");			// �������� ���������� ���������� � �����
	string name = t.name;
	if (st.is_declared(name)) error(name, " declared twice");			// ������ ������� ��� ���������� � ����� ������
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);	// ����� ����� ������ ���� ���� '='
	double d = expression(ts);
	st.define(name, d, b);												// ���������� ���������� � ������
	return d;															// ���������� ����� ���� ������ ���������
}

//-----------------------------------------------------------------------------------

double Calculator::statement(Token_stream& ts)
{
	Token t = ts.get();
	switch (t.kind) {
	case let:						// ���������� ����������
		return declaration(ts);
	case help:						// ������
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
	case sqr:						// ���������� ����� �����������
	{
		double d = expression(ts);
		if (d < 0) error("sqrt(x): x must be positive");
		return sqrt(d);
	}
	case pw:						// ���������� ������� �����
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
	default:						// ������ � �����������
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
							{ t = ts.get(); }	// ������������ ';'
		if (t.kind == quit)	{ return 1; }
		ts.unget(t);

		if (result_enable)	{ *my_ostream << result; }
		*my_ostream << statement(ts);
		if (result_enable)	{ *my_ostream << endl; }

		if (no_loop)		{ return 0; }
	}
	catch (runtime_error& e) {
		if (result_enable)	{ *my_ostream << "Error: "; }
		*my_ostream << e.what();			// ����� ��������� �� ������
		if (result_enable)	{ *my_ostream << endl; }
		if (no_loop)		{ return 0; }
		clean_up_mess(ts);					// ���������� � ����������� ������
	}
}

//-----------------------------------------------------------------------------------
