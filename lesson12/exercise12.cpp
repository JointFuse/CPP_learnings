#include "Graph.h"
#include "Simple_window.h"
#include <cmath>

void superelips_poly(Simple_window& win, double m, double n, int a, int b, int N);
void superelips_line(Simple_window& win, double m, double n, int a, int b, int N);

const int frame{ 50 };

int main()
try{
	using namespace Graph_lib;
	double m{0}, n{0};
	int N{ 0 }, a{ 0 }, b{ 0 };
	cin >> m >> n >> a >> b >> N;
	while (m <= 0 || n <= 0 || a <= 0 || b <= 0 || N <= 0) {
		cout << "All nums must be higher then zero!";
		cin >> m >> n >> a >> b >> N;
	}
	
	Simple_window win{ Point{100, 100}, 500, 500, "Super elips" };
	superelips_line(win, m, n, a, b, N);
	win.wait_for_button();
}
catch (exception& e) {
	cout << "Exception: " << e.what() << endl;
	return 1;
}
catch (...) {
	cout << "Unlnown error!" << endl;
	return 2;
}

Color rainbow()
{
	static int num{ 0 };
	++num;
	if (num == 15) num = 1;
	switch (num) {
	case 1:	return Color::red;
	case 2:	return Color::blue;
	case 3:	return Color::green;
	case 4:	return Color::yellow;
	case 5:	return Color::white;
	case 6:	return Color::black;
	case 7:	return Color::magenta;
	case 8: return Color::cyan;
	case 9: return Color::dark_red;
	case 10: return Color::dark_blue;
	case 11: return Color::dark_green;
	case 12: return Color::dark_yellow;
	case 13: return Color::dark_magenta;
	case 14: return Color::dark_cyan;
	default: return Color::black;
	}
}

void superelips_poly(Simple_window& win, double m, double n, int a, int b, int N)
{
	Point zero{ a + frame, b + frame };
	static Polygon figure;

	int N2{ N - N / 2 - 1};
	N -= N2 + 2;

	for (int x{ -a }; x < a; x += 2 * a / N) {
		int xx = zero.x + x;
		int yy = zero.y + b * pow(1 - pow(x < 0 ? -x * 1.0 / a : x * 1.0 / a, m), 1 / n);
		try { figure.add(Point{ xx, yy }); }
		catch (exception& e) {
			figure.set_point(figure.number_of_points() - 1, Point{ xx, yy });
		}
	}
	for (int x{ a }; x > -a; x -= 2 * a / N2) {
		int xx = zero.x + x;
		int yy = zero.y - b * pow(1 - pow(x < 0 ? -x * 1.0 / a : x * 1.0 / a, m), 1 / n);
		try { figure.add(Point{ xx, yy }); }
		catch (exception& e) { 
			figure.set_point(figure.number_of_points() - 1, Point{ xx, yy }); 
		}
	}

	win.attach(figure);
}

void superelips_line(Simple_window& win, double m, double n, int a, int b, int N)
{
	Point zero{ a + frame, b + frame };
	vector<Point> points;
	static vector<Line> lines;

	int N2{ N - N / 2 - 1 };
	N -= N2 + 2;

	for (int x{ -a }; x < a; x += 2 * a / N) {
		int xx = zero.x + x;
		int yy = zero.y + b * pow(1 - pow(x < 0 ? -x * 1.0 / a : x * 1.0 / a, m), 1 / n);
		points.push_back(Point{ xx, yy });
	}
	for (int x{ a }; x > -a; x -= 2 * a / N2) {
		int xx = zero.x + x;
		int yy = zero.y - b * pow(1 - pow(x < 0 ? -x * 1.0 / a : x * 1.0 / a, m), 1 / n);
		points.push_back(Point{ xx, yy });
	}

	for (int i{ 1 }; i < points.size(); ++i) {
		lines.push_back(Line{ points[i - 1], points[i] });
	}

	for (Line& l : lines) {
		l.set_color(rainbow());
		win.attach(l);
	}
}