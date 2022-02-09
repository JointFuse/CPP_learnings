#include <iostream>
#include <vector>

using namespace std;

vector<int> gv{ 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 };

void f(vector<int> v)
{
	vector<int> lv(v.size());
	for (int i{0}; i < lv.size() && i < gv.size(); ++i)
		lv[i] = gv[i];

	cout << "lv: ";
	for (int& i : lv)
		cout << i << "; ";
	cout << '\n';

	vector<int> lv2{v};
	cout << "lv2: ";
	for(int& i : lv2)
		cout << i << "; ";
	cout << '\n';
}

int fac(int n) { return n == 0 ? 1 : n * fac(n - 1); }

int main()
{
	f(gv);
	
	vector<int> vv;
	for (int i{1}; i < 11; ++i)
		vv.push_back(fac(i));

	f(vv);

	return 0;
}