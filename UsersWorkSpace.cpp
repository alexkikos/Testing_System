#include "UsersWorkSpace.h"

void testsystem::UsersWorkSpace::UserSpaceMenu(AllUser& user)
{
	system("cls");
	char a = ' ';
	cout << "\n=============================ЛИЧНЫЙ КАБИНЕТ===============================\n";
	cout << endl;
	while (a != '5')
	{
		switch (a)
		{
		case '1': user.CategoGyMenu(); break;
		case '2': user.ShowInfoUser(); break;
		case '3': user.LoadStatisticas(); break;
		case '4': user.ContinueTest(); break;
		default:
			break;
		}
		cout << "1. Посмотреть категории и выбрать тест" << endl;
		cout << "2. Моя анкета" << endl;
		cout << "3. Показать статистику" << endl;	
		cout << "4. Продолжить тест" << endl;
		cout << "5. Выйти в меню логина" << endl;
		cout << "Мой выбор: ";
		cin >> a;
	}
	system("cls");
}


