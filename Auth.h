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
		string source_all_users;//путь где хранится папка с аккаунтами
		string db_all_logins;//путь к файлу куда сохраняем все логины

		AllUser user;//все пользователи
		UsersWorkSpace userspace;//личный кабинет пользователя
		Admin adminspace;
	public:
		void Rega();//регистрация ака
		void UserLogin();//пользовательый вход
		void Menu();//меню авторизации

		void LoginAdmin();
		void ConnectToAccount();//после авторизации перебрасываю в личный кабинет
		explicit Auth( string source_file="Users", string db_all_logins = "DBAllLogin/db.bin");//констуктор с установкой папки где хранятся аккаунты
	};

}