#include "Wampus.h"

using namespace Wampus_game;

void game_engine()
{
	while (true) try {
		Cave map{ difficulty() };
		char ch;
		while (true) try{
			map.player_action(info);
			std::cout << "��������(s) ��� ����(m)?\n";
			std::cin >> ch;
			while (ch != 's' && ch != 'm' && ch != 'i')
				{ std::cin >> ch; }
			if (ch == 'i')	{ std::cout << map.state() << '\n'; }
			else			{ map.player_action(ch); }
		}
		catch (bad_input& err) {
			std::cout << "������: " << err.what() << std::endl;
			clear_stream(std::cin);
		}
	}
	catch (game_end& end) {
		std::cout << "\n\n\t���� ���������!\n"
			<< end.what() << std::endl;
	}
}

int main()
try{
	setlocale(LC_ALL, "Russian");

	std::cout << "������� ������ ���������� �� �������� ������� - �������, ����������\n"
			  << "� ��������� �������, ����������� ���������. ����� ��������� � ���!\n"
			  << "���� ���� ������������, ��� ������� ������� ���� � ����� �� ��������\n"
			  << "�������� � �������. ������ � ����� ��������� ������, ������� ����� ����\n"
			  << "� �� �����. �������, ������� ����� ����� �� ������...\n\n"
			  << "[ ��� ���������� �������� ������� �� ��� ������ ����� ����� ����: x-x-x ]\n";

	game_engine();

	return 0;
}
catch (std::exception& e) {
	std::cout << "Exception: " << e.what() << std::endl;
	return 1;
}
catch (...) {
	std::cout << "Unknown error!" << std::endl;
	return 2;
}