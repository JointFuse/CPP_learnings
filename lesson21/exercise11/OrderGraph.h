#ifndef OrderGraph_h
#define	OrderGraph_h

#include "OS/Order.h"
#include "GUI/Window.h"
#include "GUI/my_graph.h"

namespace OrderGraph_lib {
	using namespace Graph_lib;
	
	constexpr int odw_width{ 350 };
	constexpr int odw_height{ 160 };
	constexpr int odw_xoffset{ 30 };
	constexpr int odw_yoffset{ 30 };
	constexpr int odw_boxheight{ 20 };
	constexpr int odw_textoffset{ 90 };
	constexpr int odw_textoffset2{ 60 };

	constexpr int oiw_width{ 250 };
	constexpr int oiw_xoffset{ 20 };
	constexpr int oiw_yoffset{ 20 };
	constexpr int oiw_boxheight{ 25 };
	constexpr int oiw_textoffset{ 30 };
	constexpr int oiw_height{ 2 * oiw_yoffset + 7 * oiw_boxheight + 8 };

	class OrderAdd_win : Window {
		vector<Order_lib::Order> order{1};
		string file_name;

		// Vidgets
		In_box in_filename;
		In_box in_name;
		In_box in_year;
		In_box in_month;
		In_box in_day;
		In_box in_addr;
		In_box in_pname;
		In_box in_pprice;
		In_box in_pcount;
		Out_box out_purchcount;

		Button b_next;
		Button b_back;
		Button b_quit;
		Button b_save;
		Button b_add;

		// Helpfull functions
		void show_first();
		void show_second();

		// Button deal functions
		void f_next();
		void f_back() { show_first(); }
		void f_quit() { hide(); throw runtime_error("programm stoped"); }
		void f_save() { if (file_name != "") Order_lib::order_upload(order, file_name); }
		void f_add();

		// Call back functions
		static void cb_next(Address, Address pw){ reference_to<OrderAdd_win>(pw).f_next(); }
		static void cb_back(Address, Address pw){ reference_to<OrderAdd_win>(pw).f_back(); }
		static void cb_quit(Address, Address pw){ reference_to<OrderAdd_win>(pw).f_quit(); }
		static void cb_save(Address, Address pw){ reference_to<OrderAdd_win>(pw).f_save(); }
		static void cb_add(Address, Address pw)	{ reference_to<OrderAdd_win>(pw).f_add(); }
	public:
		OrderAdd_win(Point xy);
	};

	class OrderInfo_win : Window {
		// Vidgets
		In_box in_file;
		In_box in_name;

		Button b_name;
		Button b_product;
		Button b_total;
		Button b_all;
		Button b_quit;

		// Button deal functions
		void f_name();
		void f_product();
		void f_total();
		void f_all();
		void f_quit() { hide(); throw runtime_error("programm stoped"); }

		// Call back functions
		static void cb_name(Address, Address pw) { reference_to<OrderInfo_win>(pw).f_name(); }
		static void cb_product(Address, Address pw) { reference_to<OrderInfo_win>(pw).f_product(); }
		static void cb_total(Address, Address pw) { reference_to<OrderInfo_win>(pw).f_total(); }
		static void cb_all(Address, Address pw) { reference_to<OrderInfo_win>(pw).f_all(); }
		static void cb_quit(Address, Address pw) { reference_to<OrderInfo_win>(pw).f_quit(); }
	public:
		OrderInfo_win(Point xy);
	};
}
#endif // !OrderGraph_h
