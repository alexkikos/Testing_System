#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "Console.h"
using namespace std;
namespace testsystem
{
	class Test
	{
		Console console;//консольный класс для перемещения при отображении результатов теста
		string filename;
		string testname;
		string time;
		string date;
		int mark;
		int last_question_int_test;
		string test_end;
		int total_question;
		double total_correct_answers;
	public:

		void SetTIme(string time);
		void SetDate(string date);//системное время и дата
		void SetMark(int mark);//оценка за тест
		void SetLastNumberQuestion(int number);//последний номер теста который был пройден
		void SetFinishedTest(string finish);//завершен тест или нет
		void SetTestname(string name_test);//имя теста
		void SetFilename(string file);//файл с тестом, путь к тесту
		void SetTotalQuestions(int number);//общее количество вопросов в тесте
		void SetCorrectAnswersNumber(double number);//процент верный ответов


		string GetTestname() const;		
		string GetFilename() const;	
		string GetTIme()const;
		string GetDate()const;
		int GetMark()const;
		int GetLastNumberQuestion()const;
		string GetFinishedTest()const;


		void ShowInfoStat(int y, bool rechange_x=false);//отображение статистики пользователя, + использование gotoxy  для нормального вывода информации
		int GetTotalQuestions()const;
		double GetCorrectAnswersNumber()const;

		void ShowQuestions();//начато теста
		float LoadNextQuestion(ifstream& load);//возвращаю номер верного ответа и паршу тест по нужным тегам
		void SaveTest(ofstream& src);
		void LoadTest(ifstream&src);	
		bool operator == (string name);
		friend ostream& operator << (ostream& s, const Test& a);//оператор для сохранения значений
		//Test(string testname = " ", string time = " ", string date = " ", int mark = 0, int last_question_int_test = 0, string test_end = " ");
		explicit Test(string filename, string testname);
		Test() = default;
	};
}
