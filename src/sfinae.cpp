#include <iostream>
#include <list>
#include <tuple>
#include <vector>
#include <type_traits>

template <typename T, typename = void>
struct is_iterable : std::false_type {
};

template <typename T>
struct is_iterable<T, std::void_t<decltype(std::declval<T>().begin())>> : std::true_type {
};

template <typename T, typename = void>
void print_ip(T data)
{
	std::cout << data << std::endl;
}

template <typename T, typename std::enable_if<is_iterable<T>::value>::type>
void print_ip(T data)
{
	for (const auto& el : data) {
		std::cout << el << '.';
	}

	std::cout << std::endl;
}

int main()
{
	// std::vector<int> vec = {1,2,3,4};
	// std::list<int> lis {};
	// std::array<int,3> arr = {1,2,3};

	// std::cout << is_iterable<std::string>::value << std::endl;

	std::string str = "abcdifj";
	int x = -1;
	std::vector<int> vec = {1, 2, 3, 4};

	print_ip(x);
	print_ip(str);
	print_ip(vec);

	return 0;
}
