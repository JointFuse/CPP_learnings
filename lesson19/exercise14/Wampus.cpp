#include "Wampus.h"
#include <FL/Fl_Button.H>
#include <sstream>
#include <chrono>

using namespace Wampus_game;
using milliseconds = std::chrono::duration<long long, std::ratio<1, 1000>>;

//-----------------------------------------------------------
/*
inline std::default_random_engine& get_rand()
{
	static std::default_random_engine ran;	// note: not thread_local
	return ran;
};

inline void seed_randint(int s) { get_rand().seed(s); }

inline int randint(int min, int max) { return std::uniform_int_distribution<>{min, max}(get_rand()); }

inline int randint(int max) { return randint(0, max); }
*/

vector<string> string_to_vec(string ss)
{
	vector<string> ret(1);
	for (int i{ 0 }; i < ss.size(); ++i) {
		if (ss[i] == '\n') {
			if (i == ss.size() - 1)
				break;
			ret.push_back("");
			continue;
		}
		ret[ret.size() - 1] += ss[i];
	}
	return ret;
}

void notdigitindicate(string check, Graph_lib::Shape& indicator, Graph_lib::Window& win)
{
	if (check.size() == 0)
		{ win.attach(indicator); return; }
	for (char ch : check)
		if (ch < -1 || !isdigit(ch))
			{ win.attach(indicator); return; }
	win.detach(indicator);
}

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

	if (n < 20)
		{ dead_bat = 1; }

	pl_rm = randint(n - 1);
	player = rooms[pl_rm];
	while (player.bat || player.pit || player.wampus) { 
		pl_rm = player.doors[randint(2)]; 
		player = rooms[pl_rm]; 
	}

	//std::cout << "� ��������� " << n << " �����"
	//		  << (n > 26 ? "�" : "") << "\n";
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

string Cave::run_to(int n)
{
	stringstream mess;
	pl_rm = n;
	player = rooms[n];

	if (player.pit) throw game_end("�� ���������!\n[ �� ����� � ���������� �������� ��� ]");
	if (player.wampus && !dead_bat) throw game_end("�� ���������!\n[ �� �������� ������� � ���� ������� ������ ]");
	if (player.wampus && dead_bat) {
		mess << "[ �� �������� �������, �� � ��� ���� ���� ������� ���� ]\n"
			 << "[ � �� ������ �������, ������ ���� ������� ]\n"
			 << "- �� �����, ��� �� ��� ��...\n";
		--dead_bat;
		int old_rm{pl_rm};
		try {
			mess << run_to(player.doors[randint(2)]);
		}
		catch (game_end& gg) {
			throw game_end(mess.str() + gg.what());
		}
		int new_rm{pl_rm};
		while (new_rm == pl_rm || new_rm == old_rm)
			{ new_rm = randint(0, rooms.size() - 1); }
		rooms[old_rm].wampus = false;
		rooms[new_rm].wampus = true;
		return mess.str();
	}
	if (player.bat) {
		mess << "[ �������� ������� ���� ��������� ��� � ������ ������ ]\n"
			 << "- ������ ���� �� �����\n";
		try {
			mess << run_to(randint(rooms.size() - 1));
		}
		catch (game_end& gg) {
			throw game_end(mess.str() + gg.what());
		}
		
	}
	if (player.arrow) {
		mess << "- ������� ��� ��� ������, ����� �����!\n"
			 << "[ ����� = " << luck << "% ]\n";
		++arrows;
		rooms[pl_rm].arrow = false;
	}
	if (player.dead_bat) {
		mess << "- ������� ������� ����, ����� �����������...\n";
		++dead_bat;
		rooms[pl_rm].dead_bat = false;
	}
	return mess.str();
}

string Cave::arrow_fly(int n)
{
	stringstream mess;
	if (rooms[n].wampus) throw game_end("�� ��������!\n- � ���� �������!\n[ ��� ���� �� ��� �� � ������, ��? ]");
	if (rooms[n].bat) {
		mess << "- �����-�� ����! ������ � � ����-�� �����...\n";
		rooms[n].bat = false;
		rooms[n].dead_bat = true;
	}
	for (int d : rooms[n].doors)
		if (rooms[d].wampus) {
			mess << "[ ����������� ������� � ������ ]\n"
				 << "- ����, ������ ������ ��������� �������, ��������\n"
				 << "����� �������� �������\n";
			rooms[d].wampus = false;
			int new_rm = rooms[d].doors[randint(2)];
			if (new_rm == pl_rm) throw game_end(mess.str() + "�� ���������!\n- �������, ����� � ������� ���� ������!!!\n[ ������ � ��������� ������� �� ��� ]");
			rooms[new_rm].wampus = true;
		}
	return mess.str();
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

vector<bool> Cave::player_check() const
{
	/*std::cout << "\n������ � " << pl_rm + 1 << '\n'
			    << "����� - " << arrows << '\n'
			    << (dead_bat > 0 ? "� ���� ���� ����!\n" : "")
			    << "������� � ������ �";
	for (int i : player.doors)
		std::cout << ' ' << i + 1;
	std::cout << '\n';
	*/
	vector<bool> state(3);
	for (int i : player.doors) {
		if (rooms[i].bat)
			state[2] = state[2] || true;//std::cout << "- ����� ������ �������!\n";
		else
			state[2] = state[2] || false;
		if (rooms[i].pit)
			state[1] = state[1] || true;//std::cout << "- �������� ���������!\n";
		else
			state[1] = state[1] || false;
		if (rooms[i].wampus)
			state[0] = state[0] || true;//std::cout << "- �������������� ����!\n";
		else 
			state[0] = state[0] || false;
	}
	return state;
}

void Cave::player_action(char ch)
{
	switch (ch) {
	case info:
		player_check();
		break;
	case move:
		player_move(0);
		break;
	case shoot:
		player_shoot({0, 0, 0});
		break;
	default:
		throw bad_input("������������ ����� ��������");
	}
}

void Cave::player_move(int way)
{
	//std::cout << "��� � ������ - ";
	/*int r{NULL};
	while (true) {
		std::cin >> r;
		if (std::cin.rdstate())	
			{ throw bad_input("������������ ���� ������ ������"); }
		if (!player.has_tun(r - 1)) { 
			//std::cout << "��� � ������ - "; 
			continue; 
		}
		run_to(r - 1);
		//std::cout << "\n";
		break;
	}*/
	string mess(run_to(player.doors[way]));
	if (mess.size() != 0) { throw event(mess); }
}

void Cave::player_shoot(vector<int> cave)
{
	stringstream mess;
	if (!arrows) {
		mess << "- � ���� ����������� ������, �����\n"
			 << "��������� ����� ������������...\n";
		throw event(mess.str());
	}
	//std::cout << "������� ����� ��� ������ - ";
	/*char ch1{' '}, ch2{' '};
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
	}*/
	--arrows;
	Room arr_room = player;
	for (int i{ 0 }; i < 3; ++i) {
		bool missed{ true };
		for (int d : arr_room.doors)
			if (cave[i] == d) { missed = false; }
		if (missed) {
			mess << "- � ������ � ������� ������ � ������ ����-�� �������...\n";
			if (luck > randint(100)) {
				//mess << "[ ������ ��������� ��� ���� � ������ �";
				if(!i)	{ rooms[pl_rm].arrow = true; mess << run_to(pl_rm);/*pl_rm + 1 << " ]\n"; */ }
				else	{ rooms[cave[i - 1]].arrow = true; mess << "[ ������ ��������� ��� ���� � ������ �" << cave[i - 1] + 1 << " ]\n"; }
			}
			break;
		}
		mess << arrow_fly(cave[i]);
		arr_room = rooms[cave[i]];
	}
	if (mess.str().size() != 0)
		throw event(mess.str());
}

vector<vector<int>> Cave::topology() const
{
	vector<vector<int>> ret{rooms.size()};
	for (int i{ 0 }; i < rooms.size(); ++i)
		for (int j{0}; j < rooms[i].doors.size(); ++j)
			ret[i].push_back(rooms[i].doors[j]);
	return ret;
}

//-----------------------------------------------------------

std::ostream& Wampus_game::operator<< (std::ostream& os, Cave& cv)
{
	return os << cv.state();
}

//-----------------------------------------------------------

Cave_mark::Cave_mark(Point center, int n)
{
	add_shape(new Regular_polygon(center, 3, mrk_rad));
	ostringstream ss;
	ss << n;
	add_shape(new Graph_lib::Text(center, ss.str()));
	add_shape(new Graph_lib::Mark((*this)[0].point(1), '�'));
	add_shape(new Graph_lib::Mark((*this)[0].point(2), '�'));
	add_shape(new Graph_lib::Mark((*this)[0].point(0), '�'));
	(*this)[0].set_color(body_c);
	(*this)[0].set_fill_color(body_c);
	(*this)[2].set_color(danger_c);
	(*this)[3].set_color(danger_c);
	(*this)[4].set_color(warning_c);
	(*this)[1].move(12, -4);
	(*this)[2].move(-11, -4);
	(*this)[3].move(11, -4);
	(*this)[4].move(-1, 16);
	hide();
}

void Cave_mark::mark_set(Mark m)
{
	if ((*this)[m].color().visibility() == Graph_lib::Color::visible)
		(*this)[m].set_color(Graph_lib::Color::invisible);
	else
		(*this)[m].set_color(3 < m ? warning_c : danger_c);
}

void Cave_mark::show()
{
	(*this)[0].set_color(body_c);
	(*this)[0].set_fill_color(body_c);
	(*this)[1].set_color(num_c);
}

void Cave_mark::hide()
{
	for (int i{ 0 }; i < this->size(); ++i)
		(*this)[i].set_color(Graph_lib::Color::invisible);
	for (int i{ 0 }; i < this->size(); ++i)
		(*this)[i].set_fill_color(Graph_lib::Color::invisible);
}

bool Cave_mark::visible()
{
	if ((*this)[0].color().visibility() == Graph_lib::Color::visible)
		{ return true; }
	return false;
}

void Cave_mark::on()
{
	body_c = Graph_lib::Color::dark_green;
	show();
}

void Cave_mark::off()
{
	body_c = Graph_lib::Color::cyan;
	show();
}

//-----------------------------------------------------------

Map::Map(Graph_lib::Window& win, int rnum, int xofs, int yofs,
		 int xlen, int ylen, vector<vector<int>> topology, const int& pl_room)
	: rooms{ topology }, pl_rm{pl_room}
{
	map_width = int(sqrt(rooms.size())) + (int(sqrt(rooms.size())) % 10 == 0 ? 0 : 1);
	int ystep = ylen / (rnum / map_width + (rnum % map_width == 0 ? 0 : 1));
	int xstep = xlen / map_width;
	for (int i{ 0 }; i < rnum; ++i) {
		if (i != 0 && i % map_width == 0)
			{ yofs += ystep; }
		marks.push_back(new Cave_mark({xofs + xstep * (i % map_width) + int(pow(-1, randint(1))) * randint(5,10),
									   yofs + int(pow(-1, randint(1))) * randint(5,10) }, i + 1));
	}
	for (int i{ 0 }; i < rnum * 3 / 2; ++i) {
		for (int j{0}; j < rooms.size(); ++j)
			for (int jj{0}; jj < rooms[j].size(); ++jj)
				if (has_tunel(j, rooms[j][jj]) == -1) {
					tunels.push_back(new Graph_lib::Line(marks[j].center(), 
														 marks[rooms[j][jj]].center()));
					win.attach(tunels[tunels.size() - 1]);
				}
	}
	for (int i{ 0 }; i < tunels.size(); ++i) {
		tunels[i].set_style(Graph_lib::Line_style(Graph_lib::Line_style::dash, 1));
		tunels[i].set_color(Graph_lib::Color::invisible);
	}
	for (int i{0}; i < marks.size(); ++i)
		win.attach(marks[i]);
}

int Map::has_tunel(int r1, int r2)
{
	Point p1 = marks[r1].center();
	Point p2 = marks[r2].center();
	for (int i{0}; i < tunels.size(); ++i)
		if ((tunels[i].point(0) == p1 || tunels[i].point(0) == p2)&&
			(tunels[i].point(1) == p1 || tunels[i].point(1) == p2))
			{ return i; }
	return -1;
}

void Map::light_off()
{
	if (light_rm != -1)
		marks[light_rm].off();
}

void Map::light_on()
{
	marks[pl_rm].on();
}

void Map::show_neighbor()
{
	int prev_rm = light_rm;
	for (int i{ 0 }; i < rooms[pl_rm].size(); ++i)
		tunels[has_tunel(pl_rm, rooms[pl_rm][i])].set_color(Graph_lib::Color::black);
	for (int i{ 0 }; i < rooms[pl_rm].size(); ++i) {
		light_rm = rooms[pl_rm][i];
		light_off();
	}
	light_rm = prev_rm;
}

void Map::light_player()
{
	light_off();
	show_neighbor();
	light_on();
	light_rm = pl_rm;
}

//-----------------------------------------------------------

Main_menu::Main_menu(Point xy)
	: Window({xy.x - 75 < 0 ? xy.x : xy.x - 75, xy.y - 107 < 0 ? xy.y : xy.y - 107}, 150, 215, "Main menu"),
	screen_center(xy),
	t_name({Frame, Frame}, "Wampus V2.0"), t_diff({Frame + 23, Frame}, "difficulty"),
	b_start({Frame, Frame + 10}, x_max() - 2 * Frame, ButHeight, "START", cb_start),
	b_exit({Frame, Frame + ButHeight + 10}, x_max() - 2 * Frame, ButHeight, "EXIT", cb_exit),
	b_diff1({Frame, Frame + 10}, x_max() - 2 * Frame, ButHeight, "first time", cb_diff1),
	b_diff2({Frame, Frame + ButHeight + 10}, x_max() - 2 * Frame, ButHeight, "simple easy", cb_diff2),
	b_diff3({Frame, Frame + ButHeight * 2 + 10}, x_max() - 2 * Frame, ButHeight, "gold mid", cb_diff3),
	b_diff4({Frame, Frame + ButHeight * 3 + 10}, x_max() - 2 * Frame, ButHeight, "regular hard", cb_diff4),
	b_diff5({Frame, Frame + ButHeight * 4 + 10}, x_max() - 2 * Frame, ButHeight, "definitely hell", cb_diff5)
{
	attach(t_name);
	attach(b_start);
	attach(b_exit);
	attach(b_diff1);
	b_diff1.hide();
	attach(b_diff2);
	b_diff2.hide();
	attach(b_diff3);
	b_diff3.hide();
	attach(b_diff4);
	b_diff4.hide();
	attach(b_diff5);
	b_diff5.hide();
}

void Main_menu::show_main()
{
	detach(t_diff);
	b_diff1.hide();
	b_diff2.hide();
	b_diff3.hide();
	b_diff4.hide();
	b_diff5.hide();
	attach(t_name);
	b_start.show();
	b_exit.show();
}

void Main_menu::show_diff()
{
	detach(t_name);
	b_start.hide();
	b_exit.hide();
	attach(t_diff);
	b_diff1.show();
	b_diff2.show();
	b_diff3.show();
	b_diff4.show();
	b_diff5.show();
}

void Main_menu::game_start(int diff)
{
	static Game_menu* game{nullptr};
	show_main();
	if (new_game) {
		if (game != nullptr)
			{ delete game; }
		game = new Game_menu(screen_center, diff, this);
		new_game = false;
	}
	game->set_label("���� �������!");
	game->show();
	game->resize(gm_xlen - 7, gm_ylen - 7);
	hide();
}

//-----------------------------------------------------------

Game_menu::Game_menu(Point xy, int diff, Main_menu* back)
	: Window({ xy.x - gm_xlen / 2 < 0 ? xy.x : xy.x - gm_xlen / 2 , xy.y - gm_ylen / 2 < 0 ? xy.y : xy.y - gm_ylen / 2 }, gm_xlen, gm_ylen, "���� �������!"),
	descript(back), engine(diff), graphic(*this, diff, map_xofs, map_yofs, map_xlen, map_ylen, engine.topology(), engine.player_rm()),
	warn_rec1({ x_max() - Frame - gm_boxlen * 3, Frame + gm_boxhgt * 7 + gm_ledhgt }, { x_max() - Frame - gm_boxlen * 2, Frame + gm_boxhgt * 8 + gm_ledhgt }),
	warn_rec2({ x_max() - Frame - gm_boxlen * 2, Frame + gm_boxhgt * 7 + gm_ledhgt }, { x_max() - Frame - gm_boxlen * 1, Frame + gm_boxhgt * 8 + gm_ledhgt }),
	warn_rec3({ x_max() - Frame - gm_boxlen * 1, Frame + gm_boxhgt * 7 + gm_ledhgt }, { x_max() - Frame - gm_boxlen * 0, Frame + gm_boxhgt * 8 + gm_ledhgt }),
	t_goto({ x_max() - Frame - gm_boxlen * 3, Frame + gm_boxhgt * 1 + gm_ledhgt - 10 }, "���� �:"),
	t_nums({ x_max() - Frame - gm_boxlen * 3, Frame + gm_boxhgt * 7 + gm_ledhgt - 5 }, "���� ������:"),
	led_wum({ x_max() - Frame - 90, Frame }, "������!"),
	led_pit({ x_max() - Frame - 90, Frame + 50 }, "���!"),
	led_bat({ x_max() - Frame - 90, Frame + 100 }, "����! "),
	out_arrows({ x_max() - Frame - gm_boxlen, Frame + gm_boxhgt * 6 + gm_ledhgt - 22 }, gm_boxlen, gm_boxhgt, "������:"),
	out_meat({ x_max() - Frame - gm_boxlen, Frame + gm_boxhgt * 5 + gm_ledhgt - 22 }, gm_boxlen, gm_boxhgt, "����:"),
	out_way1({ x_max() - Frame - gm_boxlen * 2, Frame + gm_boxhgt * 1 + gm_ledhgt }, gm_boxlen, gm_boxhgt, ""),
	out_way2({ x_max() - Frame - gm_boxlen * 2, Frame + gm_boxhgt * 2 + gm_ledhgt }, gm_boxlen, gm_boxhgt, ""),
	out_way3({ x_max() - Frame - gm_boxlen * 2, Frame + gm_boxhgt * 3 + gm_ledhgt }, gm_boxlen, gm_boxhgt, ""),
	in_aim1({ x_max() - Frame - gm_boxlen * 3, Frame + gm_boxhgt * 7 + gm_ledhgt }, gm_boxlen, gm_boxhgt, ""),
	in_aim2({ x_max() - Frame - gm_boxlen * 2, Frame + gm_boxhgt * 7 + gm_ledhgt }, gm_boxlen, gm_boxhgt, ""),
	in_aim3({ x_max() - Frame - gm_boxlen, Frame + gm_boxhgt * 7 + gm_ledhgt }, gm_boxlen, gm_boxhgt, ""),
	b_go1({ x_max() - Frame - gm_boxlen * 3, Frame + gm_boxhgt * 1 + gm_ledhgt }, gm_boxlen, gm_boxhgt, "@->", cb_go1),
	b_go2({ x_max() - Frame - gm_boxlen * 3, Frame + gm_boxhgt * 2 + gm_ledhgt }, gm_boxlen, gm_boxhgt, "@->", cb_go2),
	b_go3({ x_max() - Frame - gm_boxlen * 3, Frame + gm_boxhgt * 3 + gm_ledhgt }, gm_boxlen, gm_boxhgt, "@->", cb_go3),
	b_shoot({ x_max() - Frame - gm_boxlen * 3, Frame + gm_boxhgt * 8 + gm_ledhgt }, gm_boxlen * 3, gm_boxhgt, "�������", cb_shoot),
	b_menu({ x_max() - Frame - gm_boxlen * 3, Frame + gm_boxhgt * 10 + gm_ledhgt }, gm_boxlen * 3, gm_boxhgt * 3, "����", cb_menu)
{
	warn_rec1.set_color(Graph_lib::Color::red);
	warn_rec1.set_style(Graph_lib::Line_style(Graph_lib::Line_style::solid, 3));
	warn_rec2.set_color(Graph_lib::Color::red);
	warn_rec2.set_style(Graph_lib::Line_style(Graph_lib::Line_style::solid, 3));
	warn_rec3.set_color(Graph_lib::Color::red);
	warn_rec3.set_style(Graph_lib::Line_style(Graph_lib::Line_style::solid, 3));
	attach(t_goto);
	attach(t_nums);
	led_wum.set_color(Graph_lib::Color::invisible);
	led_wum.set_fill_color(Graph_lib::Color::red);
	led_pit.set_color(Graph_lib::Color::invisible);
	led_pit.set_fill_color(Graph_lib::Color::red);
	led_bat.set_color(Graph_lib::Color::invisible);
	led_bat.set_fill_color(Graph_lib::Color::yellow);
	attach(out_arrows);
	attach(out_meat);
	attach(out_way1);
	attach(out_way2);
	attach(out_way3);
	attach(in_aim1);
	attach(in_aim2);
	attach(in_aim3);
	attach(b_go1);
	attach(b_go2);
	attach(b_go3);
	attach(b_shoot);
	attach(b_menu);
	create_marksets();
	graphic.light_player();
	led_soc();
	display_info();
}

void Game_menu::create_marksets()
{
 	for (int i{ 0 }; i < graphic.size(); ++i) {
		Point c = graphic[i].center();
		b_marksets.push_back(new IDButton({c.x - mrk_wid / 2, c.y - mrk_rad}, mrk_wid, (mrk_hgt + mrk_rad) / 2,
													 "", cb_marksets, i * 10 + int(Cave_mark::bat)));
		attach(b_marksets[b_marksets.size() - 1]);
		b_marksets[b_marksets.size() - 1].box(FL_NO_BOX);

		b_marksets.push_back(new IDButton({ c.x - mrk_wid, c.y - mrk_rad + (mrk_hgt + mrk_rad) / 2 }, mrk_wid, (mrk_hgt + mrk_rad) / 2,
													 "", cb_marksets, i * 10 + int(Cave_mark::wampus)));
		attach(b_marksets[b_marksets.size() - 1]);
		b_marksets[b_marksets.size() - 1].box(FL_NO_BOX);

		b_marksets.push_back(new IDButton({ c.x, c.y - mrk_rad + (mrk_hgt + mrk_rad) / 2 }, mrk_wid, (mrk_hgt + mrk_rad) / 2,
													 "", cb_marksets, i * 10 + int(Cave_mark::pit)));
		attach(b_marksets[b_marksets.size() - 1]);
		b_marksets[b_marksets.size() - 1].box(FL_NO_BOX);
	}
}

void Game_menu::led_soc()
{
	vector<bool> state{engine.player_check()};
	if (state[0])
		attach(led_wum);
	else
		detach(led_wum);
	if (state[1])
		attach(led_pit);
	else
		detach(led_pit);
	if (state[2])
		attach(led_bat);
	else
		detach(led_bat);
}

void Game_menu::pl_move(int way)
try {
	engine.player_move(way);
}
catch (event& ev) {
	static Info_window* inf{nullptr};
	if (inf != nullptr) {
		inf->hide();
		delete inf;
	}
	const int info_len{57};
	inf = new Info_window(descript->screen_center, info_len * 7 + infw_frame * 2, string_to_vec(ev.what()), "���-�� ���������");
}
catch (game_end& gg) {
	game_ended = true;
	static Info_window* inf;
	const int info_len{ 47 };
	inf = new Info_window(descript->screen_center, info_len * 7 + infw_frame * 2, string_to_vec(gg.what()), "����� ����");
	hide_control();
}

void Game_menu::pl_shoot()
try {
	vector<int> route(3);
	vector<string> test(3);
	test[0] = in_aim1.get_string();
	test[1] = in_aim2.get_string();
	test[2] = in_aim3.get_string();
	for (string s : test) {
		if (s.size() == 0)
			{ throw bad_input(""); }
		for (char ch : s)
			if (ch < -1 || !isdigit(ch))
				{ throw bad_input(""); }
	}
	detach(warn_rec1);
	detach(warn_rec2);
	detach(warn_rec3);
	route[0] = in_aim1.get_int() - 1;
	route[1] = in_aim2.get_int() - 1;
	route[2] = in_aim3.get_int() - 1;
	engine.player_shoot(route);
}
catch (event& ev) {
	static Info_window* inf{ nullptr };
	if (inf != nullptr) {
		inf->hide();
		delete inf;
	}
	const int info_len{ 57 };
	inf = new Info_window(descript->screen_center, info_len * 7 + infw_frame * 2, string_to_vec(ev.what()), "���-�� ���������");
}
catch (game_end& gg) {
	game_ended = true;
	static Info_window* inf;
	const int info_len{ 50 };
	inf = new Info_window(descript->screen_center, info_len * 7 + infw_frame * 2, string_to_vec(gg.what()), "����� ����");
	hide_control();
}
catch (bad_input& b) {
	vector<string> test(3);
	test[0] = in_aim1.get_string();
	test[1] = in_aim2.get_string();
	test[2] = in_aim3.get_string();
	notdigitindicate(test[0], warn_rec1, *this);
	notdigitindicate(test[1], warn_rec2, *this);
	notdigitindicate(test[2], warn_rec3, *this);
}


void Game_menu::f_marksets(Graph_lib::Address id)
{ 
	int i = Graph_lib::reference_to<IDButton>(id).get_id();
	Cave_mark::Mark m = Cave_mark::Mark(i % 10);
	i /= 10;
	graphic[i].mark_set(m);
	Fl:redraw();
}

void Game_menu::display_info()
{
	vector<int> tunels{engine.topology()[engine.player_rm()]};
	stringstream s1;
	stringstream s2;
	stringstream s3;
	stringstream ar;
	stringstream me;
	s1 << tunels[0] + 1;
	s2 << tunels[1] + 1;
	s3 << tunels[2] + 1;
	out_way1.put(s1.str());
	out_way2.put(s2.str());
	out_way3.put(s3.str());
	ar << engine.player_bag()[0];
	me << engine.player_bag()[1];
	if (me.str() == "0")
		out_meat.hide();
	else {
		out_meat.show();
		out_meat.put(me.str());
	}
	out_arrows.put(ar.str());
	graphic.light_player();
	Fl::redraw();
	Fl::wait();
}

void Game_menu::hide_control()
{
	b_go1.hide();
	b_go2.hide();
	b_go3.hide();
	b_shoot.hide();
	out_arrows.hide();
	out_way1.hide();
	out_way2.hide();
	out_way3.hide();
	in_aim1.hide();
	in_aim2.hide();
	in_aim3.hide();
	detach(t_goto);
	detach(t_nums);
	detach(warn_rec1);
	detach(warn_rec2);
	detach(warn_rec3);
}

// ------------------------------------------------------------------------------

Info_window::Info_window(Point xy, int w, vector<string> mes, string des)
	: Window({xy.x - w / 2 < 0 ? 0 : xy.x - w / 2,
			  xy.y - (infw_frame * 3 + int(mes.size()) * 15) / 2 < 0 ? 0 : xy.y - (infw_frame * 3 + int(mes.size()) * 15) / 2 },
			  w, infw_frame * 3 + mes.size() * 15, des),
	b_pass({ infw_frame, y_max() - infw_frame * 2 }, w - infw_frame * 2, infw_frame, "ok", cb_pass)
{
	attach(b_pass);
	for (int i{ 0 }; i < mes.size(); ++i) {
		info.push_back(new Graph_lib::Text({infw_frame, infw_frame + i * 15}, mes[i]));
		attach(info[info.size() - 1]);
	}
	clear_border();
	hide();
	show();
}

void Info_window::wait_for_button()
{
	show();
	pass = false;
	while (!pass) /*do nothing*/;
}

//-----------------------------------------------------------

void IDButton::attach(Graph_lib::Window& win)
{
	pw = new Fl_Button(loc.x, loc.y, width, height, label.c_str());
	pw->callback(reinterpret_cast<Fl_Callback*>(do_it), this); // pass the window
	own = &win;
}

//------------------------------------------------------------------------------
