#pragma once
#include <iostream>
#include <Windows.h>

using namespace std;
namespace testsystem
{
	class Console
	{
		int x, y;
	public:
		void GotoXy(int x, int y);
		Console(int x, int y);
		Console() = default;
		~Console() = default;
	};

}