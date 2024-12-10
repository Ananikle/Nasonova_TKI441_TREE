#include "Tree.h"

//Конструктор по умолчанию для "Дерева"
Tree::Tree() : root(nullptr)
{

}

//Конструктор копирования
Tree::Tree(const Tree& other)
{

}

//Конструктор перемещения
Tree::Tree(Tree&& other) noexcept
{

}

//Деструктор
Tree::~Tree()
{
	destroyTree(root);
	root = nullptr;
}

//Оператор присваивания с копированием
Tree& Tree::operator=(const Tree& other)
{
	return *this;
}

//Оператор присваивания с перемещением
Tree& Tree::operator=(Tree&& other) noexcept
{
	return *this;
}

//Вставка элемента в дерево
bool Tree::insert(int value)
{
	return insertTo(root, nullptr, value);
}

//Поиск элемента в дереве
bool Tree::find(int value) const
{
	root->value;
	return findIn(root, value);
}

//Удаление элемента из дерева
bool Tree::remove(int value)
{
	return false;
}

//Получение строкового предстваления дерева
std::string Tree::toString() const
{
	std::string result;
	putToString(root, result);
	result.pop_back();
	return result;
}

//Оператор вывода в поток
std::ostream& operator<<(std::ostream& out, const Tree& tree)
{
	Tree::print(tree.root, out, 0);
	return out;
}



//Конструктор с параметром для "Узла"
Tree::Node::Node(int value, Node* parent)
{
	height = 1;
	Node::value = value;
	Node::parent = parent;
	left = nullptr;
	right = nullptr;
}



//Рекурсивная функция вставки в поддерево
//subtreeRoot - корень поддерева, в которое вставляем новый элемент
bool Tree::insertTo(Node*& subtreeRoot, Node* subtreeParent, int newValue)
{
	//найдено место для вставки
	if (subtreeRoot == nullptr)
	{
		subtreeRoot = new Node(newValue, subtreeParent);
		return true;
	}

	bool isInserted = false;
	if (newValue < subtreeRoot->value)
	{
		isInserted = insertTo(subtreeRoot->left, subtreeRoot, newValue);
	}
	else if (newValue > subtreeRoot->value)
	{
		isInserted = insertTo(subtreeRoot->right, subtreeRoot, newValue);
	}

	unsigned leftHeight = (subtreeRoot->left == nullptr) ? 0 : (subtreeRoot->left->height);
	unsigned rightHeight = (subtreeRoot->right == nullptr) ? 0 : (subtreeRoot->right->height);

	if (leftHeight > rightHeight)
	{
		subtreeRoot->height = leftHeight + 1;
	}
	else
	{
		subtreeRoot->height = rightHeight + 1;
	}

	//newValue == subtreeRoot->value
	return isInserted;
}

//Рекурсивная функция поиска в поддереве
//subtreeRoot - корень поддерева, в котором ищем элемент
bool Tree::findIn(const Node* subtreeRoot, int valueToFind)
{
	//Если нет узла в поддереве
	if (subtreeRoot == nullptr)
	{
		return false;
	}

	if (valueToFind < subtreeRoot->value)
	{
		return findIn(subtreeRoot->left, valueToFind);
	}

	if (valueToFind > subtreeRoot->value)
	{
		return findIn(subtreeRoot->right, valueToFind);
	}

	//valueToFind == subtreeRoot->value
	return true;
}

//Рекурсивная функция печати в поток
void Tree::print(const Node* subtreeRoot, std::ostream& out, unsigned lvl)
{
	if (subtreeRoot == nullptr)
	{
		return;
	}

	print(subtreeRoot->right, out, lvl + 1);

	for (unsigned i = 0; i < lvl; ++i)
	{
		out << "      ";
	}
	out << subtreeRoot->value << "(" << subtreeRoot->height << ")" << std::endl;

	print(subtreeRoot->left, out, lvl + 1);
}

//Рекурсивная функция вывода дерева в строку
void Tree::putToString(const Node* subtreeRoot, std::string& str)
{
	if (subtreeRoot == nullptr)
	{
		return;
	}

	putToString(subtreeRoot->left, str);
	str += std::to_string(subtreeRoot->value);
	str += " ";
	putToString(subtreeRoot->right, str);
}


//Рекурсивная функция удаления дерева из памяти
void Tree::destroyTree(const Node* subtreeRoot)
{
	if (subtreeRoot == nullptr)
	{
		return;
	}

	destroyTree(subtreeRoot->left);
	destroyTree(subtreeRoot->right);
	delete subtreeRoot;
}