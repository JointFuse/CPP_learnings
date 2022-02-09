#include "my_window.h"

//----------------------------------------------------------------------------

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
	:Window(xy, w, h, title),
	next_button{ Point{ x_max() - 150, 0 }, 70, 20, 
				"Next point", cb_next },
	quit_button{ Point{x_max() - 70, 0}, 70, 20, 
				"Quit", cb_quit },
	next_x{ Point{x_max() - 310, 0}, 50, 20, "next x:" },
	next_y{ Point{x_max() - 210, 0}, 50, 20, "next y:" },
	xy_out{ Point{100, 0}, 100, 20, "current (x,y):" },
	color_menu{Point{x_max()-70, 30}, 70, 20,
				Menu::vertical, "color"},
	style_menu{Point{x_max()-70, 90}, 70, 20,
				Menu::vertical, "style"},
	color_button{Point{x_max()-90, 30}, 90, 20,
				"color menu", cb_colmenu},
	style_button{Point{x_max()-90, 90}, 90, 20,
				"style menu", cb_stymenu}
{
	attach(next_button);
	attach(quit_button);
	attach(next_x);
	attach(next_y);
	attach(xy_out);
	xy_out.put("no point");
	color_menu.attach(new Button({0, 0}, 0, 0, "red", cb_red));
	color_menu.attach(new Button({0, 0}, 0, 0, "blue", cb_blue));
	color_menu.attach(new Button({0, 0}, 0, 0, "black", cb_black));
	attach(color_menu);
	color_menu.hide();
	style_menu.attach(new Button({0, 0}, 0, 0, "dot", cb_dot));
	style_menu.attach(new Button({0, 0}, 0, 0, "solid", cb_solid));
	style_menu.attach(new Button({0, 0}, 0, 0, "dashdot", cb_dashdot));
	attach(style_menu);
	style_menu.hide();
	attach(color_button);
	attach(style_button);
	attach(lines);
}

void Lines_window::quit()
{
	hide();
}

void Lines_window::next()
{
	int x = next_x.get_int();
	int y = next_y.get_int();
	lines.add({x, y});

	ostringstream ss;
	ss << '(' << x << ',' << y << ')';
	xy_out.put(ss.str());

	redraw();
}

//----------------------------------------------------------------------------

My_window::My_window(Point xy, int w, int h, const string& title, bool hn)
	: Simple_window(xy, w, h, title),
	quit_button(Point{ x_max() - 70, 20 }, 70, 20, "Quit", cb_quit)
{
	attach(quit_button);
	if (hn) {
		next_button.hide();
		quit_button.move(0, -20);
	}
}

//----------------------------------------------------------------------------

Button_matrix::Button_matrix(Point xy, int width, int length, int l)
	: My_window{xy, width, length, "button rainbow"},
	mask{xy, 4 * l, 4},
	b0(xy, l, l, "", cb_b0),
	b1({xy.x+l, xy.y}, l, l, "", cb_b1),
	b2({xy.x+2*l, xy.y}, l, l, "", cb_b2),
	b3({ xy.x+3*l, xy.y }, l, l, "", cb_b3),
	b4({ xy.x, xy.y+l }, l, l, "", cb_b4),
	b5({ xy.x+l, xy.y+l }, l, l, "", cb_b5),
	b6({ xy.x+2*l, xy.y+l }, l, l, "", cb_b6),
	b7({ xy.x+3*l, xy.y+l }, l, l, "", cb_b7),
	b8({ xy.x, xy.y+2*l }, l, l, "", cb_b8),
	b9({ xy.x+l, xy.y+2*l }, l, l, "", cb_b9),
	b10({ xy.x+2*l, xy.y+2*l }, l, l, "", cb_b10),
	b11({ xy.x+3*l, xy.y+2*l }, l, l, "", cb_b11),
	b12({ xy.x, xy.y+3*l }, l, l, "", cb_b12),
	b13({ xy.x+l, xy.y+3*l }, l, l, "", cb_b13),
	b14({ xy.x+2*l, xy.y+3*l }, l, l, "", cb_b14),
	b15({ xy.x+3*l, xy.y+3*l }, l, l, "", cb_b15)
{
	attach(mask);
	attach(b0);
	attach(b1);
	attach(b2);
	attach(b3);
	attach(b4);
	attach(b5);
	attach(b6);
	attach(b7);
	attach(b8);
	attach(b9);
	attach(b10);
	attach(b11);
	attach(b12);
	attach(b13);
	attach(b14);
	attach(b15);
}

void Button_matrix::do_it(int i) 
{ 
	static int cur{0};
	mask.set_fill_color(cur, Color::white);
	mask.set_fill_color(i, randint(0, 256));
	cur = i;
	redraw(); 
}

//----------------------------------------------------------------------------

Moving_image::Moving_image()
	:My_window{{100, 100}, 800, 600, "Ïîéìàé ×åëåíòàíî"},
	move_pic{ {0, 0}, 200, 200, "pic", [](Address, Address pw)
	{ reference_to<Moving_image>(pw).move_but(); } },
	pic{ {0, 0}, "picture.jpg" }
{
	attach(pic);
	attach(move_pic);
	pic.set_mask({120, 10}, 200, 200);
}

void Moving_image::move_but()
{
	int dx = randint(0, 600);
	int dy = randint(0, 400);
	dx = dx - pic.point(0).x;
	dy = dy - pic.point(0).y;
	pic.move(dx,dy);
	move_pic.move(dx, dy);
	redraw();
}

//----------------------------------------------------------------------------

Figures::Figures(Point xy, int w, int h, const string& nam)
	: Window(xy, w, h, nam),
	b_next({ x_max() - 70, 0 }, 70, 20, "Next", cb_next),
	b_quit({ x_max() - 70, 20 }, 70, 20, "Quit", cb_quit),
	x_new({ x_max() - 310, 0 }, 50, 20, "next x:"),
	y_new({ x_max() - 210, 0 }, 50, 20, "next y:"),
	m_forms({ x_max() - 70, 40 }, 70, 20, Menu::vertical, "forms"),
	b_menu({x_max()-70, 40}, 70, 20, "forms", cb_menu)
{
	attach(b_next);
	attach(b_quit);
	attach(x_new);
	attach(y_new);
	m_forms.attach(new Button({ 0, 0 }, 70, 20, "circle", cb_circle));
	m_forms.attach(new Button({ 0, 0 }, 70, 20, "square", cb_square));
	m_forms.attach(new Button({ 0, 0 }, 70, 20, "triangle", cb_triangle));
	m_forms.attach(new Button({ 0, 0 }, 70, 20, "hexagon", cb_hexagon));
	attach(m_forms);
	m_forms.hide();
	attach(b_menu);
}

void Figures::draw_shape()
{
	int x = x_new.get_int();
	int y = y_new.get_int();
	int l = (x_max() + y_max()) / 2;

	switch (cur_f) {
	case f_circle:
		draw_circle(x, y, l);
		break;
	case f_square:
		draw_square(x, y, l);
		break;
	case f_triangle:
		draw_triangle(x, y, l);
		break;
	case f_hexagon:
		draw_hexagon(x, y, l);
		break;
	default:
		error("figures.draw_shape: unknown draw func");
		break;
	}

	attach(obj[obj.size() - 1]);
}

void Figures::draw_circle(int x, int y, int r)
{
	obj.push_back(new Circle({x, y}, r*scale));
}

void Figures::draw_square(int x, int y, int l)
{
	obj.push_back(new Rectangle({x, y}, l*scale, l*scale));
}

void Figures::draw_triangle(int x, int y, int h)
{
	obj.push_back(new Regular_polygon({x, y}, 3, h*scale));
}

void Figures::draw_hexagon(int x, int y, int h)
{
	obj.push_back(new Regular_hexagon({x, y}, h*scale));
}

//----------------------------------------------------------------------------

void Moving_figure::next() 
{ 
	if (0 < obj.size()) {
		Shape* ptr = &obj[obj.size() - 1];
		int dx = x_new.get_int() - ptr->point(0).x;
		int dy = y_new.get_int() - ptr->point(0).y;
		ptr->move(dx, dy);
	}

	redraw(); 
}

void Moving_figure::draw_shape()
{
	if (0 < obj.size())
		detach(obj[obj.size() - 1]);

	Figures::draw_shape();
}

//----------------------------------------------------------------------------

Clock::Clock(Point xy, string n)
	:Window(xy, 600, 600, n),
	back({ 0, 0 }, "cloack.jpg"),
	sec({ 300, 300 }, 258, 14),
	mins({ 300, 300 }, 258), 
	hour({ 300, 300 }, 258),
	b_quit({0, 0}, x_max(), y_max(), "QUIT!!!", cb_quit),
	quit_instruct({0, y_max()-10}, "TAP ANYWHERE TO CLOSE(ÍÀÆÌÈ Â ËÞÁÎÉ ÒÎ×ÊÅ ÄËß ÂÛÕÎÄÀ)")
{
	attach(back);
	attach(sec);
	attach(mins);
	attach(hour);
	attach(b_quit);
	attach(quit_instruct);

	set_time();
	tick_tak();
}

//----------------------------------------------------------------------------

Fly_plane::Fly_plane(Point xy, int width, int height)
	:bort{ {width / 2, height / 2}, 100 }, bort_eng{ bort, width, height },
	Window(xy, width, height, "flying plane"),
	b_start({x_max()-70, 0}, 70, 20, "Start", cb_start),
	b_stop({x_max()-70, 20}, 70, 20, "Stop", cb_stop),
	b_quit({x_max()-70, 20}, 70, 20, "Quit", cb_quit),
	b_phion({x_max()-160, 0}, 90, 20, "Damage off", cb_phion),
	b_phioff({x_max()-160, 0}, 90, 20, "Damage on", cb_phioff)
{
	attach(bort);
	attach(b_start);
	attach(b_stop);
	b_stop.hide();
	attach(b_quit);
	attach(b_phion);
	attach(b_phioff);

	if (bort_eng.is_damage())
		b_phion.hide();
	else
		b_phioff.hide();

	soccet();
}

void Fly_plane::soccet()
{
	while (true) {
		if (is_run) {
			bort_eng.fly();
			Fl::redraw();
			Fl::wait();
			Windows_h::Sleep(8);
		}
		else {
			Fl::redraw();
			Fl::wait();
			Windows_h::Sleep(250);
		}
	}
}

//----------------------------------------------------------------------------

Currency_converter::Currency_converter(Point xy, int w, int h)
	:Window(xy, w, h, "Converter"),
	setting_info1{ {50, y_max() - 60}, "here you can configure the processing of courses" },
	setting_info2{ {50, y_max() - 40}, "on loading and download them from convert_pairs.txt" },
	box_base({ 60, 20 }, 50, 20, "from:"),
	box_targ({ 60, 40 }, 50, 20, "to:"),
	box_from({ 120, 20 }, x_max() - 160, 20, ""),
	box_to({ 120, 40 }, x_max() - 160, 20, ""),
	b_convert({ x_max() - 70, y_max() - 67 }, 70, 20, "convert", cb_convert),
	b_setting({ x_max() - 70, y_max() - 47 }, 70, 20, "settings", cb_setting),
	b_quit({ x_max() - 70, y_max() - 27 }, 70, 20, "QUIT", cb_quit),
	b_load({ x_max() - 140, y_max() - 27 }, 70, 20, "load data", cb_load),
	b_overon({ x_max() - 210, y_max() - 27 }, 70, 20, "update off", cb_overon),
	b_overoff({ x_max() - 210, y_max() - 27 }, 70, 20, "update on", cb_overoff)
{
	attach(box_from);
	attach(box_to);
	attach(box_base);
	attach(box_targ);
	attach(b_convert);
	attach(b_quit);
	attach(b_load);
	b_load.hide();
	attach(b_overon);
	b_overon.hide();
	attach(b_overoff);
	b_overoff.hide();
	attach(b_setting);
}

void Currency_converter::show_setting()
{
	static bool open{false};
	if (open) {
		detach(setting_info1);
		detach(setting_info2);
		b_load.hide();
		if(engine.is_override())
			b_overoff.hide();
		else
			b_overon.hide();
		open ^= true;
	}
	else {
		attach(setting_info1);
		attach(setting_info2);
		b_load.show();
		if (engine.is_override())
			b_overoff.show();
		else
			b_overon.show();
		open ^= true;
	}
	redraw();
}

void Currency_converter::bp_convert()
try{
	string cur1, cur2;
	int sum;
	cur1 = box_base.get_string();
	cur2 = box_targ.get_string();
	sum = box_from.get_int();

	ostringstream result;
	result << engine.convert(cur1, cur2, sum);
	box_to.put(result.str());
	redraw();
}
catch (Finance::convert_error& e) {
	box_to.put(e.what());
	redraw();
}

void Currency_converter::bp_load()
{
	ifstream data("convert_pairs.txt");
	if (!data) {
		box_to.put("can't open convert_pairs.txt");
		return;
	}

	while(data >> engine) { }

	if (!data.eof()) {
		box_to.put("wrong syntaxis, right: (XXXYYYNUM)");
	}
	else {
		box_to.put("load complete");
	}
	redraw();
}

//----------------------------------------------------------------------------

My_calculator::My_calculator(Point xy, int w, int h)
	:Window(xy, w, h, "Calculator"),
	box_example({ 20, 20 }, x_max() - 40, 20, ""),
	box_solving({ 20, 40 }, x_max() - 40, 20, ""),
	b_calculate({ 20, 60 }, x_max() - 40, 20, "âû÷èñëèòü", cb_calculate),
	b_help({ 20, 80 }, x_max() - 40, 20, "èíôîðìàöèÿ", cb_help)
{
	attach(box_example);
	attach(box_solving);
	attach(b_calculate);
	attach(b_help);

	box_solving.put("çäåñü áóäåò îòâåò");
}

void My_calculator::switch_stream(istringstream* in_str, ostringstream* out_str)
{
	static bool window_connect{ false };
	static ostream* calcout{ Calculator::my_ostream };
	static istream* calcin{ Calculator::my_istream };
	static auto old_outbuf{ calcout->rdbuf() };
	static auto old_inbuf{ calcin->rdbuf() };

	if (window_connect) {
		calcin->set_rdbuf(old_inbuf);
		calcout->rdbuf(old_outbuf);
		calcin->clear();
		calcin->seekg(0);
		window_connect = false;
	}
	else {
		calcout = Calculator::my_ostream;
		calcin = Calculator::my_istream;
		old_outbuf = calcout->rdbuf();
		old_inbuf = calcin->rdbuf();

		calcin->set_rdbuf(in_str->rdbuf());
		if (out_str != NULL)
			calcout->rdbuf(out_str->rdbuf());
		window_connect = true;
	}
}

void My_calculator::bp_calculate()
{
	ostringstream out_str;
	istringstream in_str(box_example.get_string());
	switch_stream(&in_str, &out_str);

	if (Calculator::calculate()) {
		switch_stream(&in_str, &out_str);
		hide();
		throw exception("program stoped");
	}

	box_solving.put(out_str.str());
	switch_stream(&in_str, &out_str);
}

void My_calculator::bp_help()
{
	istringstream in_str("help");
	switch_stream(&in_str);
 	Calculator::calculate();
	switch_stream(&in_str);
}

//----------------------------------------------------------------------------

FuncGraph_creator::FuncGraph_creator(Point xy, Vector_ref<Window>& ptr1, Vector_ref<Shape>& ptr2, int param_num, bool is_p_float)
	: Window(xy, 400, 110, "Function parametrs"), winptr{ ptr1 }, shptr{ ptr2 }, O{ xy }, float_param{is_p_float},
	box_A({ 35, 20 }, x_max() / 2 - 55, 20, "A:"),
	box_B({ x_max() / 2 + 35, 20 }, x_max() / 2 - 55, 20, "<   B:"),
	box_n({ 35, 45 }, x_max() - 55, 20, "n:"),
	box_name({ 20, 20 }, x_max() - 40, 20, ""),
	box_param({ 20, 45 }, x_max() - 40, 20, ""),
	b_next({ 20, 70 }, x_max() - 40, 20, "next", cb_next),
	b_addparam({ 20, 70 }, x_max() - 40, 20, "add parametr", cb_addparam),
	b_back({ 0, 0 }, 20, 20, "<", cb_back)
{
	set_param_num(param_num);
	attach(box_A);
	attach(box_B);
	attach(box_n);
	attach(box_name);
	box_name.hide();
	attach(box_param);
	box_param.hide();
	attach(b_next);
	attach(b_back);
	b_back.hide();
	attach(b_addparam);
	b_addparam.hide();
}

void FuncGraph_creator::show_base()
{
	b_back.hide();
	b_addparam.hide();
	box_name.hide();
	box_param.hide();
	box_A.show();
	box_B.show();
	box_n.show();
	b_next.show();
}

void FuncGraph_creator::show_param()
{
	b_next.hide();
	box_A.hide();
	box_B.hide();
	box_n.hide();
	box_param.show();
	box_name.show();
	b_back.show();
	b_addparam.show();
	box_name.put("write parametr ¹0");
}

void FuncGraph_creator::bp_next()
{
	istringstream readed(box_A.get_string() + " " +
					 	 box_B.get_string() + " " +
						 box_n.get_string());
	readed >> A >> B >> n_pts;
	if (A < B) {
		auto_scale();
		show_param();
	}
}

void FuncGraph_creator::bp_addparam()
{
	string ss;
	istringstream readed(ss = box_param.get_string());
	if (ss == "") return;

	if (get_p()) {
		readed >> param[p_got - 1];
		if (float_param) {
			set_param_num(param[p_got - 1] + 1);
			float_param = false;
			--p_got;
		}
		ostringstream info;
		info << "write parametr ¹" << p_got;
		box_name.put(info.str());
	}
	else {
		winptr.push_back(draw_window());
		shptr.push_back(draw_graphic());
		winptr[winptr.size() - 1].attach(shptr[shptr.size() - 1]);
		draw_axes();
		hide();
	}

	if (p_got == param.size()) {
		box_name.put("press add parametr to show graphic");
	}
}

void FuncGraph_creator::bp_back()
{
	reset_param();
	show_base();
}

Window* FuncGraph_creator::draw_window()
{
	Window* ptr = new My_window({ O.x + x_max() / 2, O.y + y_max() / 2 }, xm, ym, "Function graphic", true);
	return ptr;
}

void FuncGraph_creator::draw_axes()
{
	Shape* ptr = new Axis(Axis::x, { xofs, ym / 2 }, xm - 2 * xofs, (xm - 2 * xofs) / xsc, "X");
	shptr.push_back(ptr);
	winptr[winptr.size() - 1].attach(*ptr);
	ptr = new Axis(Axis::y, { xm / 2, ym - yofs}, ym - 2 * yofs, (ym - 2 * yofs) / ysc, "Y");
	shptr.push_back(ptr);
	winptr[winptr.size() - 1].attach(*ptr);
}

void FuncGraph_creator::auto_scale()
{
	double scale = (xm - 2 * xofs) * 1.0 / (B - A);
	if (xsc == 1) { xsc = scale; }
	if (ysc == 1) { ysc = scale; }
}

double FuncGraph_creator::need_param(int i) const 
{ 
	if (param.size() < i + 1) 
		error("params vec range err"); 
	return param[i]; 
}

void FuncGraph_creator::set_param_num(int n)
{ 
	if (n < 0) error("wrong param num");  
	param.resize(n, 0);
}

bool FuncGraph_creator::get_p()
{
	if (param.size() == p_got) { return false; }
	else { ++p_got; return true; }
}

//----------------------------------------------------------------------------

Shape* SimpDeg_creator::draw_graphic()
{
	Shape* ptr = new Func([&](double x)->double { return need_param(0) + pow(x, need_param(1)); }, left(), right(),
						  Point{ gw_xm() / 2, gw_ym() / 2 }, precision(), xscale(), yscale(), 100);
	return ptr;
}

//----------------------------------------------------------------------------

Shape* DefFunc_creator::draw_graphic()
{
	Shape* ptr = func_switch(tp);
	return ptr;
}

Shape* DefFunc_creator::func_switch(FuncType tp)
{
	switch (tp) {
	case FuncType::abs:
		return new Func([&](double x)->double { return need_param(0) + need_param(1) * x + fabs(x); }, left(), right(),
						Point{ gw_xm() / 2, gw_ym() / 2 }, precision(), xscale(), yscale(), 100);
	case FuncType::cos:
		return new Func([&](double x)->double { return need_param(0) + need_param(1) * x + cos(x); }, left(), right(),
			Point{ gw_xm() / 2, gw_ym() / 2 }, precision(), xscale(), yscale(), 100);
	case FuncType::exp:
		return new Func([&](double x)->double { return need_param(0) + need_param(1) * x + exp(x); }, left(), right(),
			Point{ gw_xm() / 2, gw_ym() / 2 }, precision(), xscale(), yscale(), 100);
	case FuncType::floor:
		return new Func([&](double x)->double { return need_param(0) + need_param(1) * x + floor(x); }, left(), right(),
			Point{ gw_xm() / 2, gw_ym() / 2 }, precision(), xscale(), yscale(), 100);
	case FuncType::log:
		return new Func([&](double x)->double { return need_param(0) + need_param(1) * x + log(x); }, left(), right(),
			Point{ gw_xm() / 2, gw_ym() / 2 }, precision(), xscale(), yscale(), 100);
	case FuncType::sin:
		return new Func([&](double x)->double { return need_param(0) + need_param(1) * x + sin(x); }, left(), right(),
			Point{ gw_xm() / 2, gw_ym() / 2 }, precision(), xscale(), yscale(), 100);
	case FuncType::tan:
		return new Func([&](double x)->double { return need_param(0) + need_param(1) * x + tan(x); }, left(), right(),
			Point{ gw_xm() / 2, gw_ym() / 2 }, precision(), xscale(), yscale(), 100);
	case FuncType::sqrt:
		return new Func([&](double x)->double { return need_param(0) + need_param(1) * x + sqrt(x); }, left(), right(),
			Point{ gw_xm() / 2, gw_ym() / 2 }, precision(), xscale(), yscale(), 100);
	case FuncType::pow:
		return new Func([&](double x)->double { return need_param(0) + need_param(1) * x + pow(x, 2); }, left(), right(),
			Point{ gw_xm() / 2, gw_ym() / 2 }, precision(), xscale(), yscale(), 100);
	default:
		return new Func([&](double x)->double { return need_param(0) + need_param(1) * x; }, left(), right(),
			Point{ gw_xm() / 2, gw_ym() / 2 }, precision(), xscale(), yscale(), 100);
	}
}

//----------------------------------------------------------------------------

Shape* DifDeg_creator::draw_graphic()
{
	Shape* ptr = new Func([&](double x)->double { 
													double sum = 0;
													for (int i{ 0 }; i < param_num(); ++i) {
														sum += need_param(i) * pow(x, i);
													}
													return sum;
												},
						  left(), right(), Point{ gw_xm() / 2, gw_ym() / 2 }, precision(), xscale(), yscale(), 100);
	return ptr;
}

//----------------------------------------------------------------------------

Func_graphics::Func_graphics(Point xy, int w, int h)
	:Window(xy, w, h, "Function select"), O{ xy },
	b_diffunc({ 20, 20 }, x_max() - 40, 20, "p0 = n; y = p0 + ... + pn * x ^ n", cb_diffunc),
	b_simpdeg({ 20, 50 }, x_max() - 40, 20, "y = p0 + p1 * x + p2 * x ^ p3", cb_simpdeg),
	b_cos({ 20, 80 }, x_max() - 40, 20, "y = p0 + p1 * x + cos(x)", cb_cos),
	b_sin({ 20, 110 }, x_max() - 40, 20, "y = p0 + p1 * x + sin(x)", cb_sin),
	b_exp({ 20, 140 }, x_max() - 40, 20, "y = p0 + p1 * x + exp(x)", cb_exp),
	b_log({ 20, 170 }, x_max() - 40, 20, "y = p0 + p1 * x + log(x)", cb_log),
	b_tan({ 20, 200 }, x_max() - 40, 20, "y = p0 + p1 * x + tan(x)", cb_tan),
	b_stair({ 20, 230 }, x_max() - 40, 20, "y = p0 + p1 * x + extrapol(x)", cb_stair),
	b_quit({ 20, 260 }, x_max() - 40, 20, "Quit and close all", cb_quit)
{
	attach(b_diffunc);
	attach(b_simpdeg);
	attach(b_cos);
	attach(b_sin);
	attach(b_exp);
	attach(b_log);
	attach(b_tan);
	attach(b_stair);
	attach(b_quit);
}

//----------------------------------------------------------------------------
