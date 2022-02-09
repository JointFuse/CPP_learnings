#include "Wampus.h"
#include <random>
#include <sstream>
#include <chrono>

using namespace Wampus_game;
using milliseconds = std::chrono::duration<long long, std::ratio<1, 1000>>;
//-----------------------------------------------------------

inline std::default_random_engine& get_rand()
{
	static std::default_random_engine ran;	// note: not thread_local
	return ran;
};

inline void seed_randint(int s) { get_rand().seed(s); }

inline int randint(int min, int max) { return std::uniform_int_distribution<>{min, max}(get_rand()); }

inline int randint(int max) { return randint(0, max); }


//-----------------------------------------------------------

void Wampus_game::clear_stream(std::istream& is)
{
	is.clear();
	std::string ss;
	is >> ss;
	std::cout << "[ ������, �� ���������� � ������, ��� ���������:  ]\n"
			  << "[ ��� ������ �������� ��� ����������� ������� - m ]\n"
			  << "[ ��� �������� �� ���� ������� - s                ]\n"
			  << "[ � ��������� ������� ��������� ������� �����:    ]\n"
			  << "[ ���� ������ �����, � ������� ���� ������� ��    ]\n"
			  << "[ ����� ������, ���� ������� ��������� �� 1 �� 5  ]\n"
			  << "[ ��� �������� �� ���� ������� ��������� �������: ]\n"
			  << "[ ����� - ����� - �����.     �� ����� ������!     ]\n";
}

//-----------------------------------------------------------

int Wampus_game::difficulty()
{
	std::cout << "\n\t�������� ���������(1-5)\n";
	int diff{NULL};
	std::cin >> diff;
	while (diff < 1 || 5 < diff) {
		std::cin >> diff;
		if (std::cin.rdstate())
			{ clear_stream(std::cin); }
	}
	switch (diff) {
	case 1:
		return 16;
	case 2:
		return 20;
	case 3:
		return 26;
	case 4:
		return 32;
	case 5:
		return 42;
	default:
		throw bad_input("������������ ���� ������ ���������");
	}
}

//-----------------------------------------------------------

int Room::untracted()
{
	for(int i{0}; i < doors.size(); ++i)
		if(doors[i] == -1) { return i; }
	return -1;
}

bool Room::has_tun(int n)
{
	for(int i : doors)
		if (i == n) 
			{ return true; }
	return false;
}

//-----------------------------------------------------------

Cave::Cave(int n)
	: rooms{ n }
{
	if (n % 2 != 0 || n < 12) { throw bad_input("bad room number"); }
	luck -= n / 10 * 20;
	seed_rooms();
	seed_podlyanka('w');
	for (int i{ n / 10 }; i > 0; --i) 
		{ seed_podlyanka('b'); }
	for (int i{ n / 20 == 0 ? 1 : n / 20 }; i > 0; --i)
		{ seed_podlyanka('p'); }

	pl_rm = randint(n - 1);
	player = rooms[pl_rm];
	while (player.bat || player.pit || player.wampus) { 
		pl_rm = player.doors[randint(2)]; 
		player = rooms[pl_rm]; 
	}

	std::cout << "� ��������� " << n << " �����"
			  << (n > 26 ? "�" : "") << "\n";
}

void Cave::seed_rooms()
{
	milliseconds delay{100};
	int i;
	int j;
	while ((i = untracted()) != -1) try{
		j = randint(0, rooms.size() - 1);
		auto start = std::chrono::steady_clock::now();
		while(i == j || rooms[i].has_tun(j) ||
			  rooms[j].untracted() == -1) {
			  if (std::chrono::steady_clock::now() > start + delay)
				{ throw bad_rand(); }
			  j = randint(0, rooms.size() - 1);
		}
		rooms[i].doors[rooms[i].untracted()] = j;
		rooms[j].doors[rooms[j].untracted()] = i;
	}
	catch(bad_rand) {
		if (rooms[i].untracted() < 2) {
			for (int jj{ 0 }; jj < rooms.size(); ++jj) {
				bool done{ false };
				for (int& d : rooms[jj].doors) {
					if (rooms[i].has_tun(jj) || i == jj)
						{ continue;	}
					else {
						rooms[i].doors[rooms[i].untracted()] = jj;
						for (int& swd : rooms[d].doors)
							if (swd == jj) { swd = -1; }
						d = i; done = true;
						break;
					}
				}
				if (done) { break; }
			}
		}
		else {
			rooms[i].doors[2] = 0;
			j = untracted();
			rooms[i].doors[2] = j;
			rooms[j].doors[rooms[j].untracted()] = i;
		}

		static int seed{0};
		seed *= ++seed * 3 / 2;
		seed_randint(seed);
	}
}

void Cave::seed_podlyanka(char ch)
{
	int n = randint(rooms.size() - 1);
	while (rooms[n].wampus || rooms[n].bat || rooms[n].pit)
		{ n = randint(rooms.size() - 1); }

	switch (ch) {
	case 'w':
		rooms[n].wampus = true;
		break;
	case 'b':
		rooms[n].bat = true;
		break;
	case 'p':
		rooms[n].pit = true;
		break;
	default:
		break;
	}
}

int Cave::untracted()
{
	for (int i{0}; i < rooms.size(); ++i)
		for (int d : rooms[i].doors)
			if (d == -1) { return i; }
	return -1;
}

void Cave::run_to(int n)
{
	pl_rm = n;
	player = rooms[n];

	if (player.pit) throw game_end("[ �� ����� � ���������� �������� ��� ]");
	if (player.wampus && !dead_bat) throw game_end("[ �� �������� ������� � ���� ������� ������ ]");
	if (player.wampus && dead_bat) {
		std::cout << "[ �� �������� �������, �� � ��� ���� ���� ������� ���� ]\n"
				  << "[ � �� ������ �������, ������ ���� ������� ]\n"
				  << "- �� �����, ��� �� ��� ��...\n";
		--dead_bat;
		int old_rm{pl_rm};
		run_to(player.doors[randint(2)]);
		int new_rm{pl_rm};
		while (new_rm == pl_rm || new_rm == old_rm)
			{ new_rm = randint(0, rooms.size() - 1); }
		rooms[old_rm].wampus = false;
		rooms[new_rm].wampus = true;
		return;
	}
	if (player.bat) {
		std::cout << "[ �������� ������� ���� ��������� ��� � ������ ������ ]\n"
				  << "- ������ ���� �� �����\n";
		run_to(randint(rooms.size() - 1));
	}
	if (player.arrow) {
		std::cout << "- ������� ��� ��� ������, ����� �����!\n"
				  << "[ ����� = " << luck << "% ]\n";
		++arrows;
		rooms[pl_rm].arrow = false;
	}
	if (player.dead_bat) {
		std::cout << "- ������� ������� ����, ����� �����������...\n";
		++dead_bat;
		rooms[pl_rm].dead_bat = false;
	}
}

void Cave::arrow_fly(int n)
{
	if (rooms[n].wampus) throw game_end("- � ���� �������!\n[ ������ �� �� ����� �������� ������ ����� � ������� ������ ]");
	if (rooms[n].bat) {
		std::cout << "- �����-�� ����! ������ � � ����-�� �����...\n";
		rooms[n].bat = false;
		rooms[n].dead_bat = true;
	}
	for (int d : rooms[n].doors)
		if (rooms[d].wampus) {
			std::cout << "[ ����������� ������� � ������ ]\n"
					  << "- ����, ������ ������ ��������� �������,\n"
					  << "�������� ����� �������� �������\n";
			rooms[d].wampus = false;
			int new_rm = rooms[d].doors[randint(2)];
			if (new_rm == pl_rm) throw game_end("- �������, ����� � ������� ���� ������!!!\n[ ������ � ��������� ������� �� ��� ]");
			rooms[new_rm].wampus = true;
		}
}

std::string Cave::state()
{
	std::ostringstream info;
	int n{ -1 };
	for (Room r : rooms) {
		++n;
		info << "Room �" << n + 1 << ".\n"
			 << "Doors to: ";
		for(int i : r.doors)
			info << i + 1 << ' ';
		info << "\n" << (r.wampus ? "Wampus here.\n" : "")
			 << (r.bat ? "Bat here.\n" : "")
			 << (r.pit ? "Pit here.\n" : "")
			 << (r.arrow ? "Arrow here\n" : "")
			 << (r.dead_bat ? "Meat here\n" : "");
		info << '\n';
	}

	info << "Player room: " << pl_rm + 1 
		 << "\n�� ������ ����������?\n";

	return info.str();
}

void Cave::player_check()
{
	std::cout << "\n������ � " << pl_rm + 1 << '\n'
			  << "����� - " << arrows << '\n'
			  << (dead_bat > 0 ? "� ���� ���� ����!\n" : "")
			  << "������� � ������ �";
	for (int i : player.doors)
		std::cout << ' ' << i + 1;
	std::cout << '\n';

	for (int i : player.doors) {
		if (rooms[i].bat)
			std::cout << "- ����� ������ �������!\n";
		if (rooms[i].pit)
			std::cout << "- �������� ���������!\n";
		if (rooms[i].wampus)
			std::cout << "- �������������� ����!\n";
	}
}

void Cave::player_action(char ch)
{
	switch (ch) {
	case info:
		player_check();
		break;
	case move:
		player_move();
		break;
	case shoot:
		player_shoot();
		break;
	default:
		throw bad_input("������������ ����� ��������");
	}
}

void Cave::player_move()
{
	std::cout << "��� � ������ - ";
	int r{ NULL };
	while (true) {
		std::cin >> r;
		if (std::cin.rdstate())	
			{ throw bad_input("������������ ���� ������ ������"); }
		if (!player.has_tun(r - 1)) { 
			std::cout << "��� � ������ - "; 
			continue; 
		}
		run_to(r - 1);
		std::cout << "\n";
		break;
	}
}

void Cave::player_shoot()
{
	if (!arrows) {
		std::cout << "- � ���� ����������� ������,\n"
				  << "����� ��������� ����� ������������...\n";
		return;
	}
	std::cout << "������� ����� ��� ������ - ";
	char ch1{ ' ' }, ch2{ ' ' };
	int cave[] = { NULL, NULL, NULL };
	while (ch1 != '-' && ch2 != '-') {
		std::cin >> cave[0] >> ch1 >> cave[1] >> ch2 >> cave[2];
		if (std::cin.rdstate())
			{ throw bad_input("������������ ���� ���� ������"); }
		for (int i{ 0 }; i < 3; ++i) {
			--cave[i];
			if (rooms.size() <= cave[i] || cave[i] < 0)
				{ ch1 = ' '; }
		}
	}
	--arrows;
	Room arr_room = player;
	for (int i{ 0 }; i < 3; ++i) {
		bool missed{ true };
		for (int d : arr_room.doors)
			if (cave[i] == d) { missed = false; }
		if (missed) {
			std::cout << "- � ������ � ������� ������ � ��� ����-�� �������...\n";
			if (luck > randint(100)) {
				std::cout << "[ ������ ��������� ��� ���� � ������ �";
				if(!i)	{ rooms[pl_rm].arrow = true; std::cout << pl_rm + 1 << " ]\n"; }
				else	{ rooms[cave[i - 1]].arrow = true; std::cout << cave[i - 1] + 1 << " ]\n"; }
			}
			break;
		}
		arrow_fly(cave[i]);
		arr_room = rooms[cave[i]];
	}
}

//-----------------------------------------------------------

std::ostream& Wampus_game::operator<< (std::ostream& os, Cave& cv)
{
	return os << cv.state();
}

//-----------------------------------------------------------
