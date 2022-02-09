#include "std_lib_facilities.h"

bool isnew{ false };
vector<bool> bulls(4);
vector<bool> cows(4);
vector<int> numb(4);

class engine_error {};
class setrand_error{};

void engine();
void setrand();

int main()
try {
	setlocale(LC_ALL, "Russian");
	system("chcp 1251");

	char c;
	bool b{ true };

	while (b) {
		c = ' ';
		setrand();
		engine();
		cout << "������� ��� ���? (y/n)\n";
		while ((c != 'y') && (c != 'n')) {
			cout << "y/n?\n";
			cin >> c;
		}
		if (c == 'n') b = false;
	}
}
catch (engine_error) {
	cerr << "������: �� ����� �� �����\n";
	engine();
}
catch (setrand_error) {
	cerr << "������: ����� ������ ���� ������ 0\n";
	setrand();
}

void engine()
/*������ ����, �������� �������� 4 �����,
  ���� �� ���� ��������� �� �����,
  ������� ������� ���������� � �������
  � �������� ������� ������*/
{
	if (!isnew) {								//���������� ���������� isnew ��������� �������� true
		for (int i = 0; i < 4; ++i) {			//����� ��������� ������������� ���� ������ � ����� ������� ����
			bulls[i] = false;					//�������� false ������������ ����� ����, ��� ������������ ������ �����
			cows[i] = false;
		}
		numb[0] = rand() % 9;
		numb[1] = rand() % 9;
		numb[2] = rand() % 9;
		numb[3] = rand() % 9;
		isnew = true;
	}

	while (isnew) {
		cout << "������� 4 �����\n";
		vector<int> user(4);

		for (int i = 0; i < 4; ++i) {
			//cout << "������� " << i + 1 << " �����\n";
			cin >> user[i];
			if ((user[i] < 0) || (user[i] > 9)) throw engine_error();			//�������� ��������� �����
		}

		for (int i = 0; i < 4; ++i)
			if (numb[i] == user[i]) bulls[i] = true;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				if ((numb[i] == user[j]) && (bulls[j] != true) && (bulls[i] != true)) cows[j] = true;

		if ((bulls[0] == true) && (bulls[1] == true) && (bulls[2] == true) && (bulls[3] == true)) isnew = false;
		else {
			int count{ 0 };
			for (bool i : bulls)
				if (i) ++count;
			cout << "�����: " << count;
			count = 0;
			for (bool i : cows)
				if (i) ++count;
			cout << " �����: " << count << "\n";
			for (int i = 0; i < 4; ++i) {								//����� ������ ���������� � ����� � �������
				bulls[i] = false;										//�������� �������� ��������
				cows[i] = false;
			}
		}
	}

	cout << "���, �� �������� �����!\n";
}

void setrand()
/*��������� ������� �����
 ��� ������� ������������,
 �������� ����� ������
 ���� �������������*/
{
	cout << "������� ����� �����\n";
	int n;
	cin >> n;
	if (n < 0) throw setrand_error();
	srand(n);
}