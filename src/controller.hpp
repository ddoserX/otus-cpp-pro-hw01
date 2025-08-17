/**
 * @file controller.hpp
 * @headerfile
 * @brief Контроллер - связывающий View и Document (model).
 */

#pragma once

#include "circle.hpp"
#include "document.hpp"
#include "rectangle.hpp"
#include "view.hpp"

/**
 * @brief Класс контроллера
 */
class Controller
{
    private:
	Document& m_document;
	View& m_view;

    public:
	Controller(Document& doc, View& view) : m_document(doc), m_view(view) {}
	/**
	 * @brief Обработчик команды "создать новый документ"
	 */
	void handle_create_new_document() { m_document.create(); }
	/**
	 * @brief Обработчик команды "добавить круг"
	 */
	void handle_add_circle(double radius) { m_document.add_shape(std::make_unique<Circle>(radius)); }
	/**
	 * @brief Обработчик команды "добавить прямоугольник"
	 */
	void handle_add_rectangle(double width, double height)
	{
		m_document.add_shape(std::make_unique<Rectangle>(width, height));
	}
	/**
	 * @brief Обработчик команды "удалить примитив"
	 */
	void handle_remove_shape(size_t index) { m_document.remove_shape(index); }
	/**
	 * @brief Обработчик команды "сохранить"
	 */
	void handle_save(const std::string& filename) { m_document.export_to_file(filename); }
	/**
	 * @brief Обработчик команды "загрузить"
	 */
	void handle_load(const std::string& filename) { m_document.import_from_file(filename); }
	/**
	 * @brief Обработчик команды "отрисовать"
	 */
	void handle_render() { m_view.render(); }
};