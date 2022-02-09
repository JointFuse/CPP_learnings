#include "std_lib_facilities.h"

//------------------------------------------------------------------------------

void numverb();

//------------------------------------------------------------------------------

int main()
try
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");
    while (cin) {
        numverb();
    }
}
catch (exception& e) {
    cerr << "ошибка: " << e.what() << '\n';
    keep_window_open();
    return 1;
}
catch (...) {
    cerr << "”упс: незнакомое исключение!\n";
    keep_window_open();
    return 2;
}

//------------------------------------------------------------------------------

void numverb()
{
    string nums;
    char ch;

    cin >> ch;
    switch (ch) {
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        cin.putback(ch);
        break;
    default:
        error("¬ведено не число!");
    }

    cin >> nums;
    cout << nums << " - это ";
    switch (nums.size()) {
    case 1:
        cout << nums[0] - '0' << " единицы\n";
        break;
    case 2:
        cout << nums[0] - '0' << " дес€тки "
            << nums[1] - '0' << " единицы\n";
        break;
    case 3:
        cout << nums[0] - '0' << " сотни "
            << nums[1] - '0' << " дес€тки "
            << nums[2] - '0' << " единицы\n";
        break;
    case 4:
        cout << nums[0] - '0' << " тыс€чи "
            << nums[1] - '0' << " сотни "
            << nums[2] - '0' << " дес€тки "
            << nums[3] - '0' << " единицы\n";
        break;
    default:
        error("“ребуетс€ ввести целое число до 4 цифр!");
    }
}