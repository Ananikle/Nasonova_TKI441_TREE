#include <iostream>
#include <iomanip>

#include "../AVL_tree/Tree.cpp"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	//Блок, в котором "живёт" дерево
	{
		Tree t;

		t.insert(5);
		t.insert(8);
		t.insert(15);
		t.insert(1);
		t.insert(-5);
		t.insert(13);

		std::cout << "|";
		for (int i = -10; i <= 20; ++i)
		{
			std::cout << std::setw(4) << i << "|";
		}
		std::cout << std::endl;

		std::cout << "|";
		for (int i = -10; i <= 20; ++i)
		{
			std::cout << std::setw(4) << (t.find(i) ? "yes" : "-") << "|";
		}
		std::cout << std::endl;

		std::cout << t << std::endl;
	}
	//дерево перестало "жить"
	
	//Функция проверки утечки памяти (результат смотреть в MS VS в "Вывод", рядом со "Список ошибок")
	_CrtDumpMemoryLeaks();

	return 0;
}
