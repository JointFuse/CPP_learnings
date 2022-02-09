#include <std_lib_facilities.h>

struct Iterat {
	virtual double* next() = 0;
protected:
	Iterat() { }
private:
	Iterat(const Iterat&);
	Iterat& operator= (const Iterat&);
};

struct Vector_iterator : Iterat {
	Vector_iterator() { }
	Vector_iterator(const vector<double>& vec)
		: buf(vec) { }

	double* next()
	{
		static int i{ 0 };
		
		if (buf.size() == 0 || i == buf.size())
			return NULL;

		double* ptr = &buf[i];
		++i;

		return ptr;
	}
private:
	vector<double> buf;
};

struct List_iterator : Iterat {
	List_iterator() { }
	List_iterator(const list<double> lis)
		: buf{ lis } { }

	double* next()
	{
		static list<double>::pointer ptr;

		if (buf.size() == 0 || ptr == &buf.back()) 
			return NULL;
		else { 
			static list<double>::pointer i = &buf.front();
			ptr = i;
			++i;

			return ptr;
		}
}
private:
	list<double> buf;
};

void print(Iterat& iter)
{
	double* ptr;
	while (ptr = iter.next()) {
		if (ptr == NULL) return;
		cout << *ptr << '\n';
	}
}

int main()
try {
	Vector_iterator vit({ 0, 0, 0, 0 });
	List_iterator lis({1.12, 9999999, 777.897, 1});
	
	print(vit);
	print(lis);

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