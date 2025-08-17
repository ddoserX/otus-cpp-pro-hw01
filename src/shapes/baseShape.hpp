/**
 * @file baseShape.hpp
 * @headerfile
 * @brief Реализация чистого базового класса фигуры.
 */

#pragma once

#include <iostream>

/**
 * @brief Абстрактный базовый класс для графических примитивов
 */
class BaseShape
{
    public:
	BaseShape() = default;
	virtual ~BaseShape() = default;

	virtual void draw() const = 0;
};