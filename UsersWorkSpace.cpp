#include "UsersWorkSpace.h"

void testsystem::UsersWorkSpace::UserSpaceMenu(AllUser& user)
{
	system("cls");
	char a = ' ';
	cout << "\n=============================������ �������===============================\n";
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
		cout << "1. ���������� ��������� � ������� ����" << endl;
		cout << "2. ��� ������" << endl;
		cout << "3. �������� ����������" << endl;	
		cout << "4. ���������� ����" << endl;
		cout << "5. ����� � ���� ������" << endl;
		cout << "��� �����: ";
		cin >> a;
	}
	system("cls");
}


