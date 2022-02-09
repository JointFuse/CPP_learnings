#include "/Users/tony/source/repos/libs/std_lib_facilities.h"

int main()
try{
	ifstream ifs("input.txt", ios_base::binary);
	ofstream ofs("binary", ios_base::binary);
	ofstream ofs2("output.txt");
	if (!ifs||!ofs)error("");

	vector<char> bytes;
	for (char ch; ifs.read(as_bytes(ch), sizeof(char)); )
		bytes.push_back(ch);
	for (char ch : bytes)
		ofs.write(as_bytes(ch), sizeof(char));
	ofs.close();
	ifstream ifs2("binary", ios_base::binary);
	if (!ifs2) error(" ");
	vector<char> symbols;
	for (char ch; ifs2.read(as_bytes(ch), sizeof(char)); )
		symbols.push_back(ch);
	for (char ch : symbols)
		ofs2 << ch;
	return 0;
}
catch (exception& e) {
	return 1;
}