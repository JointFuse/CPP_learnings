#include "std_lib_facilities.h"
#include "lesson9.h"

#define MEMBERSHIP_FEE	12

using namespace Chrono;

enum class Genre {
	fantasy, prose, magazine,
	biography, childs
};

class Book {
private:
	
	string ISBN, name, author;
	Date reg_date;
	Genre type;
	bool on_hand;

public:

	Book(string ISBN, Genre type, string name, string author, Date reg_date);

	string get_code()	const	{ return ISBN; }
	string get_name()	const	{ return name; }
	string get_auth()	const	{ return author; }
	Date get_date()		const	{ return reg_date; }
	bool in_stock()		const	{ return !on_hand; }

	string get_type()	const;

	void take() { on_hand = true; }
	void put()	{ on_hand = false; }
};

class Patron {
private:

	string name;
	double card;
	double fee;

public:

	Patron(string name, double card);

	string get_name()	const { return name; }
	double get_card()	const { return card; }
	double get_fee()	const { return fee; }
	bool  paid()		const { return bool(fee); }

	void  set_fee(double new_fee) { fee = new_fee; }
};

class Library {
private:
	struct Transaction {
		Transaction(Book b, Patron p, Date d)
			:object{ b }, member{ p }, date{ d } {}

		Book object;
		Patron member;
		Date date;
	};

	vector<Patron> members;
	vector<Book> objects;
	vector<Transaction> deals;

public:

	void new_member(Patron add)	{ members.push_back(add); }
	void new_book(Book add)		{ objects.push_back(add); }
	
	void set_fee(string member, double fee);
	void set_book(string ISBN);

	void deal(const Patron&, const Book&);
	vector<string> debtors() const;
};

bool ISBN_check(const string&);

bool operator== (const Book&, const Book&);
bool operator!= (const Book&, const Book&);

Patron& operator+= (Patron&, double);

ostream& operator<< (ostream&, const Book&);