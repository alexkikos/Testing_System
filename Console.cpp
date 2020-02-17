#include "Console.h"


void testsystem::Console::GotoXy(int x, int y)
{
	COORD coordinates;     // coordinates is declared as COORD
	coordinates.X = x;     // defining x-axis
	coordinates.Y = y;     //defining  y-axis
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

testsystem::Console::Console(int x, int y)
{
	this->x = x;
	this->y = y;
}

