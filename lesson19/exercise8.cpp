#include "Lesson19.h"

using namespace MyLib;

int main()
{
	Allocator<int> aloc;
	int* ptr = aloc.allocate(10);
	int* p1 = &ptr[1];
	int* p2 = &ptr[9];
	for (int i{0}; i < 10; ++i)
		{ aloc.construct(ptr + i, i); }
	for (int i{0}; i < 10; ++i)
		{ cout << ptr[i] << '\n'; }
	for (int i{0}; i < 10; ++i)
		{ aloc.destroy(ptr + i); }
	aloc.deallocate(ptr, 10);

	vector<double> vdb;
	vec_check(vdb, "Construct vdb{}");
	vdb.reserve(4);
	vec_check(vdb, "Reserve 4 members vdb");
	vdb.resize(2);
	vec_check(vdb, "Resize 2 members vdb");
	vdb.resize(10);
	vec_check(vdb, "Resize 10 members vdb");
	vdb.push_back(1.25);
	vec_check(vdb, "Push back 1.25 vdb");
	vdb.resize(7);
	vec_check(vdb, "Resize 7 members vdb");
	vector<double> vdb2{3};
	vec_check(vdb2, "Construct vdb2{int 3}");
	for (int i{0}; i < vdb.size(); ++i)
		{ vdb[i] = i * 0.3 + 0.7; }
	vec_check(vdb, "Cicle fill vdb[i]");
	vector<double> vdb1(vdb);
	vec_check(vdb1, "Construct vdb1{const Vector& vdb}");
	vdb2 = vdb2;
	vec_check(vdb2, "Self copy paste vdb2");
	vdb = vdb2;
	vec_check(vdb, "Lowcast copy paste vdb = vdb2");
	vdb2 = vdb1;
	vec_check(vdb2, "Upcast copy paste vdb2 = vdb1");
	vector<char>* vcp = new vector<char>(10);
	char* ptr1 = &(*vcp)[0];
	vec_check(*vcp, "Vector pointer");
	delete vcp;
	cout << "deleted check = " << *ptr1 << '\n';
	cout << "sizeof(int*) = " << sizeof(int*) << '\n'
		 << "sizeof(vector<int>) = " << sizeof(vector<int>) << '\n';
	try {
		vdb2.at(100);
	}
	catch (exception& e) {
		cout << "Exception: " << e.what() << endl;
		return 1;
	}

	return 0;
}