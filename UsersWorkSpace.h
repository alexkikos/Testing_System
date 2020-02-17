#pragma once
#include "User.h"
#include <list>
#include <iterator>
#include <string.h>
#include <algorithm>
using namespace std;
namespace testsystem
{
	//Личный кабинет пользователя
	class UsersWorkSpace
	{	
		
	public:
		void UserSpaceMenu(AllUser&user);//личный кабинет пользователя, с статистикой, прохождением тестов и тд
		UsersWorkSpace()=default;
	};
}
