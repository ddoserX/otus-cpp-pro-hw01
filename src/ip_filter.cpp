#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "ipv4.hpp"

std::vector<std::string> split(const std::string& str, char d)
{
	std::vector<std::string> r;

	std::string::size_type start = 0;
	std::string::size_type stop = str.find_first_of(d);
	while (stop != std::string::npos) {
		r.push_back(str.substr(start, stop - start));

		start = stop + 1;
		stop = str.find_first_of(d, start);
	}

	r.push_back(str.substr(start));

	return r;
}

int main()
{
	try {
		std::vector<ipv4_addr> ip_pool;

		for (std::string line; std::getline(std::cin, line);) {
			std::vector<std::string> v = split(line, '\t');
			ip_pool.emplace_back(v.at(0));
		}

		std::sort(ip_pool.begin(), ip_pool.end(), [](const ipv4_addr a, const ipv4_addr b) { return a > b; });

		for (const auto& ip : ip_pool) {
			std::cout << ip << '\n';
		}

		std::for_each(ip_pool.cbegin(), ip_pool.cend(), [](const ipv4_addr& ip) {
			if (ip[0] == 1) {
				std::cout << ip << '\n';
			}
		});

		std::for_each(ip_pool.cbegin(), ip_pool.cend(), [](const ipv4_addr& ip) {
			if (ip[0] == 46 && ip[1] == 70) {
				std::cout << ip << '\n';
			}
		});

		std::for_each(ip_pool.cbegin(), ip_pool.cend(), [](const ipv4_addr& ip) {
			if (ip[0] == 46 || ip[1] == 46 || ip[2] == 46 || ip[3] == 46) {
				std::cout << ip << '\n';
			}
		});
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}

	return 0;
}
