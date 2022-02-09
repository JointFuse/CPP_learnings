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
    void PrintAll();                // Вывод всех данных стека имен и значений
    void PrintDat();                // Вывод данных
    bool Save();                    // Добавление токена в стек
    void Delete();                  // Удаление токена из стека
private:
    vector<Name_value> Stack;       // Вектор токенов
};

//------------------------------------------------------------------------------

void Name_value_stack::PrintAll()
{
    cout << "\tИмя\tЗначение\n";
    for (Name_value i : Stack)                      // Перебор всех элементов стека
        cout << "\t" << i.Name << "\t" << i.Value << "\n";  // Вывод элемента стека через доступ к отдельным данным типа Name_value
}

void Name_value_stack::PrintDat()
{
    cout << "Введите имя или значение для вывода связанных данных\n";

    char ch;
    cin >> ch;

    switch (ch) {
    case '0': case '1': case '2': case'3': case '4': case '5': case '6': case '7': case '8': case '9':
    {
        cin.putback(ch);
        int val;
        cin >> val;
        cout << "Значение: " << val << " Имена:\n";

        bool b{ true };
        for (Name_value i : Stack)
            if (i.Value == val) {
                cout << "\t" << i.Name << "\n";
                if (b)  b = false;
            }
        if (b)   cout << "Имен с данным значением нет!\n";
    }break;
    case 'Q': case 'W': case 'E': case 'R': case 'T': case 'Y': case 'U': case 'I': case 'O': case 'P': case 'A': case 'S': case 'D': case 'F': case 'G':
    case 'H': case 'J': case 'K': case 'L': case 'Z': case 'X': case 'C': case 'V': case 'B': case 'N': case 'M': case 'Й': case 'Ц': case 'У': case 'К':
    case 'Е': case 'Н': case 'Г': case 'Ш': case 'Щ': case 'З': case 'Х': case 'Ъ': case 'Ё': case 'Ф': case 'Ы': case 'В': case 'А': case 'П': case 'Р':
    case 'О': case 'Л': case 'Д': case 'Ж': case 'Э': case 'Я': case 'Ч': case 'С': case 'М': case 'И': case 'Т': case 'Ь': case 'Б': case 'Ю':
    {
        cin.putback(ch);
        string name;
        cin >> name;
        cout << "Имя: " << name << " Значения:\n";

        bool b{ true };
        for (Name_value i : Stack)
            if (i.Name == name) {
                cout << "\t" << i.Value << "\n";
                if (b)   b = false;
            }
        if (b)   cout << "Значений с данным именем нет!\n";
    }break;
    default:
        string name;
        cin >> name;
        cout << "Введено не число или не имя с заглавной буквы\n";
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
    case 'H': case 'J': case 'K': case 'L': case 'Z': case 'X': case 'C': case 'V': case 'B': case 'N': case 'M': case 'Й': case 'Ц': case 'У': case 'К':
    case 'Е': case 'Н': case 'Г': case 'Ш': case 'Щ': case 'З': case 'Х': case 'Ъ': case 'Ё': case 'Ф': case 'Ы': case 'В': case 'А': case 'П': case 'Р':
    case 'О': case 'Л': case 'Д': case 'Ж': case 'Э': case 'Я': case 'Ч': case 'С': case 'М': case 'И': case 'Т': case 'Ь': case 'Б': case 'Ю':
    {
        cin.putback(ch);
        cin >> name;
    }break;
    default:
        cout << "Имя требуется вводить с заглавной буквы\n";
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
        cout << "Значение должно быть целым числом\n";
        return 1;
    }
}

void Name_value_stack::Delete()
{
    cout << "Введите имя или значение для удаления всех свяханных данных\n";

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
        if (b)   cout << "Имен с данным значением нет!\n";
    }break;
    case 'Q': case 'W': case 'E': case 'R': case 'T': case 'Y': case 'U': case 'I': case 'O': case 'P': case 'A': case 'S': case 'D': case 'F': case 'G':
    case 'H': case 'J': case 'K': case 'L': case 'Z': case 'X': case 'C': case 'V': case 'B': case 'N': case 'M': case 'Й': case 'Ц': case 'У': case 'К':
    case 'Е': case 'Н': case 'Г': case 'Ш': case 'Щ': case 'З': case 'Х': case 'Ъ': case 'Ё': case 'Ф': case 'Ы': case 'В': case 'А': case 'П': case 'Р':
    case 'О': case 'Л': case 'Д': case 'Ж': case 'Э': case 'Я': case 'Ч': case 'С': case 'М': case 'И': case 'Т': case 'Ь': case 'Б': case 'Ю':
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
        if (b)   cout << "Значений с данным именем нет!\n";
    }break;
    default:
        cin >> t.Name;
        cout << "Введено не число или не имя с заглавной буквы\n";
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

    cout << "Функции программы:\nДобавление нового элемента '+'\nУдаление '-'\nВывод всех данных 'p'\n"
        << "Вывод данных по имени или значению 'd'\nВыход '.'\nКакую функцию хотите выбрать?\n";

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
            error("Неизвестная функция программы!\n");
        }
        cout << "Какую функцию хотите выбрать?\n";
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