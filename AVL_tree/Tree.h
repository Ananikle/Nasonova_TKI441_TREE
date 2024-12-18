#pragma once

#include <string>
#include <iostream>
#include <stdexcept>


/**
* @brief Шаблонный класс "АВЛ-Дерево"
*/
template<typename T>
class Tree
{
public:
	struct Node;
	class Iterator;

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
	* @brief Очистка дерева
	*/
	void clear();

	/*
	* @brief Проверка дерева на пустоту
	* @return информацию о том, пусто ли дерево
	*/
	bool isEmpty() const;

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
	* @brief Печать структуры дерева
	* @param out поток вывода
	* @param tree дерево
	*/
	void printAsTree(std::ostream& out) const;

	/*
	* @brief Получение итератора на первый элемент
	* @return итератор на begin-элемент
	*/
	Iterator begin() const;

	/*
	* @brief Получение итератора на последний элемент
	* @return итератор на last-элемент
	*/
	Iterator last() const;

	/*
	* @brief Получение итератора на элемент, следующий за последним
	* @return итератор на end-элемент
	*/
	Iterator end() const;

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

	//Рекурсивная функция поиска минимального (наиболее левого) узла
	static Node*& getMinIn(Node*& subtreeRoot);

	//Рекурсивная функция печати в поток
	static void print(const Node* subtreeRoot, std::ostream& out, int lvl);

	//Рекурсивная функция вывода дерева в строку
	static void putToString(const Node* subtreeRoot, std::string& str);

	//Рекурсивная функция копирования дерева
	static void copyTree(Node*& subtreeRootTo, Node* subtreeParent, const Node* subtreeRootFrom);

	//Рекурсивная функция удаления дерева из памяти
	static void destroyTree(const Node* subtreeRoot);

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

		//Получение самого левого потомка
		const Node* getTheMostLeft() const;

		//Получение самого правого потомка
		const Node* getTheMostRight() const;

		int height;
		T value;
		Node* parent;
		Node* left;
		Node* right;
	};

	//Вспомогательный класс "Итератор"
	class Iterator
	{
		friend class Tree;
	public:
		/*
		* @brief Конструктор по умолчанию для пустого итератора
		*/
		Iterator();
	private:
		//Конструктор с параметрами для создания итератора на данный узел
		Iterator(const Node* ptr);

	public:
		/*
		* @brief Проверка итераторов на равенство
		* @return результат проверки: true / false
		*/
		bool operator==(const Iterator& other) const;

		/*
		* @brief Проверка итераторов на неравенство
		* @return результат проверки: true / false
		*/
		bool operator!=(const Iterator& other) const;

		/*
		* @brief Сдвиг итератора вперёд
		* @return ссылка на сдвинутый вперёд итератор
		*/
		Iterator& operator++();

		/*
		* @brief Сдвиг итератора вперёд
		* @param int фиктивное значение
		* @return итератор на предыдущую позицию
		*/
		Iterator operator++(int);

		/*
		* @brief Сдвиг итератора назад
		* @return ссылка на сдвинутый вперёд итератор
		*/
		Iterator& operator--();

		/*
		* @brief Сдвиг итератора назад
		* @param int фиктивное значение
		* @return итератор на предыдущую позицию
		*/
		Iterator operator--(int);

		/*
		* @brief Разыменование
		* @return значение, на которое указывает итератор
		*/
		const T& operator*() const;

	private:
		//Указатель на текущий узел
		const Node* element;
	};
};

