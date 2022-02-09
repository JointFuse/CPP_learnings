#include <set>
#include <iostream>
#include <string>

using namespace std;

struct Fruit {
	string name;
	double weight;
	string country;
};

struct Friut_comprassion {
	bool operator() (Fruit* left, Fruit* right) const
	{ return left->name < right->name; }
};

struct Fruit_order {
	bool operator() (const Fruit& left, const Fruit& right) const
	{ return left.country < right.country; }
}; 

ostream& operator<< (ostream& os, const Fruit* f)
{ 
	return os << f->name << ", weight: " << f->weight 
			  << ", from: " << f->country; 
}

ostream& operator<< (ostream& os, const Fruit& f)
{
	return os << f.name << ", weight: " << f.weight
			  << ", from: " << f.country;
}

int main()
{
	set<Fruit*, Friut_comprassion> fruit_set;
	fruit_set.insert(new Fruit{ "apple", 0.235,  "Russia" });
	fruit_set.insert(new Fruit{ "orange", 0.198, "Nicaragua"});
	fruit_set.insert(new Fruit{ "pineapple", 0.941, "Africa"});
	fruit_set.insert(new Fruit{ "grape", 0.356, "Greece"});

	set<Fruit, Fruit_order> inventory;
	for (auto p = fruit_set.begin(); p != fruit_set.end(); ++p)
		{ inventory.insert(**p); }

	cout << "Fruit_set:\n";
	ostream_iterator<Fruit*> oo{cout, "\n"};
	copy(fruit_set.begin(), fruit_set.end(), oo);

	cout << "Inventory:\n";
	copy(inventory.begin(), inventory.end(),
		 ostream_iterator<Fruit>{cout, "\n"});
	
	cout << "Sizeof(fruit_set) = " << sizeof(set<Fruit*>) << '\n'
		 << "Sizeof(inventory) = " << sizeof(set<Fruit>) << '\n'
		 << "Sizeof(Fruit*) = " << sizeof(Fruit*) << '\n'
		 << "Sizeof(Fruit) = " << sizeof(Fruit) << '\n';

	return 0;
}