#include "my_graph.h"

const double pi{ 3.14159265 };

//----------------------------------------------------------------------------

void Arc::draw_lines() const
{
	if (fill_color().visibility()) {
		fl_color(fill_color().as_int());
		fl_pie(point(0).x, point(0).y, w + w, h + h, d1, d2);
	}
	if (color().visibility()) {
		fl_color(color().as_int());
		fl_arc(point(0).x, point(0).y, w + w, h + h, d1, d2);
	}
}

void Arc::set_fangle(double deg)
{
	if (deg > d2) error("first angle must smaller then second");
	d1 = deg;
}

void Arc::set_sangle(double deg)
{
	if (deg < d1) error("second angle must be bigger then first");
	d2 = deg;
}

//----------------------------------------------------------------------------

void Box::draw_lines() const
{
	if (fill_color().visibility()) {
		fl_color(fill_color().as_int());
		fl_rectf(point(0).x, point(0).y + r, w, h - 2 * r);
		fl_rectf(point(0).x + r, point(0).y, w - 2 * r, h);
		fl_pie(point(0).x, point(0).y, r + r, r + r, 90, 180);
		fl_pie(point(0).x + w - 2 * r, point(0).y, r + r, r + r, 0, 90);
		fl_pie(point(0).x + w - 2 * r, point(0).y + h - 2 * r, r + r, r + r, 270, 360);
		fl_pie(point(0).x, point(0).y + h - 2 * r, r + r, r + r, 180, 270);
	}
	if (color().visibility()) {
		fl_color(color().as_int());
		fl_line(point(0).x + r, point(0).y, point(0).x + w - r, point(0).y);
		fl_line(point(0).x + r, point(0).y + h, point(0).x + w - r, point(0).y + h);
		fl_line(point(0).x, point(0).y + r, point(0).x, point(0).y + h - r);
		fl_line(point(0).x + w, point(0).y + r, point(0).x + w, point(0).y + h - r);
		fl_arc(point(0).x, point(0).y, r + r, r + r, 90, 180);
		fl_arc(point(0).x + w - 2 * r, point(0).y, r + r, r + r, 0, 90);
		fl_arc(point(0).x + w - 2 * r, point(0).y + h - 2 * r, r + r, r + r, 270, 360);
		fl_arc(point(0).x, point(0).y + h - 2 * r, r + r, r + r, 180, 270);
	}
}

void Text_box::draw_lines() const
{
	Box::draw_lines();

	int ofnt = fl_font();
	int osz = fl_size();
	fl_font(fnt.as_int(), fnt_sz);
	fl_draw(lab.c_str(), point(0).x + Box::radius(), 
			point(0).y + Box::height() - Box::radius() * 1.3);
	fl_font(ofnt, osz);
}

//----------------------------------------------------------------------------

void Arrow::draw_lines() const
{
	if (color().visibility()) {
		double L{ sqrt(pow(point(0).x - point(1).x, 2) + pow(point(0).y - point(1).y, 2)) };

		double mid_x = l / L * point(0).x + (1 - l / L) * point(1).x;
		double mid_y = l / L * point(0).y + (1 - l / L) * point(1).y;

		double al_x = mid_x + w / L * (point(1).y - point(0).y);
		double al_y = mid_y + w / L * (point(0).x - point(1).x);

		double ar_x = mid_x + w / L * (point(0).y - point(1).y);
		double ar_y = mid_y + w / L * (point(1).x - point(0).x);

		fl_line(point(0).x, point(0).y, point(1).x, point(1).y);
		fl_line(point(1).x, point(1).y, al_x, al_y);
		fl_line(point(1).x, point(1).y, ar_x, ar_y);
	}
}

//----------------------------------------------------------------------------

Point n(Graph_lib::Rectangle r)
{
	return Point{ r.point(0).x + r.width() / 2, r.point(0).y };
}

Point s(Graph_lib::Rectangle r)
{
	return Point{ r.point(1).x - r.width() / 2, r.point(1).y };
}

Point e(Graph_lib::Rectangle r)
{
	return Point{ r.point(1).x, r.point(1).y - r.height() / 2 };
}

Point w(Graph_lib::Rectangle r)
{
	return Point{ r.point(0).x, r.point(0).y + r.height() / 2 };
}

Point center(Graph_lib::Rectangle r)
{
	return Point{ r.point(0).x + r.width() / 2, 
				  r.point(0).y + r.height() / 2 };
}

Point ne(Graph_lib::Rectangle r)
{
	return Point{ r.point(1).x, r.point(0).y };
}

Point se(Graph_lib::Rectangle r)
{
	return Point{ r.point(1).x, r.point(1).y };
}

Point sw(Graph_lib::Rectangle r)
{
	return Point{ r.point(0).x, r.point(1).y };
}

Point nw(Graph_lib::Rectangle r)
{
	return Point{ r.point(0).x, r.point(0).y };
}

//----------------------------------------------------------------------------

Point n(Graph_lib::Circle c)
{
	return Point{ c.center().x, c.center().y - c.radius() };
}

Point s(Graph_lib::Circle c)
{
	return Point{ c.center().x, c.center().y + c.radius() };
}

Point e(Graph_lib::Circle c)
{
	return Point{ c.center().x + c.radius(), c.center().y };
}

Point w(Graph_lib::Circle c)
{
	return Point{ c.center().x - c.radius(), c.center().y };
}

Point ne(Graph_lib::Circle* c)
{
	return Point{ c->center().x + int(c->radius() * sin(45 * pi / 180)),
				  c->center().y - int(c->radius() * sin(45 * pi / 180)) };
}

Point se(Graph_lib::Circle* c)
{
	return Point{ c->center().x + int(c->radius() * sin(45 * pi / 180)),
				  c->center().y + int(c->radius() * sin(45 * pi / 180)) };
}

Point sw(Graph_lib::Circle* c)
{
	return Point{ c->center().x - int(c->radius() * sin(45 * pi / 180)),
				  c->center().y + int(c->radius() * sin(45 * pi / 180)) };
}

Point nw(Graph_lib::Circle* c)
{
	return Point{ c->center().x - int(c->radius() * sin(45 * pi / 180)),
				  c->center().y - int(c->radius() * sin(45 * pi / 180)) };
}

//----------------------------------------------------------------------------

Point n(Graph_lib::Ellipse* e)
{
	return Point{ e->center().x, e->center().y - e->minor() };
}

Point s(Graph_lib::Ellipse* e)
{
	return Point{ e->center().x, e->center().y + e->minor() };
}

Point e(Graph_lib::Ellipse* e)
{
	return Point{ e->center().x + e->major(), e->center().y };
}

Point w(Graph_lib::Ellipse* e)
{
	return Point{ e->center().x - e->major(), e->center().y };
}

//----------------------------------------------------------------------------

Regular_hexagon::Regular_hexagon(Point p, int rr)
	:r{rr}, h{ int(r * sin(60 * pi / 180)) }
{
	add(Point{ p.x - r, p.y - h });
}

Point Regular_hexagon::center() const
{
	return Point{ point(0).x + r, point(0).y + h };
}

void Regular_hexagon::set_radius(int rr)
{
	r = rr;
	h = rr * sin(60 * pi / 180);
}

void Regular_hexagon::set_height(int hh)
{
	h = hh;
	r = hh * 1.0 / sin(60 * pi / 180);
}

void Regular_hexagon::draw_lines() const
{
	if (fill_color().visibility()) {
		fl_color(fill_color().as_int());
		fl_begin_complex_polygon();
		fl_vertex(point(0).x + r * 0.5, point(0).y);
		fl_vertex(point(0).x + r * 1.5, point(0).y);
		fl_vertex(center().x + r, center().y);
		fl_vertex(center().x + r * 0.5, center().y + h);
		fl_vertex(center().x - r * 0.5, center().y + h);
		fl_vertex(center().x - r, center().y);
		fl_end_complex_polygon();
		fl_color(color().as_int());    // reset color
	}
	if (color().visibility()) {
		fl_line(point(0).x + r *0.5, point(0).y, point(0).x + r * 1.5, point(0).y);
		fl_line(point(0).x + r * 1.5, point(0).y, center().x + r, center().y);
		fl_line(center().x + r, center().y, center().x + r * 0.5, center().y + h);
		fl_line(center().x + r * 0.5, center().y + h, center().x - r * 0.5, center().y + h);
		fl_line(center().x - r * 0.5, center().y + h, center().x - r, center().y);
		fl_line(center().x - r, center().y, point(0).x + r * 0.5, point(0).y);
	}
}

//----------------------------------------------------------------------------

void Regular_polygon::point_search()
{
	Point zero{ point(0) };
	clear_points();
	add(zero);

	double alph{ 2 * pi / n };

	for (int i{ 1 }; i < n; ++i) {
		int x = center().x + r * cos(alph * i + pi);
		int y = center().y + r * sin(alph * i + pi);
		add(Point{ x, y });
	}
}

//----------------------------------------------------------------------------

void Right_triangle::draw_lines() const
{
	if (!(color().visibility() || fill_color().visibility()))
		return;

	double azimut = acos((point(1).x - center().x) * 1.0 / radius());
	if (asin((point(1).y - center().y) * 1.0 / radius()) < 0)
		azimut = 2 * pi - azimut;

	Point p3{ center().x + int(radius() * cos(azimut + deg * pi / 180)),
			  center().y + int(radius() * sin(azimut + deg * pi / 180)) };

	if (fill_color().visibility()) {
		fl_color(fill_color().as_int());
		fl_begin_complex_polygon();
		fl_vertex(point(0).x, point(0).y);
		fl_vertex(point(1).x, point(1).y);
		fl_vertex(p3.x, p3.y);
		fl_end_complex_polygon();
		fl_color(color().as_int());    // reset color
	}

	if (color().visibility()) {
		fl_line(point(0).x, point(0).y, point(1).x, point(1).y);
		fl_line(point(1).x, point(1).y, p3.x, p3.y);
		fl_line(p3.x, p3.y, point(0).x, point(0).y);
	}
}

//----------------------------------------------------------------------------

Poly::Simp_func_coef get_sfnc_coef(const int& x1, const int& y1, const int& x2, const int& y2)
{
	if (y1 == y2) return Poly::Simp_func_coef{ 0, double(y1) };
	if (x1 == x2) return Poly::Simp_func_coef{ NULL, double(x1) };

	double b = (x1 * y2 - x2 * y1) * 1.0 / (x1 - x2);
	double k = (y1 - b) * 1.0 / x1;
	if (x1 == 0) k = (y2 - b) * 1.0 / x2;
	else		 k = (y1 - b) * 1.0 / x1;

	return Poly::Simp_func_coef{ k, b };
}

Poly::Mpoint get_cross_point(const Point& p1, const Point& p2, const Point& p3, const Point& p4)
{
	Poly::Simp_func_coef cf1{ get_sfnc_coef(p1.x, p1.y, p2.x, p2.y) };
	Poly::Simp_func_coef cf2{ get_sfnc_coef(p3.x, p3.y, p4.x, p4.y) };

	if (cf1.k == 0) return Poly::Mpoint{ (cf1.b - cf2.b) / cf2.k, cf1.b };
	if (cf2.k == 0) return Poly::Mpoint{ (cf2.b - cf1.b) / cf1.k, cf2.b };

	if (cf1.k == NULL) return Poly::Mpoint{ cf1.b, cf2.k * cf1.b + cf2.b };
	if (cf2.k == NULL) return Poly::Mpoint{ cf2.b, cf1.k * cf2.b + cf1.b };

	double x = (cf2.b - cf1.b) * 1.0 / (cf1.k - cf2.k);
	double y = cf1.k * x + cf1.b;

	return Poly::Mpoint{ x, y };
}

bool segments_overlap(const Point& p1, const Point& p2, const Point& p3, const Point& p4)
try{
	if (parallel_segments(p1, p2, p3, p4)) return false;

	Poly::Mpoint cross_point{ get_cross_point(p1, p2, p3, p4) };
	
	if (point_in_cube(p1, p2, cross_point) && point_in_cube(p3, p4, cross_point))
		return true;

	return false;
}
catch (exception& e) {
	if (e.what() != "simular segments") throw e;

	if (point_in_cube(p1, p2, p3) || point_in_cube(p1, p2, p4) ||
		point_in_cube(p3, p4, p1) || point_in_cube(p3, p4, p2))
		return true;
	
	return false;
}

bool parallel_segments(const Point& p1, const Point& p2, const Point& p3, const Point& p4)
{
	Poly::Simp_func_coef cf1{ get_sfnc_coef(p1.x, p1.y, p2.x, p2.y) };
	Poly::Simp_func_coef cf2{ get_sfnc_coef(p3.x, p3.y, p4.x, p4.y) };

	if (cf1.k == cf2.k && cf1.b == cf2.b) error("simular segments");
	if (cf1.k == cf2.k) return true;
	return false;
}

bool point_in_cube(const Point& p1, const Point& p2, const Poly::Mpoint& p3)
{
	double x1, x2, x3{ p3.x };
	if (p1.x < p2.x) { x1 = p1.x; x2 = p2.x; }
	else			 { x1 = p2.x; x2 = p1.x; }

	double y1, y2, y3{ p3.y };
	if (p1.y < p2.y) { y1 = p1.y; y2 = p2.y; }
	else			 { y1 = p2.y; y2 = p1.y; }

	if ((x1 <= x3 && x3 <= x2) && (y1 <= y3 && y3 <= y2))
		return true;

	return false;
}

Poly::Poly(initializer_list<Point> lst)
{
	if (lst.size() < 3) error("too few points in Poly");
	for (Point p : lst) add(p);

	int n = number_of_points();
	for (int i{ 0 }; i < n; ++i)
		for (int j{ 0 }; j < n; ++j) {
			if (j == i - 1 || j == i + 1 || j == i ||
				(j == n - 1 && i == 0) || 
				(j == 0 && i == n - 1))
				continue;

			if (segments_overlap(point(i), point(i == n - 1 ? 0 : i + 1),
								 point(j), point(j == n - 1 ? 0 : j + 1)))
				error("crossing lines in Poly");
		}
}

//----------------------------------------------------------------------------

void Star::point_search()
{
	Point zero{ point(0) };
	clear_points();
	add(zero);

	double alph{ 2 * pi / n };
	int x, y;

	for (int i{ 1 }; i < n; ++i) {
		x = center().x + r * 0.35 * cos(alph * i + pi - alph * 0.5);
		y = center().y + r * 0.35 * sin(alph * i + pi - alph * 0.5);
		add(Point{ x, y });

		x = center().x + r * cos(alph * i + pi);
		y = center().y + r * sin(alph * i + pi);
		add(Point{ x, y });
	}

	x = center().x + r * 0.35 * cos(alph * n + pi - alph * 0.5);
	y = center().y + r * 0.35 * sin(alph * n + pi - alph * 0.5);
	add(Point{ x, y });
}

//----------------------------------------------------------------------------
