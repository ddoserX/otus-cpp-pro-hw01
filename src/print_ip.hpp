/**
 * @file print_ip.h
 * @headerfile
 * @brief Реализация шаблонной функции print_ip.
 */

#pragma once

#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

/**
 * @brief Вспомогательный шаблон для SFINAE
 */
template <typename... T>
using void_t = void;

/**
 * @brief Базовый трейт для проверки контейнерных типов
 */
template <typename T, typename = void>
struct is_conteiner : std::false_type {
};


// clang-format off

/**
 * @brief Трейт для определения в переданном типе реализацию контейнера
 */
template <typename T>
struct is_conteiner<T, void_t<
					decltype(std::declval<T>().begin()),
					decltype(std::declval<T>().end()),
					decltype(std::declval<T>().size()),
					decltype(std::declval<T>().empty())
>> : std::true_type {};
// clang-format on

/**
 * @brief Трейт для рекурсивной проверки равенства переданных типов 
 */
template <typename T, typename... Tn>
struct is_all_same {
	static constexpr bool value = (std::is_same<T, Tn>::value && ...);
};

/**
 * @brief Базовый трейт для проверки однородных кортежей
 */
template <typename T>
struct is_homogeneous_tuple : std::false_type {
};

/**
 * @brief Трейт для проверки кортежей на равенство всех типов в нем
 */
template <typename T, typename... Rest>
struct is_homogeneous_tuple<std::tuple<T, Rest...>> : is_all_same<T, Rest...> {
};

/**
 * @brief Специализация шаблонной функции для целочисленных типов и типов с плавающей точкой
 * @fn
 */
template <typename T>
typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value>::type print_ip(T ip)
{
	size_t bytes = sizeof(ip);
	auto it = reinterpret_cast<unsigned char*>(&ip);

	for (size_t i = bytes; i > 0; --i) {
		std::cout << static_cast<int>(it[i - 1]);

		if (i - 1) {
			std::cout << '.';
		}
	}

	std::cout << std::endl;
}

/**
 * @brief Специализация шаблонной функции для контейнеров
 * @fn
 */
template <typename T>
typename std::enable_if<is_conteiner<T>::value>::type print_ip(T ip)
{
	for (auto it = ip.cbegin(), end = ip.cend(); it != end; ++it) {
		std::cout << *it;

		auto next = std::next(it);
		if (next != end) {
			std::cout << '.';
		}
	}
	std::cout << std::endl;
}

/**
 * @brief Специализация шаблонной функции для типа std::string
 * @fn
 */
template <>
void print_ip(std::string ip)
{
	std::cout << ip << std::endl;
}

/**
 * @brief Специализация шаблонной функции для кортежей
 * @fn
 */
template <typename T>
typename std::enable_if<is_homogeneous_tuple<T>::value>::type print_ip(T ip)
{
	std::apply(
	    [](auto&& first, auto&&... rest) {
		    std::cout << first;
		    ((std::cout << '.' << rest), ...);
	    },
	    ip);
	std::cout << std::endl;
}