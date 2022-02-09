#include "lesson17_lib.h"

using namespace My_link;

int main()
{
	Link* start;
	Link Gods("Zeus");
	start = &Gods;
	Link* poseidon = Gods.add(new Link("Poseidon"));
	Link* ares = Gods.add(new Link("Ares"));
	Gods.add(new Link("Athena"));
	print_all(start);
	start = ares->next();
	print_all(start);

	return 0;
}
