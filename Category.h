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
		list<Test> tests;//����� ������ ������ ��� ������ ���������
		string name_category;//����� �������� ���������	
	public:
		//����������� ��� � ���
		void SetNameCategory(string name_category);
		string GetNameCategory() const;
		//�������� ���������
		void ShowCategory() const;
		//��������� �������� ������ � ���������
		void ShowTestInCategory();
		//������� ����, ��� �� �������� �����, ����� ����� ��� ������ ����������
		int BeginTest(string name_test, string login);//��������� ��������� ���� �� ����
		//���� ��������� ���������
		void Menu(string login);
		//��������� ��������� ����������� �����
		void ShowTestResult();
		//����� ����� �� ��������
		bool FindTestName(string test_name);
		//���������� ����� �� ��� ����� ������, ��� ����������
		void AddTest();
		//���������� ����� � ������ ���������
		bool AddTest(string filename, string testname);
		//�������� ��������� � ������
		void LoadCategory(ifstream& load);
		//������������� �������� ��� ������ �� ���������, ����� ��� ���������� ������ � ������ ���������
		bool operator == (string name);
		//���������� ����������� �������� ���������, ��� �������� ���� � �������� �����
		explicit Category(string name_categogy, string testfile, string testname);
		//������ ����������� �� ���������
		Category();
		explicit Category(string name_category);
		~Category();
	};
}
