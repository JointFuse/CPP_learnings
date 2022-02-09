#include "/Users/tony/source/repos/libs/std_lib_facilities.h"

int main()
{
	ifstream ifs("output.txt", ios_base::binary);
	if (!ifs) return 1;
	vector<char> symbs;
	for (char ch; ifs.read(as_bytes(ch), sizeof(char));)
		symbs.push_back(ch);
	ifs.close();
	for (int i{ 0 }; i <= symbs.size() / 2; ++i)
		swap(symbs[i], symbs[symbs.size() - 1 - i]);
	if (symbs.size() % 2 == 0)
		swap(symbs[symbs.size() / 2 - 1], symbs[symbs.size() / 2]);
	ofstream ofs("output.txt", ios_base::app);
	if (!ofs) return 2;
	ofs << '\n';
	for (char ch : symbs)
		ofs << ch;
	return 0;
}