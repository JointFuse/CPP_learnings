#include "std_lib_facilities.h"


//------------------------------------------------------------------------------

vector<unsigned __int64> a;
char ch;

//------------------------------------------------------------------------------

void calcp();
void calcc();

void reader()
{
    cout << "Введите количество чисел для перебора: ";
    for (int i = 0; i < 2; ++i) {
        if (i == 1) cout << "Введите количество чисел в комбинации: ";

        cin >> ch;
        switch (ch) {
        case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
            cin.putback(ch);
            double b;
            cin >> b;
            a.push_back(b);
            if ((b - a[i]) != 0 || b <= 0) error("Требуется ввести целое число больше нуля!");
            break;
        default:
            error("Требуется ввести число больше нуля!");
        }
    }

    if (a[0] <= a[1]) error("а должно быть больше б!");

    cout << "Введите 'p' для вычисления перебора и 'c' для вычисления сочетания: ";
    cin >> ch;
    switch (ch) {
    case 'p':
        calcp();
        break;
    case 'c':
        calcc();
        break;
    default:
        error("Такой функции нет!");
    }
}

void calcp()
{
    unsigned __int64 up{ a[0] };
    for (int i = up - 1; i > 1; --i)
        up *= i;

    unsigned __int64 down{ a[0] - a[1] };
    for (int i = down - 1; i > 1; --i)
        down *= i;

    a.push_back(up / down);
}

void calcc()
{
    calcp();

    unsigned __int64 down{ a[1] };
    for (int i = down - 1; i > 1; --i)
        down *= i;

    a[2] = a[2] / down;
}

//------------------------------------------------------------------------------

int main()
try
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");

    reader();

    cout << "Ответ: " << a[2] << "\n";
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