#include <iostream>
#include <vector>

#include "user_allocator.hpp"
#include "user_container.hpp"

int main()
{
	std::cout << "Hello allocator\n";

	UserContainer<int, PoolAllocator<int>> container;

	container.reserve(2);
	container.push_back(1);
	container.push_back(2);
	container.push_back(3);

	std::cout << "front: " << container.front() << " back: " << container.back() << " size: " << container.size()
		  << " capacity: " << container.capacity() << '\n';

	container.clear();

	return 0;
}
