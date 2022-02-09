#include <vector>
#include <iostream>
#include <fstream>
#include <numeric>
#include <algorithm>

using namespace std;

int main()
{
	ifstream ff{"task_vecdat.txt"};

	vector<double> vd{istream_iterator<double>{ff},
					  istream_iterator<double>{}};

	ostream_iterator<double> oo{cout, "\n"};
	copy(vd.begin(), vd.end(), oo);

	vector<double> vi(vd.size());
	copy(vd.begin(), vd.end(), vi.begin());

	for (int i{0}; i < vi.size(); ++i)
		{ cout << vd[i] << " = " << vi[i] << '\n'; }

	cout << "vd summ = " << accumulate(vd.begin(), vd.end(), 0.0) << '\n'
		 << "vd summ - vi summ = " << accumulate(vd.begin(), vd.end(), 0.0) 
									  - accumulate(vi.begin(), vi.end(), 0.0) << '\n';

	reverse(vd.begin(), vd.end());
	copy(vd.begin(), vd.end(), ostream_iterator<double>{cout, "\n"});

	double avarage = accumulate(vd.begin(), vd.end(), 0.0) / vd.size();
	cout << "vd average = " << avarage << '\n';

	vector<double> vd2(count_if(vd.begin(), vd.end(), [&](double v) 
													  { return v < avarage; }));
	copy_if(vd.begin(), vd.end(), vd2.begin(), [&](double x)
											   { return x < avarage; });
	
	sort(vd2.begin(), vd2.end());
	copy(vd2.begin(), vd2.end(), ostream_iterator<double>{cout, "\n"});

	return 0;
}