#include "Simple_window.h"
#include "my_graph.h"

double sloping_cos(double x) { return cos(x) + x / 2; }

extern void first_half();
extern bool is_name(const string&);

struct Person {
	Person(string first_name = "default", string last_name = "default", int age = 0) 
		:fn(first_name), ln(last_name), a(age)
	{ 
		if (150 < a || a < 0) error("imposible age");
		if (!is_name(fn) || !is_name(ln)) error("name can't keep sign");
	}

	string first_name()	const { return fn; }
	string last_name()	const { return ln; }
	int age()	const { return a; }

	Person& operator= (const Person& p)
	{
		this->fn = p.fn;
		this->ln = p.ln;
		this->a = p.a;
		return *this;
	}
private:
	string fn;
	string ln;
	int a;
};

ostream& operator<< (ostream&, const Person&);
istream& operator>> (istream&, Person&);

class Scale {
	int cbase;
	int vbase;
	double scale;
public:
	Scale(int b, int vb, double s) :cbase(b), vbase(vb), scale(s)
	{ }
	int operator() (int v) const
	{ return cbase + (v - vbase) * scale;	}
};

int main()
try {
	Person gof;
	while(!(cin >> gof)) { }
	cout << gof;

	return 0;
}
catch (exception& e) {
	cout << "Exception: " << e.what() << endl;
	return 1;
}
catch (...) {
	cout << "Error" << endl;
	return 2;
}

ostream& operator<< (ostream& os, const Person& p)
{ 
	return os << "First name: " << p.first_name()
			  << " Last name: " << p.last_name()
			  << " Age: " << p.age() << '\n';
}

istream& operator>> (istream& is, Person& p)
{
	string first_name, last_name;
	int age;

	is >> first_name;
	if (!is_name(first_name)) {
		is.clear(ios_base::failbit);
		return is;
	}

	is >> last_name;
	if (!is_name(last_name)) {
		is.clear(ios_base::failbit);
		return is;
	}

	is >> age;
	p = Person(first_name, last_name, age);

	return is;
}

bool is_name(const string& nn)
{
	istringstream name(nn);
	if (!name) error("can't read name");

	char ch;
	while(name >> ch)
		switch (ch) {
		case ';': case ':': case '"': case '\'': case '[': case ']': case '*': 
		case '&': case '^': case '%': case '$': case '#': case '@': case '!':
			return false;
		default: { }
		}

	return true;
}

void first_half()
{
	constexpr int xmax{ 600 };
	constexpr int ymax{ 600 };

	constexpr int x_orig{ xmax / 2 };
	constexpr int y_orig{ ymax / 2 };
	const Point orig{ x_orig, y_orig };

	constexpr int xoffset{ 100 };
	constexpr int yoffset{ 100 };

	constexpr int xspace{ 100 };
	constexpr int yspace{ 100 };

	constexpr int xlength{ xmax - xoffset - xspace };
	constexpr int ylength{ ymax - yoffset - yspace };

	constexpr int xscale{ 20 };
	constexpr int yscale{ 20 };

	Simple_window  win({ 50, 50 }, xmax, ymax, "графики функций");

	Scale xs(x_orig, 0, xscale);
	Scale ys(y_orig, 0, -yscale);

	Axis Ox(Axis::x, { orig.x - xlength / 2, orig.y }, xlength, xlength / xscale, "1 == 20 пикселей");
	Axis Oy(Axis::y, { orig.x, orig.y + ylength / 2 }, ylength, ylength / yscale, "1 == 20 пикселей");

	Ox.set_color(Graph_lib::Color::red);
	Oy.set_color(Graph_lib::Color::red);
	Ox.label.move(-40, 0);
	Oy.label.move(-40, 0);

	win.attach(Ox);
	win.attach(Oy);

	constexpr int funcmin{ -10 };
	constexpr int funcmax{ 11 };

	constexpr int funcpoints{ 400 };

	Function one([](double) { return 1.0; }, funcmin, funcmax, orig, funcpoints, xscale, yscale);
	Text one_mark({ xs(-12), ys(1) }, "one");
	win.attach(one);
	win.attach(one_mark);

	Function slope([](double x) { return x / 2; }, funcmin, funcmax, orig, funcpoints, xscale, yscale);
	Text slope_mark({ xs(-12), ys(-5) }, "x/2");
	win.attach(slope);
	win.attach(slope_mark);

	Function square([](double x)->double { return x * x; }, -sqrt(10), sqrt(10), orig, funcpoints, xscale, yscale);
	win.attach(square);

	Function cosinus(cos, funcmin, funcmax, orig, funcpoints, xscale, yscale);
	cosinus.set_color(Graph_lib::Color::blue);
	win.attach(cosinus);

	Function slopcos(sloping_cos, funcmin, funcmax, orig, funcpoints, xscale, yscale);
	win.attach(slopcos);

	win.wait_for_button();
}