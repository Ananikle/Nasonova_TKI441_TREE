#include "Tree.h"

//Конструктор по умолчанию для "Дерева"
Tree::Tree() : root(nullptr)
{
	
}

//Конструктор копирования
Tree::Tree(const Tree& other)
{

}

//Деструктор
Tree::~Tree()
{

}

//Оператор присваивания
Tree& Tree::operator=(const Tree& other)
{
	return *this;
}

//Вставка элемента в дерево
bool Tree::insert(int value)
{
	return insertTo(root, value);
}

//Поиск элемента в дереве
bool Tree::find(int value) const
{
	return false;
}

//Получение строкового предстваления дерева
std::string Tree::toString() const
{
	return "";
}

//Оператор вывода в поток
std::ostream& operator<<(std::ostream& out, const Tree& tree)
{
	return out;
}



//Конструктор с параметром для "Узла"
Tree::Node::Node(int value)
{
	Node::value = value;
	left = nullptr;
	right = nullptr;
}



//Рекурсивная функция вставки в поддерево
//subtreeRoot - корень поддерева, в которое вставляем новый элемент
bool Tree::insertTo(Node*& subtreeRoot, int newValue)
{
	//найдено место для вставки
	if (subtreeRoot == nullptr)
	{
		subtreeRoot = new Node(newValue);
		return true;
	}

	if (newValue < subtreeRoot->value)
	{
		return insertTo(subtreeRoot->left, newValue);
	}

	if (newValue > subtreeRoot->value)
	{
		return insertTo(subtreeRoot->right, newValue);
	}

	//newValue == subtreeRoot->value
	return false;
}