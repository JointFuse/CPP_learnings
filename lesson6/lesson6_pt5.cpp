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
    cerr << "������: " << e.what() << '\n';
    keep_window_open();
    return 1;
}
catch (...) {
    cerr << "����: ���������� ����������!\n";
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
        error("������� �� �����!");
    }

    cin >> nums;
    cout << nums << " - ��� ";
    switch (nums.size()) {
    case 1:
        cout << nums[0] - '0' << " �������\n";
        break;
    case 2:
        cout << nums[0] - '0' << " ������� "
            << nums[1] - '0' << " �������\n";
        break;
    case 3:
        cout << nums[0] - '0' << " ����� "
            << nums[1] - '0' << " ������� "
            << nums[2] - '0' << " �������\n";
        break;
    case 4:
        cout << nums[0] - '0' << " ������ "
            << nums[1] - '0' << " ����� "
            << nums[2] - '0' << " ������� "
            << nums[3] - '0' << " �������\n";
        break;
    default:
        error("��������� ������ ����� ����� �� 4 ����!");
    }
}