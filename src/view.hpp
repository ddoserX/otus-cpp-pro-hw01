/**
 * @file view.hpp
 * @headerfile
 * @brief Представление (View), отвечающее за отображение данных.
 */

#pragma once

#include "document.hpp"

/**
 * @brief Класс представления (GUI)
 */
class View
{
    private:
	const Document& m_document;

    public:
	View(const Document& doc) : m_document(doc) {}
	/**
	 * @brief Метод для отрисовки всех примитивов в документе
	 */
	void render() const
	{
		std::cout << "=== Rendering document ===\n";

		for (const auto& shape : m_document.get_shapes()) {
			shape->draw();
		}

		std::cout << "=== End of rendering ===\n";
	}
	/**
	 * @brief Имитация отображения меню
	 */
	void show_menu() const
	{
		std::cout << "\n=== Main Menu ===" << std::endl;
		std::cout << "1. Create New Document" << std::endl;
		std::cout << "2. Add Circle" << std::endl;
		std::cout << "3. Add Rectangle" << std::endl;
		std::cout << "4. Remove Shape (by index)" << std::endl;
		std::cout << "5. Save Document" << std::endl;
		std::cout << "6. Load Document" << std::endl;
		std::cout << "7. Render Document" << std::endl;
		std::cout << "8. Exit" << std::endl;
		std::cout << "===================" << std::endl;
	}
};