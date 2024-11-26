#include "Tree.h"

//Конструктор с параметром для "Узла"
Tree::Node::Node(int value)
{
	Node::value = value;
	left = nullptr;
	right = nullptr;
}

//Конструктор по умолчанию для "Дерева"
Tree::Tree()
{
	root = nullptr;
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
void Tree::insert(int value)
{

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
