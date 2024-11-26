#pragma once

#include <string>
#include <iostream>

/**
* @brief Класс "АВЛ-Дерево"
*/
class Tree
{
private:

public:
	/*
	* @brief Конструктор по умолчанию
	*/
	Tree();

	/*
	* @brief Конструктор копирования
	* @param other дерево, откуда копируем
	*/
	Tree(const Tree& other);

	/*
	* @brief Деструктор
	*/
	~Tree();

	/*
	* @brief Присвоение
	* @param other дерево, откуда копируем
	* @return дерево, куда скопировали
	*/
	Tree& operator=(const Tree& other);

	/*
	* @brief Вставка элемента в дерево
	* @param value значение для вставки
	*/
	void insert(int value);

	/*
	* @brief Поиск элемента в дереве
	* @param value значение для вставки
	* @return информацию о том, найден ли элемент
	*/
	bool find(int value) const;

	/*
	* @brief Приведение дерева к строке
	* @return строковое представление дерева
	*/
	std::string toString() const;

	/*
	* @brief Вывод дерева в поток
	* @param out поток вывода
	* @param tree дерево
	* @return поток вывода для конвейерной работы
	*/
	friend std::ostream& operator<<(std::ostream& out, const Tree& tree);
};

