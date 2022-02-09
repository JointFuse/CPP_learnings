#include "/Users/tony/source/repos/libs/std_lib_facilities.h"

void word_from_file(const string& file, const string& word);
void del_vowel(const string& file);
bool is_vowel(char ch);

int main()
try{
	del_vowel("input.txt");
	return 0;
}
catch (exception& e) {
	cout << "Exception: " << e.what() << endl;
	return 1;
}

void word_from_file(const string& file, const string& word)
{
	ifstream ifs(file);
	if (!ifs) error("Unable to open file: ", file);

	int i{ 1 };
	while (ifs.good()) {
		string buf;
		getline(ifs, buf);
		stringstream str{ buf };
		for (string w; str >> w; )
			if (w == word)
				cout << '¹' << i << ": "
					<< buf << '\n';
		++i;
	}
}

void del_vowel(const string& file)
{
	ifstream ifs(file);
	if (!ifs) error("Can't open file to read: ", file);

	stringstream fbuf;
	for (string buf; getline(ifs, buf); fbuf << buf << '\n') { }
	ifs.close();
	ofstream ofs(file);
	if (!ofs) error("Can't open file to write: ", file);

	for (string buf; getline(fbuf, buf); ) {
		stringstream line{ buf };
		while (line >> buf) {
			for (int i{ 0 }; i < buf.size(); ++i)
				if (is_vowel(buf[i])) {
					buf.erase(i, 1);
					--i;
				}
			ofs << buf << ' ';
		}
		ofs << '\n';
	}
}

bool is_vowel(char ch)
{
	ch = tolower(ch);

	switch (ch) {
	case 'a': case 'e':
	case 'y': case 'u': 
	case 'i': case 'o':
		return true;
	default:
		return false;
	}
}