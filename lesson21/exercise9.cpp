#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <exception>
#include "Order.h"

int main()
try{
	const std::string file1{ "orders1.txt" };
	const std::string file2{ "orders2.txt" };

	std::vector<Order_lib::Order> vord;
	std::list<Order_lib::Order> lord;

	Order_lib::sort_and_safe(vord, file1);
	Order_lib::sort_and_safe(lord, file2);

	std::ofstream conkat("order_summ.txt");
	std::vector<Order_lib::Order> vord2;
	copy(lord.begin(), lord.end(), back_inserter(vord2));
	merge(vord.begin(), vord.end(), vord2.begin(), vord2.end(), 
		  std::ostream_iterator<Order_lib::Order>(conkat),
		  [](const Order_lib::Order& left, const Order_lib::Order& right)
		  { return left.get_name() < right.get_name(); });
		  
	return 0;
}
catch (std::exception& e) {
	std::cout << "Exception: " << e.what() << std::endl;
	return 1;
}
catch (std::runtime_error& r) {
	std::cout << "Runtime error: " << r.what() << std::endl;
	return 2;
}
catch (...) {
	std::cout << "Error" << std::endl;
	return 3;
}