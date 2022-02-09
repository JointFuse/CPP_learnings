#include "lesson17_lib.h"

using namespace My_link;
void sort_gods(Link* orig, Link*& greece, Link*& norway, Link*& india);

int main()
{
	Link Gods({"Zeus", Mithology::greece, "", "lightning"});
	Gods.add(new Link({"Odin", Mithology::norway, "flying horse", "spear Gungnir"}));
	Gods.add(new Link({"Alvis", Mithology::norway, "", "nature"}));
	Gods.add(new Link({"Brahma", Mithology::india, "", "create universe"}));
	Gods.add(new Link({"Poseidon", Mithology::greece, "", "trident"}));
	Gods.add(new Link({"Vishnu", Mithology::india, "", "protect universe"}));
	Gods.add(new Link({"Heinmhdal", Mithology::norway, "", "seen future"}));
	Gods.add(new Link({"Bragi", Mithology::norway, "", "wisdom"}));
	Gods.add(new Link({"Ares", Mithology::greece, "cart", "sword"}));
	Gods.add(new Link({"Shiva", Mithology::india, "", "destroy universe"}));
	Gods.add(new Link({"Yama", Mithology::india, "", "death and justice"}));
	Gods.add(new Link({"Athena", Mithology::greece, "", "spear"}));
	print_all(&Gods);

	Link* Greece_gods{ nullptr };
	Link* Norway_gods{ nullptr };
	Link* India_gods{ nullptr };

	sort_gods(&Gods, Greece_gods, Norway_gods, India_gods);

	print_all(Greece_gods);
	print_all(Norway_gods);
	print_all(India_gods);

	return 0;
}

void sort_gods(Link* orig, Link*& greece, Link*& norway, Link*& india)
{
	while (orig->previous()) 
		orig = orig->previous();

	Link* god = orig;
	while (god) {
		orig = god;
		god = god->next();
		orig->erase();
		switch (orig->value.from) {
		case Mithology::greece:
			greece = greece->add_ordered(orig);
			break;
		case Mithology::norway:
			norway = norway->add_ordered(orig);
			break;
		case Mithology::india:
			india = india->add_ordered(orig);
			break;
		default:
			break;
		}
	}
}