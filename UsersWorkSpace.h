#pragma once
#include "User.h"
#include <list>
#include <iterator>
#include <string.h>
#include <algorithm>
using namespace std;
namespace testsystem
{
	//������ ������� ������������
	class UsersWorkSpace
	{	
		
	public:
		void UserSpaceMenu(AllUser&user);//������ ������� ������������, � �����������, ������������ ������ � ��
		UsersWorkSpace()=default;
	};
}
