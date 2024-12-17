﻿#pragma once

#include <string>
#include <iostream>

/**
* @brief Шаблонный класс "АВЛ-Дерево"
*/
template<typename T>
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
	Tree(Tree&& other) noexcept;

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
	Tree& operator=(Tree&& other) noexcept;

	/*
	* @brief Вставка элемента в дерево
	* @param value значение для вставки
	* @return информацию о том, найден ли элемент
	*/
	bool insert(T value);

	/*
	* @brief Поиск элемента в дереве
	* @param value значение для вставки
	* @return информацию о том, найден ли элемент
	*/
	bool find(T value) const;

	/*
	* @brief Удаление элемента из дерева
	* @param value значение для удаления
	* @return информацию о том, удален ли элемент
	*/
	bool remove(T value);

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
		//Конструктор с параметрами для "Узла"
		Node(T value, Node* parent);

		//Пересчитывает высоту на узле
		void updateHeight();

		//Рассчёт фактора балансировки
		int getBalanceFactor() const;

		int height;
		T value;
		Node* parent;
		Node* left;
		Node* right;
	};

private:
	//Указатель на корневой элемент дерева
	Node* root;

private:
	//Функции для AVL-балансировки

	//Левый поворот
	void leftRotate(Node* a);

	//Правый поворот
	void rightRotate(Node* a);

	//Правый-левый поворот
	void rightLeftRotate(Node* a);

	//Левый-правый поворот
	void leftRightRotate(Node* a);

	//Балансировка поддерева
	void balanceSubtree(Node* subtreeRoot);

private:
	//Рекурсивная функция вставки в поддерево
	bool insertTo(Node*& subtreeRoot, Node* subtreeParent, T newValue);

	//Рекурсивная функция поиска в поддереве
	static bool findIn(const Node* subtreeRoot, T valueToFind);

	//Рекурсивная функция удаления элемента в поддереве
	bool deleteIn(Node*& subtreeRoot, T valueToDelete);

	//Функция удаления узла из дерева
	static void deleteNode(Tree::Node*& nodeToDelete);

	//Рекурсивная функция поиска минимумального (наиболее левого) узла
	static Node*& getMinIn(Node*& subtreeRoot);

	//Рекурсивная функция печати в поток
	static void print(const Node* subtreeRoot, std::ostream& out, int lvl);

	//Рекурсивная функция вывода дерева в строку
	static void putToString(const Node* subtreeRoot, std::string& str);

	//Рекурсивная функция копирования дерева
	static void copyTree(Node*& subtreeRootTo, Node* subtreeParent, const Node* subtreeRootFrom);

	//Рекурсивная функция удаления дерева из памяти
	static void destroyTree(const Node* subtreeRoot);
};

