#include "/Users/tony/source/repos/libs/std_lib_facilities.h"+

string& clear_string(string& str);
string& clear_word(string& word);
bool whitespace(char* ch);

int main()
{
	ifstream ifs("input.txt");
	ofstream ofs("dictinary.txt");
	if (!ifs) error("Can't open file: input.txt");
	if (!ofs) error("Can't open file: dictinary.txt");

	vector<string> dictinary;
	for (string buf; ifs >> buf; cout << buf << '\n') {
		cout << buf << '\t';
		dictinary.push_back(clear_word(buf));
	}

	sort(dictinary.begin(), dictinary.end());
	
	int n{ 1 };
	for (int i{ 0 }; i < dictinary.size(); ++i) {
		if (i + 1 != dictinary.size() 
			&& dictinary[i] == dictinary[i + 1])
		{ ++n; continue; }
		ofs << setw(40) << dictinary[i] << " - repeat " << n << " times\n";
		n = 1;
	}
	return 0;
}

string& clear_string(string& str)
{
	stringstream old{ str };
	str = "";
	for (string buf; old >> buf; str += ' ')
		str += clear_word(buf);
	return str;
}

string& clear_word(string& word)
{
	for (int i{ 0 }; i < word.size(); ++i)
		if (i == 0 || i == word.size() - 1
			|| word[i - 1] != '"' || word[i + 1] != '"') {
			if (whitespace(&word[i]))
				word.push_back('t');
		}
	return word;
}

bool whitespace(char* ch)
{
	switch (*ch) {
	case '-':
		if (!isalpha(*(ch - 1)) || !isalpha(*(ch + 1)))
			*ch = ' ';
		return false;
	case '\'':
		if (*(ch - 1) == 'n' && *(ch + 1) == 't') {
			if (*(ch - 3) != 'c')
				*(ch - 1) = ' ';
			*ch = 'n';
			*(ch + 1) = 'o';
			return true;
		}
	case '.': case ',': 
	case ';': case '?':
	case '(': case ')':
		*ch = ' ';
		return false;
	default:
		*ch = tolower(*ch);
		return false;
	}
}