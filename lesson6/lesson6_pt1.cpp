#include "std_lib_facilities.h"

//------------------------------------------------------------------------------

class Name_value {
public:
    string Name;                    // Name of token
    int Value;                      // Value of token
    Name_value(string st, int val)  // Make a token from a name and a value
        :Name(st), Value(val) { }
};

class Name_value_stack {
public:
    void PrintAll();                // ����� ���� ������ ����� ���� � ��������
    void PrintDat();                // ����� ������
    bool Save();                    // ���������� ������ � ����
    void Delete();                  // �������� ������ �� �����
private:
    vector<Name_value> Stack;       // ������ �������
};

//------------------------------------------------------------------------------

void Name_value_stack::PrintAll()
{
    cout << "\t���\t��������\n";
    for (Name_value i : Stack)                      // ������� ���� ��������� �����
        cout << "\t" << i.Name << "\t" << i.Value << "\n";  // ����� �������� ����� ����� ������ � ��������� ������ ���� Name_value
}

void Name_value_stack::PrintDat()
{
    cout << "������� ��� ��� �������� ��� ������ ��������� ������\n";

    char ch;
    cin >> ch;

    switch (ch) {
    case '0': case '1': case '2': case'3': case '4': case '5': case '6': case '7': case '8': case '9':
    {
        cin.putback(ch);
        int val;
        cin >> val;
        cout << "��������: " << val << " �����:\n";

        bool b{ true };
        for (Name_value i : Stack)
            if (i.Value == val) {
                cout << "\t" << i.Name << "\n";
                if (b)  b = false;
            }
        if (b)   cout << "���� � ������ ��������� ���!\n";
    }break;
    case 'Q': case 'W': case 'E': case 'R': case 'T': case 'Y': case 'U': case 'I': case 'O': case 'P': case 'A': case 'S': case 'D': case 'F': case 'G':
    case 'H': case 'J': case 'K': case 'L': case 'Z': case 'X': case 'C': case 'V': case 'B': case 'N': case 'M': case '�': case '�': case '�': case '�':
    case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�':
    case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�':
    {
        cin.putback(ch);
        string name;
        cin >> name;
        cout << "���: " << name << " ��������:\n";

        bool b{ true };
        for (Name_value i : Stack)
            if (i.Name == name) {
                cout << "\t" << i.Value << "\n";
                if (b)   b = false;
            }
        if (b)   cout << "�������� � ������ ������ ���!\n";
    }break;
    default:
        string name;
        cin >> name;
        cout << "������� �� ����� ��� �� ��� � ��������� �����\n";
    }
}

bool Name_value_stack::Save()
{
    char ch;
    string name;
    int val;
    cin >> ch;

    switch (ch) {
    case'.':
        return 0;
    case 'Q': case 'W': case 'E': case 'R': case 'T': case 'Y': case 'U': case 'I': case 'O': case 'P': case 'A': case 'S': case 'D': case 'F': case 'G':
    case 'H': case 'J': case 'K': case 'L': case 'Z': case 'X': case 'C': case 'V': case 'B': case 'N': case 'M': case '�': case '�': case '�': case '�':
    case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�':
    case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�':
    {
        cin.putback(ch);
        cin >> name;
    }break;
    default:
        cout << "��� ��������� ������� � ��������� �����\n";
        return 1;
    }
    cin >> ch;

    switch (ch) {
    case '0': case '1': case '2': case'3': case '4': case '5': case '6': case '7': case '8': case '9':
    {
        cin.putback(ch);
        cin >> val;
        Name_value t = Name_value(name, val);
        Stack.push_back(t);
        return 1;
    }
    default:
        cout << "�������� ������ ���� ����� ������\n";
        return 1;
    }
}

void Name_value_stack::Delete()
{
    cout << "������� ��� ��� �������� ��� �������� ���� ��������� ������\n";

    char ch;
    cin >> ch;
    Name_value t = Name_value("null", NULL);

    switch (ch) {
    case '0': case '1': case '2': case'3': case '4': case '5': case '6': case '7': case '8': case '9':
    {
        cin.putback(ch);
        int val;
        cin >> val;

        bool b{ true };
        for (int i = 0; i < Stack.size(); ++i) {
            t = Stack[i];
            if (t.Value == val) {
                Stack.erase(Stack.begin() + i);
                if (b)   b = false;
                --i;
            }
        }
        if (b)   cout << "���� � ������ ��������� ���!\n";
    }break;
    case 'Q': case 'W': case 'E': case 'R': case 'T': case 'Y': case 'U': case 'I': case 'O': case 'P': case 'A': case 'S': case 'D': case 'F': case 'G':
    case 'H': case 'J': case 'K': case 'L': case 'Z': case 'X': case 'C': case 'V': case 'B': case 'N': case 'M': case '�': case '�': case '�': case '�':
    case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�':
    case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�': case '�':
    {
        cin.putback(ch);
        string name;
        cin >> name;

        bool b{ true };
        for (int i = 0; i < Stack.size(); ++i) {
            t = Stack[i];
            if (t.Name == name) {
                Stack.erase(Stack.begin() + i);
                if (b)   b = false;
                --i;
            }
        }
        if (b)   cout << "�������� � ������ ������ ���!\n";
    }break;
    default:
        cin >> t.Name;
        cout << "������� �� ����� ��� �� ��� � ��������� �����\n";
    }
}

//------------------------------------------------------------------------------

Name_value_stack stk;

//------------------------------------------------------------------------------

int main()
try
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");

    cout << "������� ���������:\n���������� ������ �������� '+'\n�������� '-'\n����� ���� ������ 'p'\n"
        << "����� ������ �� ����� ��� �������� 'd'\n����� '.'\n����� ������� ������ �������?\n";

    char ch;
    while (cin >> ch) {
        switch (ch) {
        case '+':
            while (stk.Save());
            break;
        case '-':
            stk.Delete();
            break;
        case 'p':
            stk.PrintAll();
            break;
        case 'd':
            stk.PrintDat();
            break;
        case'.':
            return 1;
        default:
            error("����������� ������� ���������!\n");
        }
        cout << "����� ������� ������ �������?\n";
    }
    keep_window_open();
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