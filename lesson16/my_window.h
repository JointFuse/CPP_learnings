#ifndef my_window_h
#define my_window_h

#include "Window.h"
#include "Simple_window.h"
#include "my_graph.h"
#include <time.h>
#include "include/finance.h"
#include "include/calculator.h"

namespace Windows_h {
#include <Windows.h>
}
//----------------------------------------------------------------------------

using namespace Graph_lib;

//----------------------------------------------------------------------------


struct Lines_window : Window {
	Lines_window(Point xy, int w, int h,
				 const string& title);
private:
	// Data
	Open_polyline lines;
	
	// Vidgets
	Button next_button;
	Button quit_button;
	In_box next_x;
	In_box next_y;
	Out_box xy_out;
	Menu color_menu;
	Menu style_menu;
	Button color_button;
	Button style_button;

	void change_color(Color c)			{ lines.set_color(c); }
	void change_style(Line_style sty)	{ lines.set_style(sty); }

	void hide_colors() { color_menu.hide(); color_button.show(); }
	void hide_styles() { style_menu.hide(); style_button.show(); }

	// call back deals
	void red_pressed()		{ change_color(Color::red); hide_colors(); }
	void blue_pressed()		{ change_color(Color::blue); hide_colors(); }
	void black_pressed()	{ change_color(Color::black); hide_colors(); }
	void colmenu_pressed()	{ color_button.hide(); color_menu.show(); }

	void dot_pressed()		{ change_style(Line_style(Line_style::dot, 2)); hide_styles(); }
	void solid_pressed()	{ change_style(Line_style(Line_style::solid, 2)); hide_styles(); }
	void dashdot_pressed()	{ change_style(Line_style(Line_style::dashdot, 2)); hide_styles(); }
	void stymenu_pressed()	{ style_button.hide(); style_menu.show(); }

	void next();
	void quit();

	// call back functions
	static void cb_red(Address, Address pw)		{ reference_to<Lines_window>(pw).red_pressed(); }
	static void cb_blue(Address, Address pw)	{ reference_to<Lines_window>(pw).blue_pressed(); }
	static void cb_black(Address, Address pw)	{ reference_to<Lines_window>(pw).black_pressed(); }
	static void cb_colmenu(Address, Address pw) { reference_to<Lines_window>(pw).colmenu_pressed(); }
	static void cb_dot(Address, Address pw)		{ reference_to<Lines_window>(pw).dot_pressed(); }
	static void cb_solid(Address, Address pw)	{ reference_to<Lines_window>(pw).solid_pressed(); }
	static void cb_dashdot(Address, Address pw) { reference_to<Lines_window>(pw).dashdot_pressed(); }
	static void cb_stymenu(Address, Address pw) { reference_to<Lines_window>(pw).stymenu_pressed(); }
	static void cb_next(Address, Address pw)	{ reference_to<Lines_window>(pw).next(); }
	static void cb_quit(Address, Address pw)	{ reference_to<Lines_window>(pw).quit(); }
};

//----------------------------------------------------------------------------

struct My_window : Simple_window {
	My_window(Point xy, int width, int height, const string& title, bool hide_next = false);
private:
	Button quit_button;

	static void cb_quit(Address, Address pw) { reference_to<My_window>(pw).quit(); }
	void quit() { hide(); }
};

//----------------------------------------------------------------------------

class Button_matrix : My_window {
	Square_desk mask;
	Button b0;
	Button b1;
	Button b2;
	Button b3;
	Button b4;
	Button b5;
	Button b6;
	Button b7;
	Button b8;
	Button b9;
	Button b10;
	Button b11;
	Button b12;
	Button b13;
	Button b14;
	Button b15;

	void do_it(int i);

	static void cb_b0(Address, Address pw) { reference_to<Button_matrix>(pw).do_it(0); }
	static void cb_b1(Address, Address pw) { reference_to<Button_matrix>(pw).do_it(1); }
	static void cb_b2(Address, Address pw) { reference_to<Button_matrix>(pw).do_it(2); }
	static void cb_b3(Address, Address pw) { reference_to<Button_matrix>(pw).do_it(3); }
	static void cb_b4(Address, Address pw) { reference_to<Button_matrix>(pw).do_it(4); }
	static void cb_b5(Address, Address pw) { reference_to<Button_matrix>(pw).do_it(5); }
	static void cb_b6(Address, Address pw) { reference_to<Button_matrix>(pw).do_it(6); }
	static void cb_b7(Address, Address pw) { reference_to<Button_matrix>(pw).do_it(7); }
	static void cb_b8(Address, Address pw) { reference_to<Button_matrix>(pw).do_it(8); }
	static void cb_b9(Address, Address pw) { reference_to<Button_matrix>(pw).do_it(9); }
	static void cb_b10(Address, Address pw) { reference_to<Button_matrix>(pw).do_it(10); }
	static void cb_b11(Address, Address pw) { reference_to<Button_matrix>(pw).do_it(11); }
	static void cb_b12(Address, Address pw) { reference_to<Button_matrix>(pw).do_it(12); }
	static void cb_b13(Address, Address pw) { reference_to<Button_matrix>(pw).do_it(13); }
	static void cb_b14(Address, Address pw) { reference_to<Button_matrix>(pw).do_it(14); }
	static void cb_b15(Address, Address pw) { reference_to<Button_matrix>(pw).do_it(15); }
public:
	Button_matrix(Point xy, int width, int length, int but_size);
};

//----------------------------------------------------------------------------

class Moving_image : My_window {
	Image pic;
	Button move_pic;

	void move_but();
public:
	Moving_image();
};

//----------------------------------------------------------------------------

class Figures : protected Window {
protected:
	// Data
	Vector_ref<Shape> obj;
private:
	double scale{ 0.2 };

	// Processing
	enum Function_vec {
		f_circle, f_square,
		f_triangle, f_hexagon
	};
	Function_vec cur_f{ f_circle };
protected:
	virtual void draw_shape();
private:
	// Vidgets
	Button b_next;
	Button b_quit;
protected:
	In_box x_new;
	In_box y_new;
private:
	Menu m_forms;
	Button b_menu;

	// Shape deal functions
	void draw_circle(int, int, int);
	void draw_square(int, int, int);
	void draw_triangle(int, int, int);
	void draw_hexagon(int, int, int);

	// Vidgets deals
	virtual void next()	{ draw_shape(); redraw(); }
	void quit() { hide(); }

	void bp_menu()		{ b_menu.hide(); m_forms.show(); }
protected:
	virtual void bp_circle()	{ cur_f = f_circle; m_forms.hide(); b_menu.show(); }
	virtual void bp_square()	{ cur_f = f_square; m_forms.hide(); b_menu.show(); }
	virtual void bp_triangle()	{ cur_f = f_triangle; m_forms.hide(); b_menu.show(); }
	virtual void bp_hexagon()	{ cur_f = f_hexagon; m_forms.hide(); b_menu.show(); }
private:
	// Call back functions
	static void cb_next(Address, Address pw)	{ reference_to<Figures>(pw).next(); }
	static void cb_quit(Address, Address pw)	{ reference_to<Figures>(pw).quit(); }

	static void cb_menu(Address, Address pw)	{ reference_to<Figures>(pw).bp_menu(); }

	static void cb_circle(Address, Address pw)	{ reference_to<Figures>(pw).bp_circle(); }
	static void cb_square(Address, Address pw)	{ reference_to<Figures>(pw).bp_square(); }
	static void cb_triangle(Address, Address pw){ reference_to<Figures>(pw).bp_triangle(); }
	static void cb_hexagon(Address, Address pw)	{ reference_to<Figures>(pw).bp_hexagon(); }
public:
	Figures(Point xy, int width = 400, int height = 300, const string& label = "Figures");
};

//----------------------------------------------------------------------------

class Moving_figure : Figures {
	void draw_shape() override;

	// Vidgets deals
	void next() override;

	void bp_circle()	override { Figures::bp_circle(); draw_shape(); }
	void bp_square()	override { Figures::bp_square(); draw_shape(); }
	void bp_triangle()	override { Figures::bp_triangle(); draw_shape(); }
	void bp_hexagon()	override { Figures::bp_hexagon(); draw_shape(); }
public:
	Figures::Figures;
};

//----------------------------------------------------------------------------

class Clock : Window {
	// Graphics
	Image back;
	Sec_arr sec;
	Min_arr mins;
	Hour_arr hour;
	Text quit_instruct;

	// Vidget
	Button b_quit;

	void bp_quit()							{ hide(); error("programm stop complete"); }
	static void cb_quit(Address, Address pw){ reference_to<Clock>(pw).bp_quit(); }

	// Soccet
	void tick_tak()
	{
		while (true) {
			Fl::redraw();
			Fl::wait();
			Windows_h::Sleep(1000);
			sec.tick();
			mins.tick();
			if(mins.is_hour())
				hour.tick();
		}
	}

	void set_time()
	{
		time_t code_time;
		time(&code_time);

		struct tm* rawtime = localtime(&code_time);

		sec.set(59 < rawtime->tm_sec ? 0 : rawtime->tm_sec);
		mins.set(rawtime->tm_min * 60 + sec.current());
		hour.set(rawtime->tm_hour);
	}
public:
	Clock(Point xy, string name);
};

//----------------------------------------------------------------------------

class Fly_plane : Window {
	// Data and control
	bool is_run{ false };
	Airplane bort;
	Plane_engine bort_eng;

	// Vidgets
	Button b_start;
	Button b_stop;
	Button b_quit;
	Button b_phion;
	Button b_phioff;

	// Vidgets functions
	void bp_start() { is_run = true; b_quit.hide(); b_stop.show(); }
	void bp_stop()	{ is_run = false; b_stop.hide(); b_quit.show(); }
	void bp_quit()	{ hide(); error("programm stop complete"); }
	void bp_phion()	{ bort_eng.damage_on(); b_phion.hide(); b_phioff.show(); }
	void bp_phioff(){ bort_eng.damage_off(); b_phioff.hide(); b_phion.show(); }

	// Call back functions
	static void cb_start(Address, Address pw)	{ reference_to<Fly_plane>(pw).bp_start(); }
	static void cb_stop(Address, Address pw)	{ reference_to<Fly_plane>(pw).bp_stop(); }
	static void cb_quit(Address, Address pw)	{ reference_to<Fly_plane>(pw).bp_quit(); }
	static void cb_phion(Address, Address pw)	{ reference_to<Fly_plane>(pw).bp_phion(); }
	static void cb_phioff(Address, Address pw)	{ reference_to<Fly_plane>(pw).bp_phioff(); }

	void soccet();		// main process function, makes plane fly
public:
	Fly_plane(Point xy, int width, int height);
};

//----------------------------------------------------------------------------

class Currency_converter : Window {
	// Data
	Finance::Money_converter engine;
	Text setting_info1;
	Text setting_info2;

	// Vidgets
	In_box box_from;
	Out_box box_to;
	In_box box_base;
	In_box box_targ;
	Button b_convert;
	Button b_quit;
	Button b_load;
	Button b_overon;
	Button b_overoff;
	Button b_setting;

	// Soccet functions
	void show_setting();

	// Button functions
	void bp_convert();
	void bp_load();
	void bp_quit()		{ hide(); error("program stoped"); }
	void bp_overon()	{ b_overon.hide(); b_overoff.show(); engine.override_on(); }
	void bp_overoff()	{ b_overoff.hide(); b_overon.show(); engine.override_off(); }
	void bp_setting()	{ show_setting(); }

	// Call back functions
	static void cb_convert(Address, Address pw)	{ reference_to<Currency_converter>(pw).bp_convert(); }
	static void cb_quit(Address, Address pw)	{ reference_to<Currency_converter>(pw).bp_quit(); }
	static void cb_load(Address, Address pw)	{ reference_to<Currency_converter>(pw).bp_load(); }
	static void cb_overon(Address, Address pw)	{ reference_to<Currency_converter>(pw).bp_overon(); }
	static void cb_overoff(Address, Address pw)	{ reference_to<Currency_converter>(pw).bp_overoff(); }
	static void cb_setting(Address, Address pw)	{ reference_to<Currency_converter>(pw).bp_setting(); }
public:
	Currency_converter(Point xy, int width, int height);
};

//----------------------------------------------------------------------------

class My_calculator : Window {
	// Vidgets
	In_box box_example;
	Out_box box_solving;
	Button b_calculate;
	Button b_help;

	// Regular functions
	void switch_stream(istringstream* in_str, ostringstream* out_str = NULL);

	// Button functions
	void bp_calculate();
	void bp_help();

	// Call back functions
	static void cb_calculate(Address, Address pw)	{ reference_to<My_calculator>(pw).bp_calculate(); }
	static void cb_help(Address, Address pw)		{ reference_to<My_calculator>(pw).bp_help(); }
public:
	My_calculator(Point xy, int width, int height);
};

//----------------------------------------------------------------------------

class FuncGraph_creator : public Window {
	// Place to store Window and Shape objects
	Vector_ref<Window>& winptr;
	Vector_ref<Shape>& shptr;

	// Graphic params
	double A{ -1 }, B{ 1 }, xsc{ 1 }, ysc{ 1 };
	int n_pts{ 100 }, p_got{ 0 };
	vector<double> param;
	bool float_param;

	// Graphic window params
	int xm{ 500 }, ym{ 500 }, xofs{ 50 }, yofs{ 50 };
	Point O;

	// Vidgets
	In_box box_A;
	In_box box_B;
	In_box box_n;
	Out_box box_name;
	In_box box_param;
	Button b_next;
	Button b_back;
	Button b_addparam;

	// Menu process functions
	void show_base();
	void show_param();

	// Button deal functions
	void bp_next();
	void bp_addparam();
	void bp_back();

	// Draw new Window with things for graphic
	Window* draw_window();
	void draw_axes();
protected:
	double xscale()	const { return xsc; }
	double yscale()	const { return ysc; }
	void set_xscale(double sc) { xsc = sc; }
	void set_yscale(double sc) { ysc = sc; }
	void auto_scale();

	double left()	const { return A; }
	double right()	const { return B; }

	int gw_xm()		const { return xm; }
	int gw_ym()		const { return ym; }
	
	int precision()	const { return n_pts; }
	void set_precision(int n) { if (n < 0) error("wrong precision"); n_pts = n; }

	double need_param(int i) const;
	int param_num()	const { return param.size(); }
	void set_param_num(int n);
	void reset_param()	  { p_got = 0; }
	bool get_p();

	// Draw function graphic
	virtual Shape* draw_graphic() = 0;

	// Call back function
	static void cb_next(Address, Address pw)	{ reference_to<FuncGraph_creator>(pw).bp_next(); }
	static void cb_addparam(Address, Address pw){ reference_to<FuncGraph_creator>(pw).bp_addparam(); }
	static void cb_back(Address, Address pw)	{ reference_to<FuncGraph_creator>(pw).bp_back(); }

	FuncGraph_creator(Point xy, Vector_ref<Window>& ptr1, Vector_ref<Shape>& ptr2, int param_num = 2, bool is_p_float = false);
 };

//----------------------------------------------------------------------------

/* Equalisation type: y = p0 + p1 * x + p2 * x ^ p3 */
class SimpDeg_creator : public FuncGraph_creator {
	Shape* draw_graphic();
public:
	SimpDeg_creator(Point xy, Vector_ref<Window>& ptr1, Vector_ref<Shape>& ptr2)
		:FuncGraph_creator(xy, ptr1, ptr2, 4) { }
};

//----------------------------------------------------------------------------

/* Equalisation type: y = p0 + p1 * x + f(x) */
class DefFunc_creator : public FuncGraph_creator {
	Shape* draw_graphic();

public:
	enum class FuncType {
		round, floor, ceil, trunc, abs,
		sqrt, cbrt, pow, exp, log, log10,
		sin, cos, tan, asin, acos, atan
	};
private:
	FuncType tp;
	Shape* func_switch(FuncType);
public:
	DefFunc_creator(Point xy, Vector_ref<Window>& ptr1, Vector_ref<Shape>& ptr2, FuncType type)
		:FuncGraph_creator(xy, ptr1, ptr2), tp{ type } { }
};

//----------------------------------------------------------------------------

/* Equalisation type: y = p0 + p1 * x ^ 1 + ... + pn * x ^ n */
class DifDeg_creator : public FuncGraph_creator {
	Shape* draw_graphic();
public:
	DifDeg_creator(Point xy, Vector_ref<Window>& ptr1, Vector_ref<Shape>& ptr2)
		:FuncGraph_creator(xy, ptr1, ptr2, 1, true) { }
};

//----------------------------------------------------------------------------

class Func_graphics : Window {
	// Data store
	Vector_ref<Window> wstore;
	Vector_ref<Shape> shstore;
	Point O;

	// Vidgets
	Button b_diffunc;
	Button b_simpdeg;
	Button b_cos;
	Button b_sin;
	Button b_exp;
	Button b_log;
	Button b_tan;
	Button b_stair;
	Button b_quit;

	// Button functions
	void bp_diffunc()	{ wstore.push_back(new DifDeg_creator({ O.x + x_max() / 2, O.y + y_max() / 2 }, wstore, shstore)); }
	void bp_simpdeg()	{ wstore.push_back(new SimpDeg_creator({ O.x + x_max() / 2, O.y + y_max() / 2 }, wstore, shstore)); }
	void bp_cos()		{ wstore.push_back(new DefFunc_creator({ O.x + x_max() / 2, O.y + y_max() / 2 }, wstore, shstore, DefFunc_creator::FuncType::cos)); }
	void bp_sin()		{ wstore.push_back(new DefFunc_creator({ O.x + x_max() / 2, O.y + y_max() / 2 }, wstore, shstore, DefFunc_creator::FuncType::sin)); }
	void bp_exp()		{ wstore.push_back(new DefFunc_creator({ O.x + x_max() / 2, O.y + y_max() / 2 }, wstore, shstore, DefFunc_creator::FuncType::exp)); }
	void bp_log()		{ wstore.push_back(new DefFunc_creator({ O.x + x_max() / 2, O.y + y_max() / 2 }, wstore, shstore, DefFunc_creator::FuncType::log)); }
	void bp_tan()		{ wstore.push_back(new DefFunc_creator({ O.x + x_max() / 2, O.y + y_max() / 2 }, wstore, shstore, DefFunc_creator::FuncType::tan)); }
	void bp_stair()		{ wstore.push_back(new DefFunc_creator({ O.x + x_max() / 2, O.y + y_max() / 2 }, wstore, shstore, DefFunc_creator::FuncType::floor)); }
	void bp_quit()		{ for (int i{ 0 }; i < wstore.size(); ++i) wstore[i].hide(); hide(); error("program stoped"); }

	// Call back functions
	static void cb_diffunc(Address, Address pw) { reference_to<Func_graphics>(pw).bp_diffunc(); }
	static void cb_simpdeg(Address, Address pw) { reference_to<Func_graphics>(pw).bp_simpdeg(); }
	static void cb_cos(Address, Address pw)		{ reference_to<Func_graphics>(pw).bp_cos(); }
	static void cb_sin(Address, Address pw)		{ reference_to<Func_graphics>(pw).bp_sin(); }
	static void cb_exp(Address, Address pw)		{ reference_to<Func_graphics>(pw).bp_exp(); }
	static void cb_log(Address, Address pw)		{ reference_to<Func_graphics>(pw).bp_log(); }
	static void cb_tan(Address, Address pw)		{ reference_to<Func_graphics>(pw).bp_tan(); }
	static void cb_stair(Address, Address pw)	{ reference_to<Func_graphics>(pw).bp_stair(); }
	static void cb_quit(Address, Address pw)	{ reference_to<Func_graphics>(pw).bp_quit(); }
public:
	Func_graphics(Point xy, int width, int height);
};

//----------------------------------------------------------------------------

#endif // my_window_h