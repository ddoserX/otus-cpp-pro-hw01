/**
 * @file document.hpp
 * @headerfile
 * @brief Model, хранящая коллекцию примитивов.
 */

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "baseShape.hpp"

/**
 * @brief Класс, представляющий документ (Модель)
 */
class Document
{
    private:
	std::vector<std::unique_ptr<BaseShape>> m_shapes = {};

    public:
	Document() = default;

	Document(const Document&) = delete;
	Document& operator=(const Document&) = delete;

	/**
	 * @brief Создание нового документа (просто очищаем текущий)
	 */
	void create()
	{
		m_shapes.clear();
		std::cout << "New document created.\n";
	}
	/**
	 * @brief Импорт документа из файла
	 */
	void import_from_file(const std::string& filename)
	{
		std::cout << "Importing document from " << filename << std::endl;
	}
	/**
	 * @brief Экспорт документа в файл
	 */
	void export_to_file(const std::string& filename) const
	{
		std::cout << "Exporting document to " << filename << std::endl;
	}
	/**
	 * @brief Добавление графического примитива
	 */
	void add_shape(std::unique_ptr<BaseShape> shape)
	{
		m_shapes.emplace_back(std::move(shape));
		std::cout << "Shape added to document\n";
	}
	/**
	 * @brief Удаление графического примитива по индексу
	 */
	bool remove_shape(size_t index)
	{
		if (index < m_shapes.size()) {
			std::cout << "Shape at index " << index << " removed\n";
			return true;
		}

		std::cout << "Invalid index for shape remove " << index << std::endl;
		return false;
	}
	/**
	 * @brief Получение доступа к примитивам (для View)
	 */
	const std::vector<std::unique_ptr<BaseShape>>& get_shapes() const { return m_shapes; }
};