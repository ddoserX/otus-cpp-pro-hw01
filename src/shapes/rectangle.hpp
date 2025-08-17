/**
 * @file rectangle.hpp
 * @headerfile
 * @brief Реализация фигуры Rectangle.
 */

#pragma once

#include "baseShape.hpp"

/**
 * @brief Класс, представляющий прямоугольник
 */
class Rectangle : public BaseShape
{
    private:
	double m_width;
	double m_height;

    public:
	Rectangle(double w, double h) : m_width(w), m_height(h) {}

	void draw() const override { std::cout << "Drawing a Rectangle\n"; }
};