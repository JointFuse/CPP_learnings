#include "OrderGraph.h"

using namespace OrderGraph_lib;

//-------------------------------------------------------------------------------------------------------

OrderAdd_win::OrderAdd_win(Point xy)
	: Window(xy, odw_width, odw_height, "new order"),
	in_filename({ odw_xoffset + odw_textoffset, odw_yoffset },
				odw_width - odw_xoffset * 2 - odw_textoffset, odw_boxheight, "file name:"),
	in_name({ odw_xoffset + odw_textoffset, odw_yoffset + odw_boxheight },
			odw_width - odw_xoffset * 2 - odw_textoffset, odw_boxheight, "customer name:"),
	in_year({ odw_xoffset + odw_textoffset, odw_yoffset + odw_boxheight * 2 },
			50, odw_boxheight, "birth year:"),
	in_month({ odw_width - odw_xoffset - 94, odw_yoffset + odw_boxheight * 2 },
			 30, odw_boxheight, "month:"),
	in_day({ odw_width - odw_xoffset - 30, odw_yoffset + odw_boxheight * 2 },
		   30, odw_boxheight, "day:"),
	in_addr({ odw_xoffset + odw_textoffset, odw_yoffset + odw_boxheight * 3 },
			odw_width - odw_xoffset * 2 - odw_textoffset, odw_boxheight, "address:"),
	in_pname({ odw_xoffset + odw_textoffset2, odw_yoffset + odw_boxheight },
			 odw_width - odw_xoffset * 2 - odw_textoffset2, odw_boxheight, "product:"),
	in_pprice({ odw_xoffset + odw_textoffset2, odw_yoffset + odw_boxheight * 2 },
			  odw_width - odw_xoffset * 2 - odw_textoffset2, odw_boxheight, "price:"),
	in_pcount({ odw_xoffset + odw_textoffset2, odw_yoffset + odw_boxheight * 3 },
			  odw_width - odw_xoffset * 2 - odw_textoffset2, odw_boxheight, "count:"),
	out_purchcount({ odw_width / 2, odw_yoffset },
				   odw_width / 2 - odw_xoffset, odw_boxheight, "total purshases:"),
	b_next({ odw_width / 2 - (odw_width - 2 * odw_xoffset) / 4, odw_height - odw_yoffset - odw_boxheight },
		   (odw_width - 2 * odw_xoffset) / 4, odw_boxheight, "next", cb_next),
	b_back({ odw_width / 2 - (odw_width - 2 * odw_xoffset) / 4, odw_height - odw_yoffset - odw_boxheight },
		   (odw_width - 2 * odw_xoffset) / 4, odw_boxheight, "back", cb_back),
	b_quit({ odw_width / 2 - (odw_width - 2 * odw_xoffset) / 2, odw_height - odw_yoffset - odw_boxheight },
		   (odw_width - 2 * odw_xoffset) / 4, odw_boxheight, "quit", cb_quit),
	b_save({ odw_width / 2, odw_height - odw_yoffset - odw_boxheight },
		   (odw_width - 2 * odw_xoffset) / 4, odw_boxheight, "save", cb_save),
	b_add({ odw_width / 2 + (odw_width - 2 * odw_xoffset) / 4, odw_height - odw_yoffset - odw_boxheight },
		  (odw_width - 2 * odw_xoffset) / 4, odw_boxheight, "add", cb_add)
{
	attach(in_filename);
	attach(in_name);
	attach(in_year);
	attach(in_month);
	attach(in_day);
	attach(in_addr);
	attach(in_pname);
	attach(in_pprice);
	attach(in_pcount);
	attach(out_purchcount);
	attach(b_next);
	attach(b_back);
	attach(b_quit);
	attach(b_save);
	attach(b_add);
	show_first();
}

//-------------------------------------------------------------------------------------------------------

void OrderAdd_win::show_first()
{
	out_purchcount.put("0");
	in_pname.hide();
	in_pprice.hide();
	in_pcount.hide();
	out_purchcount.hide();
	b_back.hide();
	b_add.hide();
	in_filename.show();
	in_name.show();
	in_year.show();
	in_month.show();
	in_day.show();
	in_addr.show();
	b_next.show();
}

//-------------------------------------------------------------------------------------------------------

void OrderAdd_win::show_second()
{
	in_filename.hide();
	in_name.hide();
	in_year.hide();
	in_month.hide();
	in_day.hide();
	in_addr.hide();
	b_next.hide();
	in_pname.show();
	in_pprice.show();
	in_pcount.show();
	out_purchcount.show();
	b_back.show();
	b_add.show();
}

//-------------------------------------------------------------------------------------------------------

void OrderAdd_win::f_next()
{
	ostringstream order_info;
	order_info << "{ " << in_name.get_string() << " ("
			   << in_year.get_string() << ',' << in_month.get_string() << ',' << in_day.get_string() 
			   << ") from: " << in_addr.get_string() << " : }";
	
	istringstream info_put{order_info.str()};
	if (!(info_put >> order[0]))
		{ return; }

	order[0].clear();
	file_name = in_filename.get_string();
	if (file_name == "")
		{ file_name = in_name.get_string() + "_order"; }
	file_name += ".txt";

	show_second();
}

//-------------------------------------------------------------------------------------------------------

void OrderAdd_win::f_add()
{
	ostringstream purch_info;
	purch_info << '[' << in_pname.get_string() << ' '
			   << in_pprice.get_string() << ' '
			   << in_pcount.get_string() << ']';

	istringstream info_put{purch_info.str()};
	Order_lib::Purchase buf;
	if (!(info_put >> buf))
		{ return; }

	order[0].add_purch(buf);
	purch_info.str("");
	purch_info << order[0].check_size();
	out_purchcount.put(purch_info.str());
}

//-------------------------------------------------------------------------------------------------------

OrderInfo_win::OrderInfo_win(Point xy)
	: Window(xy, oiw_width, oiw_height, "file manipulations"),
	in_file({ oiw_xoffset + oiw_textoffset, oiw_yoffset },
			oiw_width - oiw_xoffset * 2 - oiw_textoffset, oiw_boxheight, "file:"),
	in_name({ oiw_xoffset + oiw_textoffset, oiw_yoffset + oiw_boxheight },
			oiw_width - oiw_xoffset * 2 - oiw_textoffset, oiw_boxheight, "key:"),
	b_name({ oiw_xoffset, oiw_yoffset + oiw_boxheight * 2 },
		   oiw_width - oiw_xoffset * 2, oiw_boxheight, "search by customer", cb_name),
	b_product({ oiw_xoffset, oiw_yoffset + oiw_boxheight * 3 },
			  oiw_width - oiw_xoffset * 2, oiw_boxheight, "search by product", cb_product),
	b_total({ oiw_xoffset, oiw_yoffset + oiw_boxheight * 4 },
			oiw_width - oiw_xoffset * 2, oiw_boxheight, "total from file", cb_total),
	b_all({ oiw_xoffset, oiw_yoffset + oiw_boxheight * 5 },
		  oiw_width - oiw_xoffset * 2, oiw_boxheight, "print from file", cb_all),
	b_quit({ oiw_xoffset, oiw_yoffset + oiw_boxheight * 6 },
		   oiw_width - oiw_xoffset * 2, oiw_boxheight, "quit and close", cb_quit)
{
	attach(in_file);
	attach(in_name);
	attach(b_name);
	attach(b_product);
	attach(b_total);
	attach(b_all);
	attach(b_quit);
}

//-------------------------------------------------------------------------------------------------------

void OrderInfo_win::f_name()
{
	ifstream file(in_file.get_string() + ".txt");
	if (!file) { return; }
	if (in_name.get_string() == "") { return; }

	vector<Order_lib::Order> ord = 
		Order_lib::search_byname(in_name.get_string(), file);

	copy(ord.begin(), ord.end(),
		 ostream_iterator<Order_lib::Order>(cout));
}

//-------------------------------------------------------------------------------------------------------

void OrderInfo_win::f_product()
{
	ifstream file(in_file.get_string() + ".txt");
	if (!file) { return; }
	if (in_name.get_string() == "") { return; }

	vector<Order_lib::Order> ord = 
		Order_lib::search_byproduct(in_name.get_string(), file);

	copy(ord.begin(), ord.end(),
		 ostream_iterator<Order_lib::Order>(cout));
}

//-------------------------------------------------------------------------------------------------------

void OrderInfo_win::f_total()
{
	string file_name{in_file.get_string()};
	if (file_name == "") { return; }
	ifstream file(file_name + ".txt");
	if (!file) { return; }

	cout << "Total sum from [" << file_name << "] = " 
		 << Order_lib::total_cost(file) << '\n';
}

//-------------------------------------------------------------------------------------------------------

void OrderInfo_win::f_all()
{
	ifstream file(in_file.get_string() + ".txt");
	if (!file) { return; }
	
	Order_lib::all_from_file(cout, file);
}

//-------------------------------------------------------------------------------------------------------
