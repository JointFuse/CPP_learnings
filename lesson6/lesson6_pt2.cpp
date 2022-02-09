#include "std_lib_facilities.h"

//------------------------------------------------------------------------------

vector<string> conj{ "and", "or", "but" };
vector<string> noun{ "birds", "fish", "c++" };
vector<string> verb{ "rules", "fly", "swim" };
vector<string> article{ "the" };

//------------------------------------------------------------------------------

bool gen_noun()
{
    string buf;
    cin >> buf;
    bool b{ false };

    for (string i : noun)
        if (buf == i)
            return 0;
    for (string i : article)
        if (buf == i)
            b = true;
    if (b) {
        cin >> buf;
        for (string i : noun)
            if (buf == i)
                return 0;
    }
    return 1;
}

bool sentence()
{
    if (gen_noun())
        return 1;

    string buf;
    cin >> buf;

    bool b{ true };
    for (string i : verb)
        if (buf == i)
            b = false;
    if (b)
        return 1;
    return 0;
}

string dif_sent()
{
    if (sentence())
        return "���";

    string buf;
    cin >> buf;
    if (buf == ".")
        return "��";

    bool b{ true };
    for (string i : conj)
        if (buf == i)
            b = false;
    if (b)
        return "���";

    if (sentence())
        return "���";
    return "��";
}

//------------------------------------------------------------------------------

int main()
try
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");

    cout << dif_sent();
}
catch (exception& e) {
    cerr << "������: " << e.what() << '\n';
    keep_window_open();
    return 1;
}
catch (...) {
    cerr << "����: ���������� ����������!\n";
    keep_window_open();
    return 2;
}