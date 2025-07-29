/**
 * @file main.cpp 
 * @brief Точка входа в программу.
 */

#include <iostream>
#include <vector>
#include <list>
#include <tuple>

#include "print_ip.hpp"

int main()
{
	print_ip(-1);
	print_ip(0);
	print_ip(0.0);
	print_ip(2130706433);
	print_ip(8875824491850138409);
	print_ip(std::vector<int>{192,168,0,1});
	print_ip(std::list<short>{192,168,0,2});
	print_ip(std::string("Hello world!"));
	print_ip(std::make_tuple(172,16,0,1));

	return 0;
}
