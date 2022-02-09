#include "Simple_window.h"
#include "my_graph.h"

class B1 {
public:
	virtual void vf() const { cout << "B1::vf()\n"; }
	void f() const { cout << "B1::f()\n"; }
	virtual void pvf() = 0;
};

class D1 : public B1 {
public:
	void vf() const { cout << "D1::vf()\n"; }
	void f() const { cout << "D1::f()\n"; }
};

class D2 : public D1 {
public:
	void pvf() { cout << "D2::pvf()\n"; }
};

class B2 {
public:
	virtual void pvf() const = 0;
};

class D21 : public B2 {
	string line;
public:
	D21(const string& s) : line{ s } { }
	void pvf() const { cout << line << '\n'; }
};

class D22 : public B2 {
	int num;
public:
	D22(const int& n) : num{ n } { }
	void pvf() const { cout << num << '\n'; }
};

void f(const B2& b2)
{
	b2.pvf();
}

int main()
try {
	f(D21("D21::pvf()"));
	f(D22(22));

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