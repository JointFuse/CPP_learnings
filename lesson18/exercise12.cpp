#include "Wampus.h"

using namespace Wampus_game;

void game_engine()
{
	while (true) try {
		Cave map{ difficulty() };
		char ch;
		while (true) try{
			map.player_action(info);
			std::cout << "Стрелять(s) или идти(m)?\n";
			std::cin >> ch;
			while (ch != 's' && ch != 'm' && ch != 'i')
				{ std::cin >> ch; }
			if (ch == 'i')	{ std::cout << map.state() << '\n'; }
			else			{ map.player_action(ch); }
		}
		catch (bad_input& err) {
			std::cout << "Ошибка: " << err.what() << std::endl;
			clear_stream(std::cin);
		}
	}
	catch (game_end& end) {
		std::cout << "\n\n\tИгра закончена!\n"
			<< end.what() << std::endl;
	}
}

int main()
try{
	setlocale(LC_ALL, "Russian");

	std::cout << "Местные жители жаловались на ужасного монстра - Вампуса, обитающего\n"
			  << "в окрестных пещерах, соединенных тоннелями. Пойду разберусь с ним!\n"
			  << "Надо быть внимательнее, там водятся летучие мыши и можно не заметить\n"
			  << "пропасть в темноте. Возьму с собой волшебные стрелы, которые летят куда\n"
			  << "я им скажу. Говорят, монстра можно найти по запаху...\n\n"
			  << "[ Для управления стрелами вводите по три номера пещер через тире: x-x-x ]\n";

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