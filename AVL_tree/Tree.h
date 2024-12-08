﻿#pragma once

#include <string>
#include <iostream>

/**
* @brief Класс "АВЛ-Дерево"
*/
class Tree
{
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
	* @brief Конструктор перемещения
	* @param other дерево, откуда перемещаем
	*/
	Tree(Tree&& other);

	/*
	* @brief Деструктор
	*/
	~Tree();

	/*
	* @brief Присвоение с копированием
	* @param other дерево, откуда копируем
	* @return дерево, куда скопировали
	*/
	Tree& operator=(const Tree& other);

	/*
	* @brief Присвоение с перемещением
	* @param other дерево, откуда перемещаем
	* @return дерево, куда переместили
	*/
	Tree& operator=(Tree&& other);

	/*
	* @brief Вставка элемента в дерево
	* @param value значение для вставки
	* @return информацию о том, найден ли элемент
	*/
	bool insert(int value);

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

private:
	//Вспомогательная структура "Узел"
	struct Node
	{
		Node(int value);

		int value;
		Node* left;
		Node* right;
	};

private:
	//Указатель на корневой элемент дерева
	Node* root;

private:
	//Рекурсивная функция вставки в поддерево
	static bool insertTo(Node*& subtreeRoot, int newValue);

	//Рекурсивная функция поиска в поддереве
	static bool findIn(const Node* subtreeRoot, int valueToFind);

	//Рекурсивная функция удаления дерева из памяти
	static void destroyTree(const Node* subtreeRoot);
};

