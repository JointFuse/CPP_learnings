#include <vector>
#include <stdexcept>
#include <string>
#include <iostream>

extern inline void seed_randint(int s);

namespace Wampus_game {
	constexpr char move{'m'};
	constexpr char shoot{'s'};
	constexpr char info{'i'};

	struct Room {
		std::vector<int> doors;
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
		std::vector<Room> rooms;
		Room player;
		int luck{100};
		int pl_rm{ 0 };
		int arrows{ 5 };
		int dead_bat{ 0 };

		void seed_rooms();
		void seed_podlyanka(char ch);
		int untracted();

		void run_to(int n);
		void arrow_fly(int n);
		void player_move();
		void player_shoot();
		void player_check();
	public:
		Cave(int n);

		void player_action(char ch);

		std::string state();
	};

	int difficulty();
	void clear_stream(std::istream& is);

	struct game_end : std::runtime_error {
		game_end(std::string why) : std::runtime_error{why} { }
	};
	struct bad_input : std::runtime_error {
		bad_input(std::string what) : std::runtime_error{what} { }
	};
	struct bad_rand : std::runtime_error {
		bad_rand() : std::runtime_error{""} { }
	};

	std::ostream& operator<< (std::ostream&, Cave&);
}