#include <iostream>
#include <iomanip>

#include "../AVL_tree/Tree.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	//Блок, в котором "живёт" дерево
	{
		Tree t;


		std::cout << "Options:" << std::endl;
		std::cout << "i - insert" << std::endl;
		std::cout << "f - find" << std::endl;
		std::cout << "d - delete" << std::endl;
		std::cout << "e - exit" << std::endl;
		std::cout << std::endl;
		char choice;

		do
		{
			std::cout << "TREE:" << std::endl;
			std::cout << t << std::endl;
			std::cout << "[" << t.toString() << "]" << std::endl;

			std::cout << "Choose your next move: ";
			std::cin >> choice;

			int number;
			switch (choice)
			{
			case 'i':
				std::cout << "Enter number:" << std::endl;
				std::cin >> number;
				std::cout << "Insert: " << (t.insert(number) ? "SUCCEED" : "FAILED") << std::endl;
				break;
			case 'f':
				std::cout << "Enter number:" << std::endl;
				std::cin >> number;
				std::cout << "Find: " << (t.find(number) ? "FOUND" : "NOT FOUND") << std::endl;

				break;
			case 'd':
				std::cout << "Enter number:" << std::endl;
				std::cin >> number;
				std::cout << "Delete: " << (t.remove(number) ? "SUCCEED" : "FAILED") << std::endl;
				break;

			case 'e':

				break;
			default:
				std::cout << "INVALID INPUT!\a" << std::endl;
			}

			std::cout << std::endl;
			for (int i = 0; i < 20; ++i)
			{
				std::cout << "-";
			}
			std::cout << std::endl;

		} while (choice != 'e');


	}
	//дерево перестало "жить"
	
	//Функция проверки утечки памяти (результат смотреть в MS VS в "Вывод", рядом со "Список ошибок")
	_CrtDumpMemoryLeaks();

	return 0;
}
