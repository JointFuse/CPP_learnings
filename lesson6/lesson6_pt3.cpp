#include "std_lib_facilities.h"
#include <bitset>
//------------------------------------------------------------------------------

#define MAXLENGTH   4

//------------------------------------------------------------------------------

class Token {
public:
    char kind;                  // what kind of token
    bitset<MAXLENGTH> value;    // for bit numbers: a value
    Token(char ch)              // make a token from a char
        :kind(ch), value(0) { }
    Token(char ch, bitset<MAXLENGTH> val)   // make a token from a char and bitset
        :kind(ch), value(val) { }
};

class Token_stream {
public:
    Token_stream();             // make a Token_stream that reads from cin
    Token get();                // get a Token (get() is defined elsewhere)
    void putback(Token t);      // put a Token back
private:
    bool full;                  // is there a Token in the buffer?
    Token buffer;               // here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
    :full(false), buffer(0)     // no Token in buffer
{
}

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
    if (full) error("putback(): буффер заполнен");
    buffer = t;                 // copy t to buffer
    full = true;                // buffer is now full
}

Token Token_stream::get()
{
    if (full) {                 // do we already have a Token ready?
                                // remove Token from buffer
        full = false;
        return buffer;
    }

    char ch;
    cin >> ch;

    switch (ch) {
    case '=':       // for "print"
    case 'x':       // for "quit"
    case '(': case ')': case '!': case '~': case '&': case '^': case '|':
        return Token(ch);       // let each character represent itself
    case '1': case '0':
    {
        cin.putback(ch);        // put digit back into the input stream
        bitset<MAXLENGTH> val;
        cin >> val;             // read a bitset number
        return Token('8', val); // let '8' represent "a number"
    }
    default:
        error("Неправильная лексема");
    }
}

//------------------------------------------------------------------------------

Token_stream ts;                // provides get() and putback()

//------------------------------------------------------------------------------

bitset<MAXLENGTH> expression(); // declaration so that primary() can call expression()

//------------------------------------------------------------------------------

// deal with numbers and parentheses
bitset<MAXLENGTH> primary()
{
    Token t = ts.get();
    switch (t.kind) {
    case '(':                       // handle '(' expression ')'
    {
        bitset<MAXLENGTH> d = expression();
        t = ts.get();
        if (t.kind != ')') error("Требуется ')'");
        return d;
    }
    case '8':                       // we use '8' to represent a number
        return t.value;
    default:
        error("Ожидается первичное выражение");
    }
}

// deal with '!' and '~'
bitset<MAXLENGTH> unarexpr()
{
    Token t = ts.get();

    switch (t.kind) {
    case '!': case '~':             // handle '!'primary and '~'primary 
        return ~primary();
    case '8':                       // return number
        return t.value;
    default:
        error("Ожидается первичное выражение или унарный оператор");
    }
}

// deal with '&'
bitset<MAXLENGTH> andexpr()
{
    bitset<MAXLENGTH> left = unarexpr();
    Token t = ts.get();             // get the next Token from Token_stream

    while (true) {
        switch (t.kind) {
        case '&':
            left &= unarexpr();
            t = ts.get();
            break;
        default:
            ts.putback(t);          // put t back into the Token strem
            return left;
        }
    }
}

// deal with '^'
bitset<MAXLENGTH> xorexpr()
{
    bitset<MAXLENGTH> left = andexpr();
    Token t = ts.get();             // get the next Token from Token stream

    while (true) {
        switch (t.kind) {
        case '^':
            left ^= andexpr();
            t = ts.get();
            break;
        default:
            ts.putback(t);          // put t back into the Token stream
            return left;
        }
    }
}

// deal with '|'
bitset<MAXLENGTH> expression()
{
    bitset<MAXLENGTH> left = xorexpr(); // read and evaulate a xor
    Token t = ts.get();                 // read the next Token from Token stream

    while (true) {
        switch (t.kind) {
        case '|':
            left |= xorexpr();
            t = ts.get();
            break;
        default:
            ts.putback(t);              // put t back into the Token stream
            return left;                // finally: no more iterations: return the answer
        }
    }
}

//------------------------------------------------------------------------------

int main()
try
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");

    cout << '\n' << "Добро пожаловать в программу-калькулятор для двоичных чисел!" << "\n"
        << "Вводите выражения с двоичными числами." << "\n"
        << "Можно использовать следующие операторы: |, ^, &, ~, !, (, )" << '\n'
        << "Для вывода результата на экран используется знак '=', для выхода из программы введите 'x'" << "\n";

    bitset<MAXLENGTH> val;
    while (cin) {
        Token t = ts.get();

        if (t.kind == 'x') break;   // 'x' for quit
        if (t.kind == '=')          // '=' for print now
            cout << "=" << val << "\n";
        else
            ts.putback(t);
        val = expression();
    }
    keep_window_open();
}
catch (exception& e) {
    cerr << "ошибка: " << e.what() << '\n';
    keep_window_open();
    return 1;
}
catch (...) {
    cerr << "Уупс: незнакомое исключение!\n";
    keep_window_open();
    return 2;
}