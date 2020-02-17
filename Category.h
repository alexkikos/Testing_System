#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "Test.h"
#include <iterator>
#include <string>
#include <algorithm>
#include <Windows.h>
#include <time.h>
using namespace std;
namespace testsystem
{
	class Category
	{
		list<Test> tests;//храню массив тестов для данной категории
		string name_category;//храню название категории	
	public:
		//стандартные сет и гет
		void SetNameCategory(string name_category);
		string GetNameCategory() const;
		//название категории
		void ShowCategory() const;
		//показываю названия тестов в категории
		void ShowTestInCategory();
		//начинаю тест, ищу по названию файла, логин нужен для записи результата
		int BeginTest(string name_test, string login);//возвращаю набранные балы за тест
		//меню выбранной категории
		void Menu(string login);
		//показываю результат прохождения теста
		void ShowTestResult();
		//поиск теста по названию
		bool FindTestName(string test_name);
		//добавление теста из под админ панели, без параметров
		void AddTest();
		//добавление теста в нужную категорию
		bool AddTest(string filename, string testname);
		//загрузка категорий и тестов
		void LoadCategory(ifstream& load);
		//перегруженный оператор для поиска по итератору, нужно для добавления тестов в нужную категорию
		bool operator == (string name);
		//констуктор принимающий название категории, где хранится файл и название теста
		explicit Category(string name_categogy, string testfile, string testname);
		//пустой конструктор по умолчанию
		Category();
		explicit Category(string name_category);
		~Category();
	};
}
