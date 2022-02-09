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
	sort(nums.begin(), nums.end());
	int dubl{ 1 };
	for (int i{ 0 }; i < nums.size(); ++i) {
		if (i != nums.size() - 1 && nums[i] == nums[i + 1])
			{ ++dubl; continue; }
		ofs << nums[i] << '\t';
		if (dubl != 1) ofs << dubl;
		dubl = 1;
		ofs << '\n';
	}
	return 0;
}