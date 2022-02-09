#include "Lesson19.h"
#include <sstream>

using namespace MyLib;

template<typename T>
void f(Counted_ptr<T> smart_ptr)
{
	cout << "Argument copy for f(): " << *smart_ptr
		 << "\ncount copy arg: " << smart_ptr.count() << '\n';
	for (int i{ 0 }; i < 4; ++i) {
		Counted_ptr<string> sptr2;
		sptr2 = smart_ptr;
		ostringstream oss;
		oss << ". iteration " << i;
		*sptr2 += oss.str();
		cout << "Counted ptr from cicle: " << *sptr2
			<< "\ncount cicle: " << sptr2.count() << '\n';
	}
}

int main()
{
	Unique_ptr<vector<int>> ptr(new vector<int>());
	(*ptr).push_back(123);
	cout << ptr->size() << '\n';
	Unique_ptr<vector<int>> ptr2 = ptr.release();

	Counted_ptr<string> sptr{new string{"sptr"}};
	cout << "Orig cnt ptr: " << *sptr
		 << "\ncount: " << sptr.count() << '\n';
	Counted_ptr<string> sptr1{sptr};
	cout << "Copied construct: " << *sptr1
		 << "\ncount orig: " << sptr.count() 
		 << "\ncount copy: " << sptr1.count() << '\n';
	f(sptr1);
	Counted_ptr<string> sptr3{new string{"sptr3"}};
	cout << "Sec orig cntptr: " << *sptr3
		 << "\ncount: " << sptr3.count() << '\n';
	f(sptr3);
	cout << "sptr count before: " << sptr.count() << '\n'
		 << "sptr3 count before: " << sptr3.count() << '\n';
	sptr1 = sptr3;
	cout << "sptr count after: " << sptr.count() << '\n'
		 << "sptr3 count after: " << sptr3.count() << '\n';
	vector<Counted_ptr<string>> cptrvec(5, sptr);
	cout << "sptr count after vector: " << cptrvec[0].count() << '\n';

	return 0;
}