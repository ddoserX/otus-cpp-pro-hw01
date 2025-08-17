/**
 * @file circle.hpp
 * @headerfile
 * @brief Реализация фигуры Circle.
 */

#pragma once

#include "baseShape.hpp"

/**
 * @brief Класс, представляющий круг
 */
class Circle : public BaseShape
{
    private:
	double m_radius;

    public:
	Circle(double r) : m_radius(r) {}

	void draw() const override { std::cout << "Drawing a Circle\n"; }
};