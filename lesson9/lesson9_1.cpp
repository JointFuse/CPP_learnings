#include "lesson9_1.h"

bool ISBN_check(const string& ISBN)
{
	int dash_num{ 0 };
	string buf{ "" };

	for (int i = 0; i < ISBN.size(); ++i) {
		if (ISBN[i] == '-' && dash_num < 3) {
			if (buf.size() == 0) return false;
			++dash_num;
			buf = "";
			continue;
		}
		buf += ISBN[i];
		if (!isdigit(ISBN[i]) && dash_num < 3) return false;
		if (!isdigit(ISBN[i]) && !isalpha(ISBN[i]) && dash_num == 3) return false;
	}
	if (dash_num != 3) return false;
	return true;
}

bool author_check(string auth)
{
	for (int i = 0; i < auth.size(); ++i)
		if (!isalpha(auth[i])) return false;
	return true;
}

Book::Book(string code, Genre tp, string nm, string auth, Date rd)
	:ISBN{ code }, type{ tp }, name{ nm }, author{ auth },
	reg_date{ rd }, on_hand{ false }
{
	if (!ISBN_check(ISBN)) throw runtime_error("unacceptable ISBN code");
	if (!author_check(author)) throw runtime_error("unacceptable author name");
}

string Book::get_type() const
{
	switch (type) {
	case Genre::fantasy:
		return "fantasy";
		break;
	case Genre::magazine:
		return "magazine";
		break;
	case Genre::prose:
		return "prose";
		break;
	case Genre::biography:
		return "biography";
		break;
	case Genre::childs:
		return "child's";
		break;
	default:
		return "unknow";
	}
}

Patron::Patron(string nm, double crd)
	:name{ nm }, card{ crd }, fee{ MEMBERSHIP_FEE }
{
	if (!author_check(name)) throw runtime_error("unacceptable client name!");
}

void Library::set_fee(string member, double fee)
{
	for (int i = 0; i < members.size(); ++i)
		if (members[i].get_name() == member) { members[i].set_fee(fee); return; }

	cout << "\nNo members found!\n";
}

void Library::set_book(string ISBN)
{
	for(int i=0;i<objects.size();++i)
		if (objects[i].get_code() == ISBN) {
			if (objects[i].in_stock()) objects[i].take();
			else objects[i].put();
			return;
		}

	cout << "\nNo books found!\n";
}

void Library::deal(const Patron& member, const Book& object)
{
	bool is{ true };
	for (Patron i : members) {
		if (i.get_name() == member.get_name()) { 
			if (i.get_fee() != 0) { cout << "\nUnpaid checks, pay first!\n"; return; }
			is = false; 
			break; 
		}
	}

	if (is) { cout << "\nNo members found!\n"; return; }
	is = true;

	for (Book i : objects) {
		if (i == object && i.in_stock()) { is = false; set_book(object.get_code()); break; }
	}

	if (is) { cout << "\nNo books found!\n"; return; }

	Transaction new_trans{ object, member, Date{2000, Month::feb, 13} };
	deals.push_back(new_trans);
}

vector<string> Library::debtors() const
{
	vector<string> feed_back;
	for (Patron i : members)
		if (i.paid())
			feed_back.push_back(i.get_name());

	return feed_back;
}

bool operator== (const Book& left, const Book& right)
{
	if (left.get_code() == right.get_code())
		return true;
	return false;
}

bool operator!= (const Book& left, const Book& right)
{
	return !(left == right);
}

Patron& operator+= (Patron& pat, double fee)
{
	pat.set_fee(pat.get_fee() + fee);
	return pat;
}

ostream& operator<< (ostream& os, const Book& book)
{
	return os << "\nName <" << book.get_name() << ">\n"
			  << "Type <" << book.get_type() << ">\n"
			  << "Author <" << book.get_auth() << ">\n"
			  << "ISBN <" << book.get_code() << ">\n";
}