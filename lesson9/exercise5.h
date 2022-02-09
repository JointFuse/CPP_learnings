#include "exercise0.h"

class Book {
public:

	string ISBN_get()	const { return ISBN; }
	string name_get()	const { return name; }
	string author_get()	const { return author; }
	bool in_stock()		const { return on_hands; }

	string date_get()	const;

private:
	
	string ISBN;				// identification code
	string name;				// book name
	string author;				// author first name
	
	Version3::Date reg_date;	// author rights registration data
	
	bool on_hands;				// is book issued in hand or not
};