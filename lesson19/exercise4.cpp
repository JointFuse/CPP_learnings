#include "lesson17_lib.h"

using namespace My_link;
void sort_gods(Link<God>* orig, Link<God>*& greece, Link<God>*& norway, Link<God>*& india);
void test_f(const Link<God>&);

int main()
{
	Link<God> Gods({ "Zeus", Mithology::greece, "", "lightning" });
	Gods.add(new Link<God>({ "Odin", Mithology::norway, "flying horse", "spear Gungnir" }));
	Gods.add(new Link<God>({ "Alvis", Mithology::norway, "", "nature" }));
	Gods.add(new Link<God>({ "Brahma", Mithology::india, "", "create universe" }));
	Gods.add(new Link<God>({ "Poseidon", Mithology::greece, "", "trident" }));
	Gods.add(new Link<God>({ "Vishnu", Mithology::india, "", "protect universe" }));
	Gods.add(new Link<God>({ "Heinmhdal", Mithology::norway, "", "seen future" }));
	Gods.add(new Link<God>({ "Bragi", Mithology::norway, "", "wisdom" }));
	Gods.add(new Link<God>({ "Ares", Mithology::greece, "cart", "sword" }));
	Gods.add(new Link<God>({ "Shiva", Mithology::india, "", "destroy universe" }));
	Gods.add(new Link<God>({ "Yama", Mithology::india, "", "death and justice" }));
	Gods.add(new Link<God>({ "Athena", Mithology::greece, "", "spear" }));
	print_all(&Gods);

	Link<God>* Greece_gods{ nullptr };
	Link<God>* Norway_gods{ nullptr };
	Link<God>* India_gods{ nullptr };

	sort_gods(&Gods, Greece_gods, Norway_gods, India_gods);

	print_all(Greece_gods);
	print_all(Norway_gods);
	print_all(India_gods);
	test_f(*Greece_gods);

	return 0;
}

void sort_gods(Link<God>* orig, Link<God>*& greece, Link<God>*& norway, Link<God>*& india)
{
	while (orig->previous())
		orig = orig->previous();

	Link<God>* god = orig;
	while (god) {
		orig = god;
		god = god->next();
		orig->erase();
		switch (orig->val.from) {
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

void test_f(const Link<God>& gg)
{
	God zeus("Zeus", Mithology::greece, "", "lightning");
	const Link<God>* fnd = gg.find(zeus);
	if (fnd)
		std::cout << fnd->val;
}