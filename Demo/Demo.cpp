#include <iostream>
#include <iomanip>

#include "../AVL_tree/Tree.hpp"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

//Вывод дерева в поток
template <typename Type>
std::ostream& operator<<(std::ostream& out, const Tree<Type>& tree)
{
	out << "TREE = ";

	for (Tree<int>::Iterator it = tree.begin(); it != tree.last(); ++it)
	{
		out << *it << ", ";
	}

	if (tree.last() != tree.end())
	{
		out << *tree.last() << ". ";
	}

	return out;
}

//Ввод дерева из потока
template <typename Type>
std::istream& operator>>(std::istream& in, Tree<Type>& tree)
{
	tree.clear();

	if (&in == &std::cin)
	{
		std::cout << "Enter how many values do you want to place in the tree?" << std::endl;
	}
	int count;
	in >> count;

	if (&in == &std::cin)
	{
		std::cout << "Enter values:" << std::endl;
	}

	for (int i = 0; i < count; ++i)
	{
		Type value;
		in >> value;
		bool isInserted = tree.insert(value);

		if (&in == &std::cin)
		{
			std::cout << (isInserted ? "Added!" : "Failed!") << std::endl;
		}
	}

	return in;
}

int main()
{
	//Блок, в котором "живёт" дерево
	{
		Tree<int> t;


		std::cout << "Options:" << std::endl;
		std::cout << "i <number> - insert number to the tree" << std::endl;
		std::cout << "f <number> - find number in the tree" << std::endl;
		std::cout << "d <number> - delete number from the tree" << std::endl;
		std::cout << "r - read" << std::endl;
		std::cout << "t - tree-print" << std::endl;
		std::cout << "p - print" << std::endl;
		std::cout << "e - check iterators" << std::endl;
		std::cout << "x - exit" << std::endl;
		std::cout << std::endl;

		char choice;
		std::cout << "Input:" << std::endl;
		do
		{
			std::cin >> choice;

			int number;
			switch (choice)
			{
			case 'i':
				std::cin >> number;
				std::cout << std::setw(6) << std::left << "Insert";
				std::cout << std::setw(4) << std::right << number;
				std::cout << std::left << ": " << (t.insert(number) ? "SUCCEED" : "FAILED") << std::endl;
				break;

			case 'f':
				std::cin >> number;
				std::cout << std::setw(6) << std::left << "Find";
				std::cout << std::setw(4) << std::right << number;
				std::cout << std::left << ": " << (t.find(number) ? "FOUND" : "NOT FOUND") << std::endl;
				break;

			case 'd':
				std::cin >> number;
				std::cout << std::setw(6) << std::left << "Delete";
				std::cout << std::setw(4) << std::right << number;
				std::cout << std::left << ": " << (t.remove(number) ? "SUCCEED" : "FAILED") << std::endl;
				break;

			case 'r':
				std::cin >> t;
				break;

			case 't':
				t.printAsTree(std::cout);
				std::cout << "[" << t.toString() << "]" << std::endl;
				break;

			case 'p':
				std::cout << t << std::endl;
				break;

			case 'e':
				for (Tree<int>::Iterator it = t.begin(); it != t.end(); ++it)
				{
					std::cout << *it << " > ";
				}
				std::cout << "END" << std::endl;

				for (Tree<int>::Iterator it = t.last(); it != t.end(); --it)
				{
					std::cout << *it << " > "; 
				}
				std::cout << "END" << std::endl;
				break;

			case 'x':
				break;

			default:
				std::cout << "INVALID INPUT!\a" << std::endl;
			}

		} while (choice != 'e');


	}
	//дерево перестало "жить"

	//Функция проверки утечки памяти (результат смотреть в MS VS в "Вывод", рядом со "Список ошибок")
	_CrtDumpMemoryLeaks();

	return 0;
}
