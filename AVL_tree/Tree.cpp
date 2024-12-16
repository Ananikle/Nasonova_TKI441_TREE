#include "Tree.h"

//Конструктор по умолчанию для "Дерева"
Tree::Tree() : root(nullptr)
{

}

//Конструктор копирования
Tree::Tree(const Tree& other)
{
	copyTree(this->root, nullptr, other.root);
}

//Конструктор перемещения
Tree::Tree(Tree&& other) noexcept
{
	this->root = other.root;
	other.root = nullptr;
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
	//проверяем не одинаковые ли адреса у this и other
	if (this != &other)
	{
		destroyTree(this->root);
		copyTree(this->root, nullptr, other.root);
	}

	return *this;
}

//Оператор присваивания с перемещением
Tree& Tree::operator=(Tree&& other) noexcept
{
	//проверяем не одинаковые ли адреса у this и other
	if (this != &other)
	{
		destroyTree(this->root);
		this->root = other.root;
		other.root = nullptr;
	}

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
	return deleteIn(root, value);
}

//Получение строкового представления дерева
std::string Tree::toString() const
{
	std::string result;
	putToString(root, result);
	if (!result.empty())
	{
		result.pop_back();
	}
	return result;
}

//Оператор вывода в поток
std::ostream& operator<<(std::ostream& out, const Tree& tree)
{
	Tree::print(tree.root, out, 0);
	return out;
}



//Конструктор с параметрами для "Узла"
Tree::Node::Node(int value, Node* parent)
{
	height = 1;
	Node::value = value;
	Node::parent = parent;
	left = nullptr;
	right = nullptr;
}

//Пересчитывает высоту на узле
void Tree::Node::updateHeight()
{
	//находимся в узле (this - это ЭТОТ узел):

	unsigned leftHeight = (this->left == nullptr) ? 0 : (this->left->height);
	unsigned rightHeight = (this->right == nullptr) ? 0 : (this->right->height);

	if (leftHeight > rightHeight)
	{
		this->height = leftHeight + 1;
	}
	else
	{
		this->height = rightHeight + 1;
	}
}



//Левый поворот
void Tree::leftRotate(Node* a)
{
	Node* b = a->right;

	//Узел a забирает правого ребёнка у b
	a->right = b->left;
	if (a->left != nullptr)
	{
		a->left->parent = a;
	}

	//Узел b забирает родителя a
	b->parent = a->parent;
	if (b->parent == nullptr)
	{
		root = b;
	}
	else
	{
		(a->parent->right == a ? b->parent->right: b->parent->left) = b;
	}

	//Узел a становится левым ребёнком b
	b->left = a;
	a->parent = b;

	//Пересчёт высот для a и b
	a->updateHeight();
	b->updateHeight();
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

	subtreeRoot->updateHeight();

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

//Рекурсивная функция удаления элемента в поддереве
//subtreeRoot - корень поддерева, в котором ищем элемент
bool Tree::deleteIn(Node*& subtreeRoot, int valueToDelete)
{
	//Если нет узла в поддереве
	if (subtreeRoot == nullptr)
	{
		return false;
	}

	if (valueToDelete == subtreeRoot->value)
	{
		deleteNode(subtreeRoot);
		return true;
	}

	bool isDeleted = false;
	if (valueToDelete < subtreeRoot->value)
	{
		isDeleted = deleteIn(subtreeRoot->left, valueToDelete);
	}
	else if (valueToDelete > subtreeRoot->value)
	{
		isDeleted = deleteIn(subtreeRoot->right, valueToDelete);
	}

	if (isDeleted)
	{
		subtreeRoot->updateHeight();
	}

	return isDeleted;
}

//Функция удаления узла из дерева
//linkToNode - ссылка(!) на удаляемый узел дерева
void Tree::deleteNode(Node*& linkToNode)
{
	Node* parent = linkToNode->parent;
	Node* nodeToDelete = linkToNode;

	if (linkToNode->left == nullptr && linkToNode->right == nullptr)
	{
		//удаление узла без детей
		delete nodeToDelete;
		linkToNode = nullptr;
		return;
	}

	if (linkToNode->left != nullptr && linkToNode->right != nullptr)
	{
		//удаление узла с двумя детьми
		//ищем наименьший элемент в правом дереве
		Node*& min = getMinIn(linkToNode->right);
		std::swap(min->value, linkToNode->value);
		deleteNode(min);

		return;
	}

	//удаление узла с одним ребёнком
	linkToNode = (linkToNode->left != nullptr) ? linkToNode->left : linkToNode->right;
	linkToNode->parent = parent;
	delete nodeToDelete;
}

//Рекурсивная функция поиска минимумального (наиболее левого) узла
Tree::Node*& Tree::getMinIn(Node*& subtreeRoot)
{
	if (subtreeRoot->left == nullptr)
	{
		return subtreeRoot;
	}

	return getMinIn(subtreeRoot->left);
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

//Рекурсивная функция копирования дерева
void Tree::copyTree(Node*& subtreeRootTo, Node* subtreeParent, const Node* subtreeRootFrom)
{
	//если нет узла для создания клона
	if (subtreeRootFrom == nullptr)
	{
		subtreeRootTo = nullptr;
		return;
	}

	subtreeRootTo = new Node(subtreeRootFrom->value, subtreeParent);
	subtreeRootTo->height = subtreeRootFrom->height;
	copyTree(subtreeRootTo->left, subtreeRootTo, subtreeRootFrom->left);
	copyTree(subtreeRootTo->right, subtreeRootTo, subtreeRootFrom->right);
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