#pragma once
#include <list>
#include <iterator>
#include <string.h>
#include <fstream>
#include <iostream>
#include "User.h"
#include "UsersWorkSpace.h"

using namespace std;
namespace testsystem
{
	class Auth
	{
		string source_all_users;//���� ��� �������� ����� � ����������
		string db_all_logins;//���� � ����� ���� ��������� ��� ������

		AllUser user;//��� ������������
		UsersWorkSpace userspace;//������ ������� ������������
		Admin adminspace;
	public:
		void Rega();//����������� ���
		void UserLogin();//�������������� ����
		void Menu();//���� �����������

		void LoginAdmin();
		void ConnectToAccount();//����� ����������� ������������ � ������ �������
		explicit Auth( string source_file="Users", string db_all_logins = "DBAllLogin/db.bin");//���������� � ���������� ����� ��� �������� ��������
	};

}