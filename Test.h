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
		Console console;//���������� ����� ��� ����������� ��� ����������� ����������� �����
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
		void SetDate(string date);//��������� ����� � ����
		void SetMark(int mark);//������ �� ����
		void SetLastNumberQuestion(int number);//��������� ����� ����� ������� ��� �������
		void SetFinishedTest(string finish);//�������� ���� ��� ���
		void SetTestname(string name_test);//��� �����
		void SetFilename(string file);//���� � ������, ���� � �����
		void SetTotalQuestions(int number);//����� ���������� �������� � �����
		void SetCorrectAnswersNumber(double number);//������� ������ �������


		string GetTestname() const;		
		string GetFilename() const;	
		string GetTIme()const;
		string GetDate()const;
		int GetMark()const;
		int GetLastNumberQuestion()const;
		string GetFinishedTest()const;


		void ShowInfoStat(int y, bool rechange_x=false);//����������� ���������� ������������, + ������������� gotoxy  ��� ����������� ������ ����������
		int GetTotalQuestions()const;
		double GetCorrectAnswersNumber()const;

		void ShowQuestions();//������ �����
		float LoadNextQuestion(ifstream& load);//��������� ����� ������� ������ � ����� ���� �� ������ �����
		void SaveTest(ofstream& src);
		void LoadTest(ifstream&src);	
		bool operator == (string name);
		friend ostream& operator << (ostream& s, const Test& a);//�������� ��� ���������� ��������
		//Test(string testname = " ", string time = " ", string date = " ", int mark = 0, int last_question_int_test = 0, string test_end = " ");
		explicit Test(string filename, string testname);
		Test() = default;
	};
}
