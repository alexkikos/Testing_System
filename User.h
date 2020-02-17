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
	class User//абстрактный класс
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
		void LoadCategorysFromDB();//загружаю из базы данных актуальные тесты, данные хранятся в категории, далее пользователь работает с этими тестами что есть в базе данных
	public:
		string GetLogin() const override;//стандартные гетеры и сеторы
		string GetPassword() const override;
		string GetFio() const override;
		string GetAddress() const override;
		string GetPhone() const override;
		void SetAdress(string adress) override;
		void SetLogin(string login) override;
		void SetPassword(string password) override;
		void SetFio(string fio) override;
		void SetPhone(string phone) override;

		void PhillInfo() override;//заполняю информацию о юзере
		void ShowInfoUser() const override;		//отображение анкетных данных, данные хранятся в отдельном файле
		void CategoGyMenu();//навигация по меню
		int ContinueTest();//продолжение теста, начало теста идет в категории
		void LoadStatisticas();//статистика хранится в отедльном файле
		bool operator == (string s);
		void SaveLogin(ofstream& src);
		void LoadLogin(ifstream& src);
		AllUser(string login,string password=" ", string fio=" ", string adress=" ", string phone=" ");
		~AllUser();
		AllUser() = default;
	};


	//класс полностью закрытый и доступен только для дружественного класca Auth
	class Admin final : private AllUser
	{
		Console console;//для вывода статистики в норм виде
		string db_all_logins;//храню в отдельной базе все зарегистрированные логины пользователей
		string source_all_users;//путь где хранится папка с аккаунтами
		string file_statistics;	//путь к файлу статистики пользователей
		string path_to_save_statistic_user_seraching;//путь к выводу и сохранению результатов статистики по всем юзерам
		string path_to_save_statistic_test_seraching;//путь к выводу и сохранению результатов статистики по тегам пользователей
		string path_to_db_all_tests;//папка где хранятся все наши тесты

		void AddNewUser();//создание юзера
		void MenuChangeuserInfo();//меню изменение информации о юзере
		void LoadInfoUser();//загружаю информацию о пользователе
		void LoadInfoUserName(string login);
		void ChangeuserInfo();//редактирование информации пользователя
		void ClearStatisticFile();//очистка файла статистики пользователя
		void RemoveResultTestAtNames();//удаление результатов тестирования по названию теста


		void StatisticsMenu();//меню для работы со статистикой
		void ShowResultsAllusers();//вывожу результаты всех польхователей
		void ShowResultAtTestName();//вывод результата по названию теста
		void ShowResultSomePerson();//результат тестирования определенного пользователя
	

		void TestingMenu();//меню для работы с файлами тестов, подключение удаление и тд
		void AddCategoryAndTests(string name_category, string filename_test, string testname);//создание категории тестрований
		void ShowTestModulesInDB() const;//вывожу подключенные модули тестирования в баззе данных
		void ShowAllUserFromDB() const; //вывожу всех пользователей базы данных


		void Menu();//общее меню при входе в админ панель
		void MenuRemoveTestFromDB();//меню удаления файлов из базы
		void RemoveTestAtname(string test_name);//удаляю тест по названию
		void RemoveTestsCategorys(string name_categorys);//удаляем все тесты и категорию тестов
		explicit Admin(string login = "admin", string passwaord = "aaaAAA111", string source_all_users = "Users", string file_statistics = "Results", string db_all_logins = "DBAllLogin/db.bin", string path_to_save_statistic_user_seraching = "Statistic/UserStatistics/stat.txt", string path_to_save_statistic_test_seraching = "Statistic/UserStatistics/stat_test_names.txt", string path_to_db_all_tests = "DBTests/db.txt");//корневая папка где хранятся пользователи
		~Admin()=default;
		friend class Auth;
	};
}
