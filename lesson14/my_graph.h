#include <std_lib_facilities.h>
#include "Graph.h"
#include "GUI.h"

const Graph_lib::Font def_font{ Graph_lib::Font::times_bold };
const int def_fnt_size{ 20 };
const int binary_tree_min_n{ 0 };
const int binary_tree_min_w{ 10 };
const int binary_tree_min_h{ 10 };

//----------------------------------------------------------------------------

enum class Connect_line {
	simple, down_arrow, up_arrow,
	text_simple, text_down_arrow, text_up_arrow
};

//----------------------------------------------------------------------------

struct Arc : Graph_lib::Shape {
	Arc(Point p, int ww, int hh, double deg1, double deg2)
		: w{ ww }, h{ hh }, d1{ deg1 }, d2{ deg2 } 
	{ 
		add(Point{ p.x - w, p.y - h });
	}

	void draw_lines()	const;

	Point center()	const { return Point{ point(0).x + w, point(0).y + h }; }

	void set_fangle(double deg);
	double fangle()	const { return d1; }

	void set_sangle(double deg);
	double sangle() const { return d2; }

	void set_major(int ww)
	{
		set_point(0, Point{ center().x - ww, center().y - h });
		w = ww;
	}
	int major()		const { return w; }

	void set_minor(int hh)
	{
		set_point(0, Point{ center().x - w, center().y - hh });
		h = hh;
	}
	int minor()		const { return h; }
private:
	int w;
	int h;
	double d1;
	double d2;
};

//----------------------------------------------------------------------------

struct Box : Graph_lib::Shape {
	Box() :w{ 2 }, h{ 2 }, r{ 1 } { }
	Box(Point p, int ww, int hh, int rr)
		: w{ ww }, h{ hh }, r{ rr }
	{
		if (w <= r || h <= r) error("sides must be bigger then radius");
		add(p); 
	}

	void draw_lines()	const;

	void set_width(int ww)
	{
		if (ww <= 0) error("width must be bigger then zero");
		if (ww <= r) error("side must be bigger then radius");
		w = ww;
	}
	int width()			const { return w; }

	void set_height(int hh)
	{
		if (hh <= 0) error("high must be bigger then zero");
		if (hh <= r) error("side must be bigger then radius");
		h = hh;
	}
	int height()			const { return h; }

	void set_radius(int rr)
	{
		if (rr <= 0) error("radius must be bigger then zero");
		if (w <= rr || h <= rr) error("radius must be smaller then sides");
		r = rr;
	}
	int radius()		const { return r; }
private:
	int w;
	int h;
	int r;
};

struct Text_box : Box {
	Text_box(Point p, const string& s)
		:lab(s), fnt(def_font), fnt_sz(def_fnt_size),
		 Box(p, int(s.size() + 3) * 0.45 * def_fnt_size, 
			 def_fnt_size * 2, def_fnt_size / 2)
	{	}

	void draw_lines() const;

	void set_text(const string& s) 
	{ 
		lab = s; 
		Box::set_width(int(s.length() + 1) * fnt_sz / 2); 
	}
	string text() const { return lab; }

	void set_font(Graph_lib::Font f) { fnt = f; }
	Graph_lib::Font font() const { return Graph_lib::Font(fnt); }

	void set_font_size(int s) 
	{ 
		fnt_sz = s;
		Box::set_height(s * 2);
		Box::set_radius(s / 2);
		Box::set_width(int(lab.length() + 1) * s / 2);
	}
	int font_size() const { return fnt_sz; }
private:
	string lab;
	Graph_lib::Font fnt;
	int fnt_sz;
};

//----------------------------------------------------------------------------

struct Arrow : Graph_lib::Line {
	Arrow(Point p1, Point p2, int ll, int ww)
		:Line{ p1, p2 }, l{ ll }, w{ ww }
	{
		if (l <= 0) error("length should be greater then zero");
		if (w <= 0) error("width should be greater then zero");
	}

	void draw_lines() const;
private:
	int w;
	int l;
};

//----------------------------------------------------------------------------

Point n(Graph_lib::Rectangle);
Point s(Graph_lib::Rectangle);
Point e(Graph_lib::Rectangle);
Point w(Graph_lib::Rectangle);

Point center(Graph_lib::Rectangle);

Point ne(Graph_lib::Rectangle);
Point se(Graph_lib::Rectangle);
Point sw(Graph_lib::Rectangle);
Point nw(Graph_lib::Rectangle);

//----------------------------------------------------------------------------

Point n(Graph_lib::Circle);
Point s(Graph_lib::Circle);
Point e(Graph_lib::Circle);
Point w(Graph_lib::Circle);

Point ne(Graph_lib::Circle*);
Point se(Graph_lib::Circle*);
Point sw(Graph_lib::Circle*);
Point nw(Graph_lib::Circle*);

//----------------------------------------------------------------------------

Point n(Graph_lib::Ellipse*);
Point s(Graph_lib::Ellipse*);
Point e(Graph_lib::Ellipse*);
Point w(Graph_lib::Ellipse*);

//----------------------------------------------------------------------------

struct Regular_hexagon : Graph_lib::Shape {
	Regular_hexagon(Point p, int rr);	// center and radius

	void draw_lines() const;

	Point center() const;

	void set_radius(int rr);
	int radius() const { return r; }

	void set_height(int hh);
	int height() const { return h; }
private:
	int r;
	int h;
};

//----------------------------------------------------------------------------

struct Regular_polygon : Graph_lib::Closed_polyline {
	Regular_polygon(Point p, int nn, int rr)
		:n{ nn }, r{ rr }
	{ 
		if (r <= 0) error("radius should be bigger then zero");
		if (n < 3) r = 3;
		add(Point{ p.x - r, p.y });
		point_search();
	}

	void set_center(Point p)
	{
		set_point(0, Point{ p.x - r, p.y });
		point_search();
	}
	Point center() const { return Point(point(0).x + r, point(0).y); }

	void set_radius(int rr)
	{
		if (r <= 0) error("radius should be bigger then zero");
		set_point(0, Point{ center().x - rr, center().y });
		r = rr;
		point_search();
	}
	int radius() const { return r; }

	void set_cornum(int nn)
	{
		n = nn;
		if (nn < 3) r = 3;
		point_search();
	}
	int cornum() const { return n; }
protected:
	void point_search();

	int n;
	int r;
};

//----------------------------------------------------------------------------

struct Right_triangle : Graph_lib::Shape {
	Right_triangle(Point p1, Point p2, double dd)
		: deg{ dd }
	{
		if (int(deg) % 180 == 0) error("angle shouldn't equal n*180");
		add(p1);
		add(p2); 
	}

	void draw_lines() const;

	int radius()	const
	{
		return sqrt(pow(point(0).x - point(1).x, 2) +
					pow(point(0).y - point(1).y, 2)) / 2;
	}

	Point center()	const
	{
		return Point{ (point(0).x + point(1).x) / 2, 
					  (point(0).y + point(1).y) / 2 };
	}

	void set_angle(double dd) { deg = dd; }
	double angle()	const	 { return deg; }
private:
	double deg;
};

//----------------------------------------------------------------------------

struct Poly : Graph_lib::Polygon {
	Poly(initializer_list<Point> lst);

	struct Simp_func_coef {
		Simp_func_coef(double kk, double bb)
			:k{ kk }, b{ bb } { }

		double k;
		double b;
	};
	
	struct Mpoint {
		Mpoint(double xx, double yy)
			:x{ xx }, y{ yy } { }
		Mpoint(Point p)
			:x{ double(p.x) }, y{ double(p.y) } { }

		double x;
		double y;
	};
};

/* ���������� ������������ �������� ��������� ���������, ������������ �� ���� ������ ������� */
Poly::Simp_func_coef get_sfnc_coef(const int& x1, const int& y1, const int& x2, const int& y2);

/* ���������� �����, � ������� ������������ ��� �����, ����������� �� ������������� */
Poly::Mpoint get_cross_point(const Point& p1, const Point& p2, const Point& p3, const Point& p4);

/* ���������, ����������� �� ����� ����������� ���� ����� �������� �������� */
bool segments_overlap(const Point& p1, const Point& p2, const Point& p3, const Point& p4);

/* ���������, ������������ �� ������� ���� ����� */
bool parallel_segments(const Point& p1, const Point& p2, const Point& p3, const Point& p4);

/* ���������, ����� �� ����� � ��������������, ������������ ���������� ����� ������� p1 � p2 */
bool point_in_cube(const Point& p1, const Point& p2, const Poly::Mpoint& p3);

//----------------------------------------------------------------------------

struct Star : Regular_polygon {
	using Regular_polygon::Regular_polygon;

	void point_search();
};

//----------------------------------------------------------------------------

struct Smiley : Graph_lib::Circle {
	using Circle::Circle;
	void draw_lines() const;
};

struct Hat_smiley : Smiley {
	using Smiley::Smiley;
	void draw_lines() const;
};

struct Frowny : Graph_lib::Circle {
	using Circle::Circle;
	void draw_lines() const;
};

struct Hat_frowny : Frowny {
	using Frowny::Frowny;
	void draw_lines() const;
};

//----------------------------------------------------------------------------

struct Immobile_circle : Graph_lib::Circle {
	using Circle::Circle;
private:
	void move(int dx, int dy) { }
};

//----------------------------------------------------------------------------

struct Striped_rectangle : Graph_lib::Rectangle {
	using Rectangle::Rectangle;
	void draw_lines() const;
};

//----------------------------------------------------------------------------

struct Striped_circle : Graph_lib::Circle {
	using Circle::Circle;
	void draw_lines() const;
};

//----------------------------------------------------------------------------

struct Striped_closed_polyline : Graph_lib::Closed_polyline {
	using Closed_polyline::Closed_polyline;
	void draw_lines() const;
};

//----------------------------------------------------------------------------

struct Octagon : Regular_polygon {
	Octagon(Point p, int rr): Regular_polygon(p, 8, rr) { }
protected:
	using Shape::set_point;
private:
	using Regular_polygon::set_cornum;
	using Shape::add;
};

//----------------------------------------------------------------------------

struct Group : Graph_lib::Shape {
	void add_shape(Shape& s) { shapes.push_back(s); }
	void add_shape(Shape* p) { shapes.push_back(p); }

	void draw() const;
	void move(int dx, int dy);

	void set_color(Graph_lib::Color col);
	void set_style(Graph_lib::Line_style sty);
	void set_fill_color(Graph_lib::Color col);

	int size() const { return shapes.size(); }

	Point point() const 
	{
		if (shapes.size() <= 0) error("there is no points in group");
		return shapes[0].point(0); 
	}
protected:
	void move(int i, int x, int y)
	{
		shapes[i].move(x, y);
	}
	void set_color(int i, Graph_lib::Color col)
	{
		shapes[i].set_color(col);
	}
	void set_style(int i, Graph_lib::Line_style sty)
	{
		shapes[i].set_style(sty);
	}
	void set_fill_color(int i, Graph_lib::Color col)
	{
		shapes[i].set_fill_color(col);
	}
private:
	Shape::set_point;

	Graph_lib::Vector_ref<Shape> shapes;
};

//----------------------------------------------------------------------------

struct Chess_desk : Group {
	Chess_desk(Point p, int size);

	int size()		const { return s; }
	
	void set_center(Point p);
	Point center()	const { return { point().x + s / 2, point().y + s / 2 }; }

	Point sector(int x, int y) const;
protected:
	Group::size;
	Group::add_shape;
	Group::set_color;
	Group::set_style;
	Group::set_fill_color;
private:
	int s;
};

//----------------------------------------------------------------------------

struct Pseudo_window : Group {
	Pseudo_window(Point p, int width, int height, const string& s);

	int width()		const { return w; }
	int height()	const { return h; }
private:
	int w;
	int h;
};

//----------------------------------------------------------------------------

struct Binary_tree : Graph_lib::Shape {
	Binary_tree(Point p, int levels, int width, int height);
	Binary_tree(Point p, int levels, int width, int height, Connect_line line);
	Binary_tree(Point p, int levels, int width, int height, Graph_lib::Color color);
	Binary_tree(Point p, int levels, int width, int height, Graph_lib::Color color, Connect_line line);

	void draw_lines() const;

	void add_text(int level, int position, const string& label);

	Point point(int i, int j) const;
protected:
	virtual void units() const;

	void calc();

	void styled_line(Point begin, Point end) const;
 
	Shape::point;
	Shape::set_color;
private:
	Shape::set_fill_color;
	Shape::set_point;

	Graph_lib::Vector_ref<Graph_lib::Text> marks;
	Connect_line lstyle = Connect_line::simple;
	Point p0;
	int fnt_size{ 10 };
	int n;
	int w;
	int h;
};

//----------------------------------------------------------------------------

struct Binary_tree_triangle : Binary_tree {
	Binary_tree::Binary_tree;
	void units() const;
};

//----------------------------------------------------------------------------

struct Controller {
	virtual void on() = 0;
	virtual void off() = 0;
	virtual void set_level(int) = 0;
	virtual void show() const = 0;
};

struct Test_control : Controller {
	Test_control() { }

	void on()	{ state = true; }
	void off()	{ state = false; }

	void set_level(int l) { level = l; }

	void show() const
	{
		cout << "\tState: <" << (state ? "on" : "off") << ">; "
			 << "Level: [ " << level << " ]\n";
	}
private:
	bool state{ false };
	int level{ 0 };
};

struct Color_control : Controller {
	Color_control(Graph_lib::Shape* p)
		: ptr{ p } { }
	
	void on()	{ ptr->set_color(Graph_lib::Color::visible); }
	void off()	{ ptr->set_color(Graph_lib::Color::invisible); }

	void set_level(int l)
	{
		if (l < 0) error("color is a positive number");
		ptr->set_color(Graph_lib::Color(l % 256));
	}

	void show() const 
	{
		cout << "State: <" << (ptr->color().visibility() == 0 ? "off" : "on") << ">; "
			 << "Color: [ " << ptr->color().as_int() << " ]\n";
	}
private:
	Graph_lib::Shape* ptr;
};

//----------------------------------------------------------------------------
