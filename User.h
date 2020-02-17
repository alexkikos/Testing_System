#pragma once
#include <fstream>
#include <iostream>
#include <list>
#include "Category.h"
#include<vector>
#include<map>
#include<algorithm>

using namespace std;
namespace testsystem
{
	class User//����������� �����
	{
	protected:
		string login;
		string password;
		string fio;
		string adress;
		string phone;

	public:
		virtual string GetLogin() const = 0;
		virtual string GetPassword() const = 0;
		virtual string GetFio() const = 0;
		virtual string GetAddress() const = 0;
		virtual string GetPhone() const = 0;
		virtual void SetAdress(string adress)=0;
		virtual void SetLogin(string login) = 0;
		virtual void SetPassword(string password) = 0;
		virtual void SetFio(string fio) = 0;
		virtual void SetPhone(string phone) = 0;
		virtual void PhillInfo() = 0;
		virtual void ShowInfoUser() const = 0;
		virtual ~User() = default;
		User(string login, string password, string fio, string adress, string phone);		
		User() = default;
	};
	   	  

	class AllUser:public User
	{
	protected:
		list<Category> categogys;	
		void LoadCategorysFromDB();//�������� �� ���� ������ ���������� �����, ������ �������� � ���������, ����� ������������ �������� � ����� ������� ��� ���� � ���� ������
	public:
		string GetLogin() const override;//����������� ������ � ������
		string GetPassword() const override;
		string GetFio() const override;
		string GetAddress() const override;
		string GetPhone() const override;
		void SetAdress(string adress) override;
		void SetLogin(string login) override;
		void SetPassword(string password) override;
		void SetFio(string fio) override;
		void SetPhone(string phone) override;

		void PhillInfo() override;//�������� ���������� � �����
		void ShowInfoUser() const override;		//����������� �������� ������, ������ �������� � ��������� �����
		void CategoGyMenu();//��������� �� ����
		int ContinueTest();//����������� �����, ������ ����� ���� � ���������
		void LoadStatisticas();//���������� �������� � ��������� �����
		bool operator == (string s);
		void SaveLogin(ofstream& src);
		void LoadLogin(ifstream& src);
		AllUser(string login,string password=" ", string fio=" ", string adress=" ", string phone=" ");
		~AllUser();
		AllUser() = default;
	};


	//����� ��������� �������� � �������� ������ ��� �������������� ����ca Auth
	class Admin final : private AllUser
	{
		Console console;//��� ������ ���������� � ���� ����
		string db_all_logins;//����� � ��������� ���� ��� ������������������ ������ �������������
		string source_all_users;//���� ��� �������� ����� � ����������
		string file_statistics;	//���� � ����� ���������� �������������
		string path_to_save_statistic_user_seraching;//���� � ������ � ���������� ����������� ���������� �� ���� ������
		string path_to_save_statistic_test_seraching;//���� � ������ � ���������� ����������� ���������� �� ����� �������������
		string path_to_db_all_tests;//����� ��� �������� ��� ���� �����

		void AddNewUser();//�������� �����
		void MenuChangeuserInfo();//���� ��������� ���������� � �����
		void LoadInfoUser();//�������� ���������� � ������������
		void LoadInfoUserName(string login);
		void ChangeuserInfo();//�������������� ���������� ������������
		void ClearStatisticFile();//������� ����� ���������� ������������
		void RemoveResultTestAtNames();//�������� ����������� ������������ �� �������� �����


		void StatisticsMenu();//���� ��� ������ �� �����������
		void ShowResultsAllusers();//������ ���������� ���� �������������
		void ShowResultAtTestName();//����� ���������� �� �������� �����
		void ShowResultSomePerson();//��������� ������������ ������������� ������������
	

		void TestingMenu();//���� ��� ������ � ������� ������, ����������� �������� � ��
		void AddCategoryAndTests(string name_category, string filename_test, string testname);//�������� ��������� �����������
		void ShowTestModulesInDB() const;//������ ������������ ������ ������������ � ����� ������
		void ShowAllUserFromDB() const; //������ ���� ������������� ���� ������


		void Menu();//����� ���� ��� ����� � ����� ������
		void MenuRemoveTestFromDB();//���� �������� ������ �� ����
		void RemoveTestAtname(string test_name);//������ ���� �� ��������
		void RemoveTestsCategorys(string name_categorys);//������� ��� ����� � ��������� ������
		explicit Admin(string login = "admin", string passwaord = "aaaAAA111", string source_all_users = "Users", string file_statistics = "Results", string db_all_logins = "DBAllLogin/db.bin", string path_to_save_statistic_user_seraching = "Statistic/UserStatistics/stat.txt", string path_to_save_statistic_test_seraching = "Statistic/UserStatistics/stat_test_names.txt", string path_to_db_all_tests = "DBTests/db.txt");//�������� ����� ��� �������� ������������
		~Admin()=default;
		friend class Auth;
	};
}
