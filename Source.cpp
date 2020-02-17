#include "Auth.h"
#include <Windows.h>
#include <time.h>
#include <memory>
#ifdef _DEBUG
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#endif
using namespace std;
using namespace  testsystem;


int main()
{
	srand(time(0));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	_CrtMemState _ms;
	_CrtMemCheckpoint(&_ms);

	setlocale(LC_ALL, "");
	{
		Auth g{  };
		g.Menu();//начало программы с модуля авторизации
	}
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtMemDumpAllObjectsSince(&_ms);
	system("pause");
	return 0;
}