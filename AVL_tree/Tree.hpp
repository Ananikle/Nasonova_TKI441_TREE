#include "Tree.h"

//Конструктор по умолчанию для "Дерева"
template<typename T>
Tree<T>::Tree() : root(nullptr)
{

}

//Конструктор копирования
template<typename T>
Tree<T>::Tree(const Tree& other)
{
	copyTree(this->root, nullptr, other.root);
}

//Конструктор перемещения
template<typename T>
Tree<T>::Tree(Tree&& other) noexcept
{
	this->root = other.root;
	other.root = nullptr;
}

//Деструктор
template<typename T>
Tree<T>::~Tree()
{
	destroyTree(root);
	root = nullptr;
}

//Оператор присваивания с копированием
template<typename T>
Tree<T>& Tree<T>::operator=(const Tree<T>& other)
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
template<typename T>
Tree<T>& Tree<T>::operator=(Tree<T>&& other) noexcept
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
template<typename T>
bool Tree<T>::insert(T value)
{
	return insertTo(root, nullptr, value);
}

//Поиск элемента в дереве
template<typename T>
bool Tree<T>::find(T value) const
{
	root->value;
	return findIn(root, value);
}

//Удаление элемента из дерева
template<typename T>
bool Tree<T>::remove(T value)
{
	return deleteIn(root, value);
}

//Получение строкового представления дерева
template<typename T>
std::string Tree<T>::toString() const
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
template<typename T>
std::ostream& operator<<(std::ostream& out, const Tree<T>& tree)
{
	Tree<T>::print(tree.root, out, 0);
	return out;
}



//Конструктор с параметрами для "Узла"
template<typename T>
Tree<T>::Node::Node(T value, Node* parent)
{
	height = 1;
	Node::value = value;
	Node::parent = parent;
	left = nullptr;
	right = nullptr;
}

//Пересчитывает высоту на узле
template<typename T>
void Tree<T>::Node::updateHeight()
{
	//находимся в узле (this - это ЭТОТ узел):

	int leftHeight = (this->left == nullptr) ? 0 : (this->left->height);
	int rightHeight = (this->right == nullptr) ? 0 : (this->right->height);

	if (leftHeight > rightHeight)
	{
		this->height = leftHeight + 1;
	}
	else
	{
		this->height = rightHeight + 1;
	}
}

//Рассчёт фактора балансировки
template<typename T>
int Tree<T>::Node::getBalanceFactor() const
{
	int leftHeight = (this->left == nullptr) ? 0 : (this->left->height);
	int rightHeight = (this->right == nullptr) ? 0 : (this->right->height);

	return (leftHeight - rightHeight);
}



//Левый поворот
template<typename T>
void Tree<T>::leftRotate(Node* a)
{
	Node* b = a->right;

	//Узел a забирает левого ребёнка у b
	a->right = b->left;
	if (a->right!= nullptr)
	{
		a->right->parent = a;
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

//Правый поворот
template<typename T>
void Tree<T>::rightRotate(Node* a)
{
	Node* b = a->left;

	//Узел а забирает правого ребенка у b
	a->left = b->right;
	if (a->left != nullptr)
	{
		a->left->parent = a;
	}

	//Узел b забирает родителя а
	b->parent = a->parent;
	if (b->parent == nullptr)
	{
		root = b;
	}
	else
	{
		(a->parent->left == a ? b->parent->left : b->parent->right) = b;
	}

	//узел а становится правым ребенком
	b->right = a;
	a->parent = b;

	//Пересчет высот 
	a->updateHeight();
	b->updateHeight();
}

//Правый-левый поворот
template<typename T>
void Tree<T>::rightLeftRotate(Node* a)
{
	rightRotate(a->right);
	leftRotate(a);
}

//Левый-правый поворот
template<typename T>
void Tree<T>::leftRightRotate(Node* a)
{
	leftRotate(a->left);
	rightRotate(a);
}

//Балансировка поддерева
template<typename T>
void Tree<T>::balanceSubtree(Node* subtreeRoot)
{
	int balanceFactor = subtreeRoot->getBalanceFactor();

	if (balanceFactor == -2)
	{
		if (subtreeRoot->right->left == nullptr)
		{
			leftRotate(subtreeRoot);
		}
		else
		{
			rightLeftRotate(subtreeRoot);
		}
	}
	else if (balanceFactor == +2)
	{
		if (subtreeRoot->left->right == nullptr)
		{
			rightRotate(subtreeRoot);
		}
		else
		{
			leftRightRotate(subtreeRoot);
		}
	}
}

//Рекурсивная функция вставки в поддерево
//subtreeRoot - корень поддерева, в которое вставляем новый элемент
template<typename T>
bool Tree<T>::insertTo(Node*& subtreeRoot, Node* subtreeParent, T newValue)
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

	if (isInserted)
	{
		subtreeRoot->updateHeight();
		balanceSubtree(subtreeRoot);
	}

	//newValue == subtreeRoot->value
	return isInserted;
}

//Рекурсивная функция поиска в поддереве
//subtreeRoot - корень поддерева, в котором ищем элемент
template<typename T>
bool Tree<T>::findIn(const Node* subtreeRoot, T valueToFind)
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
template<typename T>
bool Tree<T>::deleteIn(Node*& subtreeRoot, T valueToDelete)
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
		balanceSubtree(subtreeRoot);
	}

	return isDeleted;
}

//Функция удаления узла из дерева
//linkToNode - ссылка(!) на удаляемый узел дерева
template<typename T>
void Tree<T>::deleteNode(Node*& linkToNode)
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
template<typename T>
Tree<T>::Node*& Tree<T>::getMinIn(Node*& subtreeRoot)
{
	if (subtreeRoot->left == nullptr)
	{
		return subtreeRoot;
	}

	return getMinIn(subtreeRoot->left);
}

//Рекурсивная функция печати в поток
template<typename T>
void Tree<T>::print(const Node* subtreeRoot, std::ostream& out, int lvl)
{
	if (subtreeRoot == nullptr)
	{
		return;
	}

	print(subtreeRoot->right, out, lvl + 1);

	for (int i = 0; i < lvl; ++i)
	{
		out << "      ";
	}
	out << subtreeRoot->value << "(" << subtreeRoot->height << ")" << std::endl;

	print(subtreeRoot->left, out, lvl + 1);
}

//Рекурсивная функция вывода дерева в строку
template<typename T>
void Tree<T>::putToString(const Node* subtreeRoot, std::string& str)
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
template<typename T>
void Tree<T>::copyTree(Node*& subtreeRootTo, Node* subtreeParent, const Node* subtreeRootFrom)
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
template<typename T>
void Tree<T>::destroyTree(const Node* subtreeRoot)
{
	if (subtreeRoot == nullptr)
	{
		return;
	}

	destroyTree(subtreeRoot->left);
	destroyTree(subtreeRoot->right);
	delete subtreeRoot;
}