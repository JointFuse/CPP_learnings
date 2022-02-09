#include <vector>
#include <stdexcept>
#include <string>
#include <iostream>
#include "my_graph.h"

extern inline void seed_randint(int s);

namespace Wampus_game {
	constexpr double pi{ 3.14159265358979323846 };
	constexpr int infw_frame{ 20 };
	constexpr int mrk_rad{ 23 };
	const int mrk_hgt = int(mrk_rad * sin(pi / 6));
	const int mrk_wid = int(mrk_rad * cos(pi / 6));
	constexpr int Frame{ 25 };
	constexpr int ButHeight{ 30 };

	const int map_xofs{ 50 };
	const int map_yofs{ 50 };
	const int map_xlen{ 570 };
	const int map_ylen{ 600 };
	const int gm_xlen{ 700 };
	const int gm_ylen{ 600 };
	const int gm_boxlen{ 30 };
	const int gm_boxhgt{ ButHeight };
	const int gm_ledhgt{ 150 };

	constexpr char move{'m'};
	constexpr char shoot{'s'};
	constexpr char info{'i'};
	
	class Game_menu;

	struct IDButton : Graph_lib::Button {
		IDButton(Point xy, int w, int h, const string& label, Graph_lib::Callback cb, int my_id)
			: Button(xy, w, h, label, cb), id{ my_id } { }
		int get_id() const { return id; }
		Game_menu* get_own() const { return reinterpret_cast<Game_menu*>(own); }

		void attach(Graph_lib::Window&);
	private:
		int id;
	};

	struct Room {
		vector<int> doors;
		bool wampus{false};
		bool pit{false};
		bool bat{false};
		bool arrow{false};
		bool dead_bat{false};

		Room() : doors(3, -1) { }
		int untracted();
		bool has_tun(int n);
	};

	struct Cave {
	private:
		vector<Room> rooms;
		Room player;
		int luck{100};
		int pl_rm{ 0 };
		int arrows{ 5 };
		int dead_bat{ 0 };

		void seed_rooms();
		void seed_podlyanka(char ch);
		int untracted();

		string run_to(int n);
		string arrow_fly(int n);
	public:
		Cave(int n);

		vector<vector<int>> topology() const;
		const int& player_rm() const { return pl_rm; }

		void player_action(char ch);
		void player_move(int way);
		void player_shoot(vector<int> route);
		vector<bool> player_check() const;
		vector<int> player_bag() const { return {arrows, dead_bat}; }

		std::string state();
	};

	int difficulty();
	void clear_stream(std::istream& is);

	struct game_end : std::runtime_error {
		game_end(std::string why) : std::runtime_error{why} { }
	};
	struct event : std::runtime_error {
		event(string mes) : std::runtime_error(mes) { }
	};
	struct bad_input : std::runtime_error {
		bad_input(std::string what) : std::runtime_error{what} { }
	};
	struct bad_rand : std::runtime_error {
		bad_rand() : std::runtime_error{""} { }
	};
	struct shut_off : std::runtime_error {
		shut_off() : std::runtime_error{"game exit"} { }
	};

	std::ostream& operator<< (std::ostream&, Cave&);

	struct Cave_mark : Group {
		enum Mark {
			pit = 2, wampus, bat
		};
		Cave_mark(Point center, int n);
		
		void mark_set(Mark);
		void show();
		bool visible();
		void hide();
		void on();
		void off();

		Point center() { return Point(point().x, point().y + mrk_rad); }
	private:
		Group::add_shape;
		Group::move;

		Graph_lib::Color body_c{Graph_lib::Color::cyan}, num_c{Graph_lib::Color::black},
						 danger_c{Graph_lib::Color::red}, warning_c{Graph_lib::Color::yellow};
	};

	class Map {
		vector<vector<int>> rooms;
		Graph_lib::Vector_ref<Cave_mark> marks;
		Graph_lib::Vector_ref<Graph_lib::Line> tunels;
		int light_rm{ -1 };
		const int& pl_rm;
		int map_width;

		int has_tunel(int r1, int r2);
		void light_on();
		void light_off();
		void show_neighbor();
	public:
		Map(Graph_lib::Window& win, int rnum, int xofs, int yofs, 
			int xlen, int ylen, vector<vector<int>> topology, const int& pl_room);

		void light_player();

		Cave_mark& operator[] (int i) { return marks[i]; }
		int size() const { return marks.size(); }
	};

	class Main_menu : public Graph_lib::Window {
		Graph_lib::Text t_name;
		Graph_lib::Text t_diff;

		// Vidgets
		Graph_lib::Button b_start;
		Graph_lib::Button b_exit;
		Graph_lib::Button b_diff1;
		Graph_lib::Button b_diff2;
		Graph_lib::Button b_diff3;
		Graph_lib::Button b_diff4;
		Graph_lib::Button b_diff5;

		void show_main();
		void show_diff();
		void game_start(int diff);

		// Button functions
		void f_start()	{ if (new_game) { show_diff(); return; } game_start(42); }
		void f_exit()	{ hide(); throw shut_off(); }
		void f_diff1()	{ hide(); game_start(16); }
		void f_diff2()	{ hide(); game_start(20); }
		void f_diff3()	{ hide(); game_start(26); }
		void f_diff4()	{ hide(); game_start(32); }
		void f_diff5()	{ hide(); game_start(42); }

		// Call back functions
		static void cb_start(Graph_lib::Address, Graph_lib::Address pw)	{ Graph_lib::reference_to<Main_menu>(pw).f_start(); }
		static void cb_exit(Graph_lib::Address, Graph_lib::Address pw)	{ Graph_lib::reference_to<Main_menu>(pw).f_exit(); }
		static void cb_diff1(Graph_lib::Address, Graph_lib::Address pw) { Graph_lib::reference_to<Main_menu>(pw).f_diff1(); }
		static void cb_diff2(Graph_lib::Address, Graph_lib::Address pw) { Graph_lib::reference_to<Main_menu>(pw).f_diff2(); }
		static void cb_diff3(Graph_lib::Address, Graph_lib::Address pw) { Graph_lib::reference_to<Main_menu>(pw).f_diff3(); }
		static void cb_diff4(Graph_lib::Address, Graph_lib::Address pw) { Graph_lib::reference_to<Main_menu>(pw).f_diff4(); }
		static void cb_diff5(Graph_lib::Address, Graph_lib::Address pw) { Graph_lib::reference_to<Main_menu>(pw).f_diff5(); }

	public:
		bool new_game{ true };
		const Point screen_center;

		Main_menu(Point xy);
	};

	struct Info_window : Graph_lib::Window {
		Info_window(Point xy, int w, vector<string> message, string descriptor);

		void wait_for_button();
	private:
		bool pass{ false };
		Graph_lib::Vector_ref<Graph_lib::Text> info;
		Graph_lib::Button b_pass;

		void f_pass() { pass = true; hide(); }
		static void cb_pass(Graph_lib::Address, Graph_lib::Address pw) { Graph_lib::reference_to<Info_window>(pw).f_pass(); }
	};

	class Game_menu : public Graph_lib::Window {
		// Состояние игрового процесса
		bool game_ended{false};
		// Адрес вызвавшего окна (главного меню)
		Main_menu* descript;

		// Логика игры и графика
		Cave engine;
		Map graphic;

		// Вспомогательная графика
		Graph_lib::Text t_goto;
		Graph_lib::Text t_nums;
		Graph_lib::Rectangle warn_rec1;
		Graph_lib::Rectangle warn_rec2;
		Graph_lib::Rectangle warn_rec3;

		Text_box led_wum;
		Text_box led_pit;
		Text_box led_bat;

		// Виджеты
		Graph_lib::Out_box out_arrows;
		Graph_lib::Out_box out_meat;
		Graph_lib::Out_box out_way1;
		Graph_lib::Out_box out_way2;
		Graph_lib::Out_box out_way3;
		Graph_lib::In_box in_aim1;
		Graph_lib::In_box in_aim2;
		Graph_lib::In_box in_aim3;
		Graph_lib::Button b_go1;
		Graph_lib::Button b_go2;
		Graph_lib::Button b_go3;
		Graph_lib::Button b_shoot;
		Graph_lib::Button b_menu;
		Graph_lib::Vector_ref<IDButton> b_marksets;

		// Логика управления графикой и движком
		void create_marksets();
		void led_soc();
		void pl_move(int way);
		void pl_shoot();
		void display_info();
		void hide_control();

		// Функции виджетов
		void f_go1() { pl_move(0); led_soc(); display_info(); }
		void f_go2() { pl_move(1); led_soc(); display_info(); }
		void f_go3() { pl_move(2); led_soc(); display_info(); }
		void f_shoot(){ pl_shoot(); led_soc(); display_info(); }
		void f_marksets(Graph_lib::Address);
		void f_menu(){ descript->new_game = game_ended; descript->show(); descript->resize(150, 215); hide(); }

		// Функции обратного вызова виджетов
		static void cb_go1(Graph_lib::Address, Graph_lib::Address pw)	{ Graph_lib::reference_to<Game_menu>(pw).f_go1(); }
		static void cb_go2(Graph_lib::Address, Graph_lib::Address pw)	{ Graph_lib::reference_to<Game_menu>(pw).f_go2(); }
		static void cb_go3(Graph_lib::Address, Graph_lib::Address pw)	{ Graph_lib::reference_to<Game_menu>(pw).f_go3(); }
		static void cb_shoot(Graph_lib::Address, Graph_lib::Address pw)	{ Graph_lib::reference_to<Game_menu>(pw).f_shoot(); }
		static void cb_marksets(Graph_lib::Address, Graph_lib::Address pw){ Graph_lib::reference_to<IDButton>(pw).get_own()->f_marksets(pw); }
		static void cb_menu(Graph_lib::Address, Graph_lib::Address pw)	{ Graph_lib::reference_to<Game_menu>(pw).f_menu(); }

	public:
		Game_menu(Point xy, int diff, Main_menu* back);
	};
}