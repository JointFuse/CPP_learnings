#include "/Users/tony/source/repos/libs/std_lib_facilities.h"

int main()
{
	ifstream ifs("nums.txt");
	ofstream ofs("output.txt");
	if (!ifs) return 1;
	if (!ofs) return 2;
	vector<double> nums;
	for (double buf; ifs >> buf; )
		nums.push_back(buf);
	ofs << '|' << scientific << setprecision(8);
	for (int i{ 0 }; i < nums.size(); ++i) {
		ofs << setw(14) << nums[i] << '|';
		if (i != 0 && (i + 1) % 4 == 0)
			ofs << "\n|";
	}
	return 0;
}