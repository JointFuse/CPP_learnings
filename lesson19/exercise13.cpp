#include "Lesson19.h"

using namespace MyLib;

Tracer glob("global create", "global destroy");

void f(Tracer tr)
{
	cout << "f() start\n";
	Tracer loc("local create", "local destroy");
	tr = loc;
	cout << "f() ends\n";
}

class A {
	Tracer tr{"class create", "class destroy"};
};

int main()
{
	A aa;
	f(glob);
	Tracer* ptr = new Tracer("dynamic create", "dynamic destroy");
	Tracer tt{glob};
	*ptr = tt;
	f(*ptr);
	delete ptr;

	return 0;
}