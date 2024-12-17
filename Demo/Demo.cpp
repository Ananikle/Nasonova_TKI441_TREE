#include <iostream>
#include <iomanip>

#include "../AVL_tree/Tree.hpp"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	//Блок, в котором "живёт" дерево
	{
		Tree<int> t;


		std::cout << "Options:" << std::endl;
		std::cout << "i <number> - insert number to the tree" << std::endl;
		std::cout << "f <number> - find number in the tree" << std::endl;
		std::cout << "d <number> - delete number from the tree" << std::endl;
		std::cout << "p - print" << std::endl;
		std::cout << "t - check iterators" << std::endl;
		std::cout << "e - exit" << std::endl;
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

			case 'p':
				std::cout << t << std::endl;
				std::cout << "[" << t.toString() << "]" << std::endl;
				break;

			case 't':
				std::cout << "< ";
				for (Tree<int>::Iterator it = t.begin(); it != t.end(); ++it)
				{
					std::cout << *it << " ";
				}
				std::cout << ">" << std::endl;

				std::cout << "< ";
				Tree<int>::Iterator last = t.end();
				--last;
				for (Tree<int>::Iterator it = last; it != t.end(); --it)
				{
					std::cout << *it << " ";
				}
				std::cout << ">" << std::endl;

				break;
			case 'e':
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
