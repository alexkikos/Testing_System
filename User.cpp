#include "User.h"

string testsystem::AllUser::GetLogin() const
{
	return login;
}

string testsystem::AllUser::GetPassword() const
{
	return password;
}

string testsystem::AllUser::GetFio() const
{
	return fio;
}

string testsystem::AllUser::GetAddress() const
{
	return adress;
}

string testsystem::AllUser::GetPhone() const
{
	return phone;
}

void testsystem::AllUser::SetAdress(string adress)
{
	if (adress.length() > 0)
		this->adress = adress;
	else
		cout << "\nПроверьте корректность ввода!" << endl;
}

void testsystem::AllUser::SetLogin(string login)
{
	if (login.length() > 0)
		this->login = login;
	else
		cout << "\nПроверьте корректность ввода!" << endl;
}

void testsystem::AllUser::SetPassword(string password)
{
	if (password.length() > 0)
		this->password = password;
	else
		cout << "\nПроверьте корректность ввода!" << endl;
}

void testsystem::AllUser::SetFio(string fio)
{
	if (fio.length() > 0)
		this->fio = fio;
	else
		cout << "\nПроверьте корректность ввода!" << endl;
}

void testsystem::AllUser::SetPhone(string phone)
{
	if (phone.length() > 0)
		this->phone = phone;
	else
		cout << "\nПроверьте корректность ввода!" << endl;
}

void testsystem::AllUser::PhillInfo()
{

	cin.ignore();
	cin.clear();
agh:
	cout << "\nВведите пароль(x - возврат обратно): ";
	cin >> password;
	if (password == "x") return;
	int totolint = 0, tottalstr = 0, totalupper = 0;
	for (int i = 0; i < password.length(); i++)
	{
		if (isalpha(password[i]))
		{
			tottalstr++;
			if (isupper(password[i])) totalupper++;
		}
		else
			if (isdigit(password[i])) totolint++;

	}
	if (totolint < 3 or tottalstr < 6 or totalupper < 3)
	{
		cout << "\nНеобходимо ввести 3 обычных символа, 3 цифры, 3 заглавных символа";
		goto agh;
	}
	cin.ignore();
	cin.clear();
	cout << "\nВведите фамилию/имя/отчество: ";
	getline(cin, fio);
	cout << "\nВведите домашний адрес: ";
	getline(cin, adress);
	cout << "\nВведите контактный телефон: ";
	getline(cin, phone);
}

void testsystem::AllUser::ShowInfoUser() const
{
	system("cls");
	cout << "                  ИНФОРМАЦИЯ О ПОЛЬЗОВАТЕЛЕ" << endl;
	cout << "Логин: " << login << endl;
	cout << "ФИО: " << fio << endl;
	cout << "Адрес: " << adress << endl;
	cout << "Телефон: " << phone << endl;

}





int testsystem::AllUser::ContinueTest()
{
	system("cls");
	bool check = false;
	list<Test> my;
	ifstream load("Results/" + login + ".bin", ios::binary);
	int y = 4;
	if (load.is_open())
	{
		while (!load.eof())
		{
			if (load.peek() == EOF) break;
			Test b;
			b.LoadTest(load);
			my.push_back(b);
		}
		load.close();
		list<Test>::iterator t = my.begin();
		cout << "День сдачи           Время            Название теста             Оценка            Количество вопросов      Завершен       Всего правильных ответов       Правильных ответов(%)" << endl;
		while (t != my.end())
		{
			(*t).ShowInfoStat(y);
			t++;
			y++;
		}
	}
	else cout << "\nДанные отсутствуют" << endl;
	cout << "\n========================================================================\n";	
	cout << "\nВведите название теста: ";
	cin.ignore();
	cin.clear();
	string s;
	getline(cin, s);
	my.clear();
	load.open("Results/" + login + ".bin", ios::binary);
	if (load.is_open())
	{
		while (!load.eof())
		{
			if (load.peek() == EOF) break;
			Test b;
			b.LoadTest(load);
			if (b.GetFinishedTest() == "Нет" and _strcmpi((b).GetTestname().c_str(), s.c_str()) == 0) { check = true; };
			my.push_back(b);
		}
		load.close();
		if (check)
		{
			list<Test>::iterator t = my.begin();
			bool finish = true;
			bool end_current_and_exit = true;
			while (t != my.end())
			{
				if ((*t).GetFinishedTest() == "Нет" and _strcmpi((*t).GetTestname().c_str(), s.c_str()) == 0 and end_current_and_exit)
				{
					int last_question = ((*t)).GetLastNumberQuestion();//получил номер вопроса на котором остановился
					int count = 0;
					int user_mark_for_test;
					if (last_question != 0)
					{
						user_mark_for_test = (*t).GetTotalQuestions();
					}
					else  user_mark_for_test = 0;
					int count_of_questions = ((*t)).GetLastNumberQuestion();
					ifstream load((*t).GetFilename());
					if (load.is_open()) //листая файл до нужного вопроса
					{

						while (!load.eof())
						{
							if (count == last_question)
							{
								system("cls");

								cout << "\n==============================" << count_of_questions + 1 << "==============================\n";
								float g = (*t).LoadNextQuestion(load);//загружаю и паршу с файла вопросы тестирования

								if (g == -1)//обработка возвращаемого результата
								{
									break;//словили пустую строку == конец файла
								}
								else
									if (g == -2) //pause
									{
										finish = false;
										(*t).SetFinishedTest("Нет");//возврат паузы во время сдачи теста
										break;
									}
									else
									{
										user_mark_for_test += g;
									}
								count_of_questions++;
							}
							else
							{
								s = "";
								getline(load, s);
								if (s.length() == 0) return -1;//если пустая строка или конец файла == завершили тест
								if (s[0] == '>') 	count++;//подсчет количество вопросов	
							}
						}
						load.close();
						if (user_mark_for_test + ((*t).GetMark()) == 0 and finish)//отметка что тест сдан плохо
						{
							(*t).SetMark(1);
							(*t).SetCorrectAnswersNumber(0);
							end_current_and_exit = false;
						}
						else
						{
							int k2 = (12 / count_of_questions) * user_mark_for_test;
							(*t).SetMark(k2);// набранные балы
							double k1 = ((((12.f / count_of_questions) * user_mark_for_test) / 12.f) * 100);//вычисляю % верных ответов
							(*t).SetCorrectAnswersNumber(k1);
							(*t).SetTotalQuestions(user_mark_for_test);//записываю верные ответы в тесте
							if (finish) 	(*t).SetFinishedTest("Да");//
							(*t).SetLastNumberQuestion(count_of_questions);	//сохраняю номер последнего вопроса для восстановления прохождения по тесту
							end_current_and_exit = false;
						}
					}

				}
				if (!finish) break;
				t++;
			}
			t = my.begin();
			ofstream save;
			save.open("Results/" + login + ".bin", ios::binary);//перезаписываб весь файл с новыми значениями тестов + старые подтягиваю
			save.clear();
			while (t != my.end())
			{
				(*t).SaveTest(save);
				t++;

			}
			save.close();
		}
	}
	if (!check) 			cout << "\nДанный тест не найден!" << endl;

	my.clear();
}




void testsystem::AllUser::SaveLogin(ofstream& s)
{
	int n;
	n = login.length() + 1;
	s.write((char*)& n, sizeof(int));
	s.write(login.c_str(), n);

	n = password.length() + 1;
	s.write((char*)& n, sizeof(int));
	s.write(password.c_str(), n);

	n = fio.length() + 1;
	s.write((char*)& n, sizeof(int));
	s.write(fio.c_str(), n);

	n = adress.length() + 1;
	s.write((char*)& n, sizeof(int));
	s.write(adress.c_str(), n);

	n = phone.length() + 1;
	s.write((char*)& n, sizeof(int));
	s.write(phone.c_str(), n);

}

void testsystem::AllUser::LoadLogin(ifstream& s)
{

	int n;
	char b[200];
	s.read((char*)& n, sizeof(int));
	s.read(b, n);
	login = b;

	s.read((char*)& n, sizeof(int));
	s.read(b, n);
	password = b;

	s.read((char*)& n, sizeof(int));
	s.read(b, n);
	fio = b;

	s.read((char*)& n, sizeof(int));
	s.read(b, n);
	adress = b;

	s.read((char*)& n, sizeof(int));
	s.read(b, n);
	phone = b;
}



void testsystem::AllUser::LoadStatisticas()
{
	system("cls");
	cout << "\n                          СТАТИСТИКА ПОЛЬЗОВАТЕЛЯ" << endl;
	cout << "========================================================================\n";
	list<Test> my;
	ifstream load("Results/" + login + ".bin", ios::binary);
	int y = 4;
	if (load.is_open())
	{
		while (!load.eof())
		{
			if (load.peek() == EOF) break;
			Test b;
			b.LoadTest(load);
			my.push_back(b);
		}
		load.close();
		list<Test>::iterator t = my.begin();
		cout << "День сдачи           Время            Название теста             Оценка            Количество вопросов      Завершен       Всего правильных ответов       Правильных ответов(%)" << endl;
		while (t != my.end())
		{
			(*t).ShowInfoStat(y);
			t++;
			y++;
		}
	}
	else cout << "\nДанные отсутствуют" << endl;
	cout << "\n========================================================================\n";
	my.clear();

}

void testsystem::AllUser::CategoGyMenu()
{
res:

	system("cls");
	cout << "                    ДОСТУПНЫЕ КАТЕГОРИИ ТЕСТИРОВАНИЯ" << endl;
	cout << "========================================================================\n";
	list<Category>::iterator s = categogys.begin();
	int count = 1;
	while (s != categogys.end())
	{
		cout << count++ << ". ";
		(*s).ShowCategory();
		s++;
	}
	cout << "========================================================================\n";
	int number;
	cout << "\n Выберите номер категории(0-назад): ";
	cin >> number;
	if (number == 0) { system("cls"); return; };
	if (number > categogys.size() or number < 0)
	{
		goto res;
	}
	else
	{
		s = categogys.begin();
		int k = 1;
		while (k != number)
		{
			k++;
			s++;
		}
		(*s).Menu(this->login);
	}
}

void testsystem::AllUser::LoadCategorysFromDB()
{
	ifstream load("DBTests/db.txt");//при старте программы загружаю в память все доступные категории тестирования
	if (load.is_open())
	{
		string s, s1, s2;
		int count = 0;
		while (!load.eof())
		{
			load >> s >> s1 >> s2;
			if (s.length() == 0 and count > 0)
			{
				load.close();
				return; //если конец файла
			}
			if (count == 0)
			{
				Category a{ s };
				a.AddTest(s1, s2);
				categogys.push_back(a);
				count++;
			}
			else
			{
				count++;
				list<Category>::iterator i = categogys.begin();
				i = find_if(categogys.begin(), categogys.end(), [&](const Category& a) {return (_strcmpi(s.c_str(), a.GetNameCategory().c_str()) == 0); });//ищу название категории, если  такой нету создаю, если есть добавляю в нее тест
				if (i != categogys.end())
				{
					(*i).AddTest(s1, s2);
				}
				else
				{
					Category a{ s };
					a.AddTest(s1, s2);
					categogys.push_back(a);

				}
			}
		}

	}
	load.close();
}

bool testsystem::AllUser::operator==(string s)
{
	if (login == s) return true;
	else return false;
}

testsystem::AllUser::AllUser(string login, string password, string fio, string adress, string phone) :User(login, password, fio, adress, phone)
{
	LoadCategorysFromDB();
}



testsystem::AllUser::~AllUser()
{
	categogys.clear();
}



testsystem::User::User(string login, string password, string fio, string adress, string phone)
{
	this->login = login;
	this->password = password;
	this->fio = fio;
	this->adress = adress;
	this->phone = phone;
}


testsystem::Admin::Admin(string login, string passwaord, string source_all_users, string file_statistics, string db_all_logins, string path_to_save_statistic_user_seraching, string path_to_save_statistic_test_seraching, string path_to_db_all_tests) : AllUser(login, passwaord)
{

	this->source_all_users = source_all_users;
	this->file_statistics = file_statistics;
	this->db_all_logins = db_all_logins;
	this->path_to_save_statistic_user_seraching = path_to_save_statistic_user_seraching;
	this->path_to_save_statistic_test_seraching = path_to_save_statistic_test_seraching;
	this->path_to_db_all_tests = path_to_db_all_tests;
}

void testsystem::Admin::Menu()
{
	system("cls");
	char a = ' ';
	cout << endl;
	while (a != '5')
	{
		cout << "1. Добавить пользователя" << endl;//++
		cout << "2. Изменить информацию о пользователе" << endl;//++
		cout << "3. Просмотр статистики" << endl;//++
		cout << "4. Управление тестированием" << endl;//++
		cout << "5. Выйти в меню обратно" << endl;
		cout << "Мой выбор: ";
		cin >> a;
		switch (a)
		{
		case '1': system("cls"); AddNewUser(); break;
		case '2': 	system("cls"); MenuChangeuserInfo(); break;
		case '3': system("cls"); StatisticsMenu(); break;
		case '4': system("cls"); TestingMenu(); break;
		default:
			break;
		}
	}
	system("cls");
}

void testsystem::Admin::MenuRemoveTestFromDB()
{
	system("cls");
	char a = ' ';
	cout << endl;
	string b;
	ShowTestModulesInDB();
	cout << endl;
	while (a != '3')
	{
		cout << "1. Удалить тест из базы" << endl;//++
		cout << "2. Удалить рубрику категорий" << endl;//++
		cout << "3. Возврат" << endl;
		cout << "Мой выбор: ";
		cin >> a;
		switch (a)
		{
		case '1':		
			cin.ignore();
			cin.clear();
			cout << "\nВведите название теста(x - назад): ";
			cin >> b;
			if (b == "x") return;
			RemoveTestAtname(b);
			break;
		case '2':
			system("cls");
			cin.ignore();
			cin.clear();
			ShowTestModulesInDB();
			cout << endl;
			cout << "\nВведите название категории(x - назад): ";
			cin >> b;
			if (b == "x") return;
			RemoveTestsCategorys(b);
		default:
			break;
		}
	}
	system("cls");
}

void testsystem::Admin::RemoveTestAtname(string test_name)
{
	vector<string> my;
	ifstream load(path_to_db_all_tests);
	if (load.is_open())
	{
		while (!load.eof())
		{
			string s, s1, s2;
			load >> s >> s1 >> s2;
			if (s.length() == 0)
			{
				load.close();//файл пустой выходим
				break;
			}
			if (_strcmpi(s2.c_str(), test_name.c_str()) == 0)//если совпадение
			{
				continue;
			}
			else
			{
				string g = s + " " + s1 + " " + s2; //в иных случаях заносим все другие строки в массив и пересохраняем файл
				my.push_back(g);
			}
		}
		load.close();
	}
	else
		cout << "\nCant open file ";

	ofstream save(path_to_db_all_tests);
	save.clear();
	sort(my.begin(), my.end(), [&](string s, string s1) { return (s[0] < s1[0]); });//сортирую лямбдой по возрастанию
	if (save.is_open())
	{
		for (int i = 0; i < my.size(); i++)
		{
			save << my[i] << endl;
		}
		save.close();
		cout << "\nОперация успешна" << endl;
	}
	else cout << "\nTrouble With save file\n";
	return;
}

void testsystem::Admin::RemoveTestsCategorys(string name_categorys)
{
	vector<string> my;
	ifstream load(path_to_db_all_tests);
	if (load.is_open())
	{
		while (!load.eof())
		{
			string s, s1, s2;
			load >> s >> s1 >> s2;
			if (s.length() == 0)
			{
				load.close();//файл пустой выходим
				break;
			}
			if (_strcmpi(s.c_str(), name_categorys.c_str()) == 0)//если совпадение
			{
				continue;
			}
			else
			{
				string g = s + " " + s1 + " " + s2; //в иных случаях заносим все другие строки в массив и пересохраняем файл
				my.push_back(g);
			}
		}
		load.close();
	}
	else
		cout << "\nCant open file ";

	ofstream save(path_to_db_all_tests);
	save.clear();
	sort(my.begin(), my.end(), [&](string s, string s1) { return (s[0] < s1[0]); });//сортирую лямбдой по возрастанию
	if (save.is_open())
	{
		for (int i = 0; i < my.size(); i++)
		{
			save << my[i] << endl;
		}
		save.close();
		cout << "\nОперация успешна" << endl;
	}
	else cout << "\nTrouble With save file\n";
	return;
}

void testsystem::Admin::AddNewUser()
{

beg:
	string us, ps;
	char a;
	cout << "\n=================ДОБАВЛЕНИЕ ПОЛЬЗОВАТЕЛЯ========================\n";
	cout << "\nВведите имя пользователя(x-вернуться в предыдущее меню): ";
	cout << "\nВвод: ";
	cin >> us;
	if (us == "x") return;
	ifstream load(source_all_users + "/" + us + ".bin", ios::binary);
	if (load.is_open())
	{
		cout << "\nПользователь уже есть в системе";
		load.close();
		goto beg;
	}
	else
	{
		load.close();
		AllUser b{ us };
		b.PhillInfo();
		ofstream save(source_all_users + "/" + us + ".bin", ios::binary);
		if (save.is_open())
		{
			b.SaveLogin(save);
		}
		save.close();
		save.open(db_all_logins, ios::binary | ios::app);
		int g = us.length() + 1;
		save.write((char*)& g, sizeof(int));
		save.write(us.c_str(), g);
		save.close();
		cout << "\nДобавление успешно, для продолжения нажмите любуш клавишу!" << endl;
		cin >> a;
		system("cls");
		return;
	}
}

void testsystem::Admin::MenuChangeuserInfo()
{
	system("cls");
	char a = ' ';
	cout << endl;
	while (a != '6')
	{
		cout << "1. Показывать все логины зарегистрированные в базе" << endl;
		cout << "2. Загрузить информацию о пользователе" << endl;//++
		cout << "3. Изменить данные" << endl; //++
		cout << "4. Очистить файл статистики" << endl;//++
		cout << "5. Удалить результаты тестирования(по названию)" << endl;//++
		cout << "6. Вернуться обратно" << endl;
		cout << "Мой выбор: ";
		cin >> a;
		switch (a)
		{
		case '1':  system("cls"); ShowAllUserFromDB(); break;
		case '2':  LoadInfoUser(); break;
		case '3': 	 ChangeuserInfo();  break;
		case '4':  ClearStatisticFile();  break;
		case '5':  RemoveResultTestAtNames();  break;
		default:
			break;
		}
	}
	system("cls");
}

void testsystem::Admin::LoadInfoUser()
{

beg:
	string us;
	system("cls");
	ShowAllUserFromDB();
	cout << endl;
	cout << "\n=======================================================================================================================\n";
	cout << "\nВведите имя пользователя(x-вернуться в предыдущее меню): ";
	cout << "\nВвод: ";
	cin >> us;
	if (us == "x") return;
	ifstream load(source_all_users + "/" + us + ".bin", ios::binary);
	if (!load.is_open())
	{
		cout << "\nНеккоректное имя";
		load.close();
		goto beg;
	}
	ifstream load1(source_all_users + "/" + us + ".bin", ios::binary);
	while (!load1.eof())
	{
		if (load1.peek() == EOF) break;
		AllUser::LoadLogin(load1);
	}
	load1.close();
	AllUser::ShowInfoUser();
	cout << "\n                                   СТАТИСТИКА ПОЛЬЗОВАТЕЛЯ" << endl;
	cout << "===================================================================================================================================================================================\n";
	list<Test> my;
	ifstream load2("Results/" + us + ".bin", ios::binary);
	if (load2.is_open())
	{
		while (!load2.eof())
		{
			if (load2.peek() == EOF) break;
			Test b;
			b.LoadTest(load2);
			my.push_back(b);
		}
		load2.close();
		list<Test>::iterator t = my.begin();
		int y = 11;
		cout << "День сдачи           Время            Название теста             Оценка            Количество вопросов      Завершен       Всего правильных ответов       Правильных ответов(%)" << endl;
		while (t != my.end())
		{	
			(*t).ShowInfoStat(y);
			y++;
			t++;
		}
	}
	else cout << "\nДанные отсутствуют" << endl;
	cout << "\n==================================================================================================================================================================================== \n";
	my.clear();
	load2.close();
	return;
}

void testsystem::Admin::LoadInfoUserName(string login)
{
	cout << "\n                                   СТАТИСТИКА ПОЛЬЗОВАТЕЛЯ" << endl;
	cout << "===================================================================================================================================================================================\n";
	list<Test> my;
	ifstream load2("Results/" + login + ".bin", ios::binary);
	if (load2.is_open())
	{
		while (!load2.eof())
		{
			if (load2.peek() == EOF) break;
			Test b;
			b.LoadTest(load2);
			my.push_back(b);
		}
		load2.close();
		list<Test>::iterator t = my.begin();
		int y = 11;
		cout << "День сдачи           Время            Название теста             Оценка            Количество вопросов      Завершен       Всего правильных ответов       Правильных ответов(%)" << endl;
		while (t != my.end())
		{
			(*t).ShowInfoStat(y);
			y++;
			t++;
		}
	}
	else cout << "\nДанные отсутствуют" << endl;
	cout << "\n==================================================================================================================================================================================== \n";
	my.clear();
	load2.close();
	return;
}

void testsystem::Admin::ChangeuserInfo()
{

beg:
	string us;
	system("cls");
	ShowAllUserFromDB();
	cout << endl;
	cout << "\n=======================================================================================================================\n";
	cout << "\n================ИЗМЕНЕНИЕ  ДАННЫХ ПОЛЬЗОВАТЕЛЯ=================================\n";
	cout << "\nВведите имя пользователя для редакторования(x-вернуться в предыдущее меню): ";
	cout << "\nВвод: ";
	cin >> us;
	if (us == "x") return;
	ifstream load(source_all_users + "/" + us + ".bin", ios::binary);
	if (!load.is_open())
	{
		cout << "\nНеккоректное имя";
		load.close();
		goto beg;
	}
	cout << endl;
	AllUser b{ us };
	b.PhillInfo();
	ofstream save(source_all_users + "/" + us + ".bin", ios::binary);
	save.clear();
	if (save.is_open())
	{
		b.SaveLogin(save);
	}
	save.close();
}

void testsystem::Admin::ClearStatisticFile()
{

beg:
	string us;
	char a;
	system("cls");
	ShowAllUserFromDB();
	cout << endl;
	cout << "\n=======================================================================================================================\n";
	cout << "\nВведите имя пользователя у которого удалить ВСЮ статистику(x-вернуться в предыдущее меню): ";
	cout << "\nВвод: ";
	cin >> us;
	if (us == "x") return;
	ifstream load(source_all_users + "/" + us + ".bin", ios::binary);
	if (!load.is_open())
	{
		cout << "\nНеккоректное имя,для возврата нажмите любую кнопку";
		load.close();
		cin >> a;
		goto beg;
	}
	ofstream save(file_statistics + "/" + us + ".bin", ios::binary);
	if (!save.is_open())
	{
		cout << "\nСтатистики нет для данного пользователя, для возврата нажмите любую кнопку";
		save.close();
		cin >> a;
		goto beg;
	}
	else
	{
		save.clear();
		save.close();
		cout << endl;
		cout << "\nСтатистика очищена!, для возврата нажмите любую кнопку";
		cin >> a;
		goto beg;
	}
	system("cls");
}

void testsystem::Admin::RemoveResultTestAtNames()
{

beg:
	string us;
	char a;
	system("cls");
	ShowAllUserFromDB();
	cout << endl;
	cout << "\n=======================================================================================================================\n";
	cout << "\nВведите имя пользователя у которого удалить статистику(x-вернуться в предыдущее меню): ";
	cout << "\nВвод: ";
	cin >> us;
	if (us == "x") return;
	ifstream load1(source_all_users + "/" + us + ".bin", ios::binary);
	if (!load1.is_open())
	{
		cout << "\nНеккоректное имя,для возврата нажмите любую кнопку";
		load1.close();
		cin >> a;
		goto beg;
	}
	string testname;
	cin.ignore();
	cin.clear();
	system("cls");
	LoadInfoUserName(us);
	cout << endl;
	cout << "\nВведите название теста для удаления статистики: ";
	getline(cin, testname);
	ifstream load(file_statistics + "/" + us + ".bin", ios::binary);
	if (!load.is_open())
	{
		cout << "\nСтатистики нет для данного пользователя, для возврата нажмите любую кнопку";
		load.close();
		cin >> a;
		goto beg;
	}
	else
	{
		vector<Test> my;
		while (!load.eof())
		{
			if (load.peek() == EOF) break;
			Test b;
			b.LoadTest(load);
			my.push_back(b);
		}
		load.close();
		ofstream save(file_statistics + "/" + us + ".bin", ios::binary);
		save.clear();
		save.close();
		save.open(file_statistics + "/" + us + ".bin", ios::binary);
		if (save.is_open())
		{

			for (int i = 0; i < my.size(); i++)
			{
				if (_strcmpi(my[i].GetTestname().c_str(), testname.c_str()) == 0) continue;
				else
					my[i].SaveTest(save);
			}

			save.close();
			my.clear();
			cout << "\nУспешно, для продолжения нажмите любую кнопку";
			cin >> a;
			return;

		}
		else cout << "\nSystem error cant open file";
	}
	system("cls");
}

void testsystem::Admin::StatisticsMenu()
{
	system("cls");
	char a = ' ';
	cout << endl;
	string g;
	while (a != '5')
	{
		cout << "1. Результаты всех пользователей" << endl;//++
		cout << "2. Резульртаты по названию тестов" << endl;//++ доделать проверку на наличие теста в общей базе тестов
		cout << "3. Результаты пользователя" << endl;//++
		cout << "5. Выйти в меню обратно" << endl;
		cout << "Мой выбор: ";
		cin >> a;
		switch (a)
		{
		case '1': system("cls"); ShowResultsAllusers(); break;
		case '2': 	system("cls"); ShowResultAtTestName(); break;
		case '3': 	system("cls"); 		ShowResultSomePerson();		break;
		case '5': 	system("cls"); return; break;
		default:
			break;
		}
	}
	system("cls");
}

void testsystem::Admin::ShowResultsAllusers()
{
	ifstream load1(db_all_logins, ios::binary);//открыл файл где хранятся все пользователи
	multimap<string, Test> multi;//храню имя пользователя и результат его тестирования
	cout << "Пользователь          День сдачи           Время            Название теста             Оценка            Количество вопросов      Завершен       Всего правильных ответов       Правильных ответов(%)" << endl;
	int y = 3;
	if (load1.is_open())
	{
		while (!load1.eof())//открыл вайл с логинами
		{
			if (load1.peek() == EOF) break;
			int n;
			char buff[50];
			load1.read((char*)& n, sizeof(int));
			load1.read(buff, n);
			string a = buff;
			ifstream load2("Results/" + a + ".bin", ios::binary);//загрузил даннные его тестирования
			ofstream save(path_to_save_statistic_user_seraching, ios::app);//этот сейф нужен для обычного сохранения, без мультимап
			if (load2.is_open())
			{
				while (!load2.eof())
				{
					if (load2.peek() == EOF) break;
					Test b1;
					console.GotoXy(1, y);
					cout << buff;
					b1.LoadTest(load2);
					b1.ShowInfoStat(y, true);
					y++;
					multi.insert(make_pair(a, b1)); //добавил имя пользователя и тест сданный им
				}
				save.close();
				load2.close();
			}
		}
		load1.close();
	}
	else
		cout << "\nSystem Error when read file\n";

	char z;
	cout << "\nz - save to file" << endl;
	cout << "x - return" << endl;
	cout << "Ввод: ";
	cin >> z;
	if (z == 'z')
	{
		ofstream save(path_to_save_statistic_user_seraching);
		multimap<string, Test>::iterator s = multi.begin();
		save << "Пользователь          День сдачи           Время            Название теста             Оценка            Количество вопросов      Завершен       Всего правильных ответов       Правильных ответов(%)" << endl;
		while (s != multi.end())
		{
			save << (*s).first << setw(20) << (*s).second;
			s++;
		}
		save.close();
	}
	multi.clear();
	return;
}

void testsystem::Admin::ShowResultAtTestName()
{
	string testname;
	cin.ignore();
	cin.clear();
	cout << "\nВведите название теста для формирования статистики: ";
	getline(cin, testname);
	system("cls");
	ifstream load1(db_all_logins, ios::binary);//открыл файл где хранятся все пользователи
	multimap<string, Test> multi;//храню имя пользователя и результат его тестирования
	int y = 3;
	cout << "Пользователь          День сдачи           Время            Название теста             Оценка            Количество вопросов      Завершен       Всего правильных ответов       Правильных ответов(%)" << endl;
	if (load1.is_open())
	{
		while (!load1.eof())//открыл вайл с логинами
		{
			if (load1.peek() == EOF) break;
			int n;
			char buff[50];
			load1.read((char*)& n, sizeof(int));
			load1.read(buff, n);
			string a = buff;
			ifstream load2("Results/" + a + ".bin", ios::binary);//загрузил даннные его тестирования
			ofstream save(path_to_save_statistic_user_seraching, ios::app);//этот сейф нужен для обычного сохранения, без мультимап
			if (load2.is_open())
			{
				while (!load2.eof())
				{
					if (load2.peek() == EOF) break;
					Test b1;
					b1.LoadTest(load2);
					if (_strcmpi(b1.GetTestname().c_str(), testname.c_str()) == 0)
					{
						multi.insert(make_pair(a, b1)); //добавил имя пользователя и тест сданный им	
						console.GotoXy(1, y);
						cout << buff;
						b1.ShowInfoStat(y, true);
						y++;
					}
				}
				save.close();
				load2.close();
			}
		}
		load1.close();
	}
	else
		cout << "\nSystem Error when read file\n";

	char z;
	cout << "\nz - save to file" << endl;
	cout << "x - return" << endl;
	cout << "Ввод: ";
	cin >> z;
	if (z == 'z')
	{
		ofstream save(path_to_save_statistic_test_seraching +"_"+ testname);
		multimap<string, Test>::iterator s = multi.begin();
		save << "Пользователь          День сдачи           Время            Название теста             Оценка            Количество вопросов      Завершен       Всего правильных ответов       Правильных ответов(%)" << endl;
		while (s != multi.end())
		{
			save << (*s).first << setw(20) << (*s).second;//вывожу на экран и сразу сохраняю

			s++;
		}
		save.close();
	}

	multi.clear();
}

void testsystem::Admin::ShowResultSomePerson()
{
	beg:
	string us;
	cout << "\nВведите имя пользователя(x-вернуться в предыдущее меню): ";
	cout << "\nВвод: ";
	cin >> us;
	if (us == "x") return;
	ifstream load(source_all_users + "/" + us + ".bin", ios::binary);
	if (!load.is_open())
	{
		cout << "\nНеккоректное имя";
		load.close();
		goto beg;
	}
	cout << "\n                                   СТАТИСТИКА ПОЛЬЗОВАТЕЛЯ" << endl;
	cout << "===================================================================================================================================================================================\n";
	multimap<string, Test> mult;
	list<Test> my;
	ifstream load2(file_statistics +"/" + us + ".bin", ios::binary);
	if (load2.is_open())
	{
		while (!load2.eof())
		{
			if (load2.peek() == EOF) break;
			Test b;
			b.LoadTest(load2);
			mult.insert(make_pair(us,b));// в листе реализовал перегруженный оператор сохранения в файл
			my.push_back(b);//у листов перегруженный сохранения в бин, поэтому в разные массивы временные
		}
		load2.close();
		list<Test>::iterator t = my.begin();
		int y = 10;
		cout << "День сдачи           Время            Название теста             Оценка            Количество вопросов      Завершен       Всего правильных ответов       Правильных ответов(%)" << endl;
		
		while (t != my.end())
		{
			(*t).ShowInfoStat(y);
			y++;
			t++;
		}
	}
	else cout << "\nДанные отсутствуют" << endl;
	cout << "\n==================================================================================================================================================================================== \n";
	char z;
	cout << "z - save to file" << endl;
	cout << "x - return" << endl;
	cout << "Ввод: ";
	cin >> z;
	if (z == 'z')
	{
		ofstream save(path_to_save_statistic_user_seraching + "_" + us);
		if (save.is_open())
		{
			save << "Пользователь        День сдачи           Время            Название теста             Оценка            Количество вопросов      Завершен       Всего правильных ответов       Правильных ответов(%)" << endl;
			for (auto i = mult.begin(); i != mult.end(); i++)
			{
				save << (*i).first << (*i).second << endl;
			}
		}
	}
	my.clear();
	mult.clear();
	load2.close();
	return;
}

void testsystem::Admin::TestingMenu()
{
	char a = ' ';
	cout << endl;
	string s, s1, s2;
	while (a != '4')
	{
		cout << endl;
		cout << "1. Подключить файл с тестами в общую базу" << endl;//++
		cout << "2. Отключить файл с тестами из общей базы" << endl; //
		cout << "3. Показать подключенные модули тестов" << endl; //++
		cout << "4. Вернуться обратно" << endl;
		cout << "Мой выбор: ";
		cin >> a;
		switch (a)
		{
		case '1': system("cls");
			cin.ignore();
			cin.clear();
			ShowTestModulesInDB();
			cout << endl;
			cout << "\nВведите название категории: ";
			cin >> s;
			cout << "\nВведите полный путь к файлу(Tests/Matematics/Matematic.txt): ";
			cin >> s1;
			cout << "\nВведите название теста: ";
			cin >> s2;
			AddCategoryAndTests(s, s1, s2);
			break;
		case '2': 	system("cls"); MenuRemoveTestFromDB(); break;
		case '3': system("cls"); ShowTestModulesInDB(); break;
		default:
			break;
		}
	}
	system("cls");
}

void testsystem::Admin::AddCategoryAndTests(string name_category, string filename_test, string testname)
{
	LoadCategorysFromDB();
ag:
	ifstream load(path_to_db_all_tests);
	if (load.is_open())
	{
		list<Category>::iterator l = categogys.begin();
		string cat, path, tname;
		int count = 0;
		while (!load.eof())
		{
			list<Category>::iterator l = categogys.begin();
			bool check = true;
			load >> cat >> path >> tname;
			if (cat.length() == 0 and count != 0)
			{
				load.close();
				return;//clear string == empty file
			}
			count++;
			while (l != categogys.end())
			{
				if (_strcmpi((*l).GetNameCategory().c_str(), cat.c_str()) == 0) check = false;
				l++;
			}
			if (!check)//если есть категория то добавим в нее тест, и сохраняем в общую базу название категории теста и путь к тесту
			{
				l = find_if(categogys.begin(), categogys.end(), [&](const Category& c) { return (_strcmpi(cat.c_str(), c.GetNameCategory().c_str()) == 0); });
				if ((*l).AddTest(filename_test, testname) == true)//if this test no exist will be create new test
				{
					load.close();
					ofstream save(path_to_db_all_tests, ios::app);//add categorys tol exist DB file for load next time
					if (save.is_open())
					{
						save << name_category << " " << filename_test << " " << testname << endl;
						save.close();
						cout << "\nВсе прошло успешно!";
						return;
					}
					else
						cout << "\nSystem error2 cant open file for save categorys";
				}
				else
				{
					load.close();
					return;
				}
			}
			else
			{
				load.close();
				Category b{ name_category };//если нету, создадим категорию, закинем в нее тест, и также сохраняем все в общей базе
				categogys.push_back(b);
				b.AddTest(filename_test, testname);
				ofstream save(path_to_db_all_tests, ios::app);//add categorys tol exist DB file for load next time
				if (save.is_open())
				{
					save << name_category << " " << filename_test << " " << testname << endl;
					save.close();
					cout << "\nВсе прошло успешно!";
					return;
				}
				else
					cout << "\nSystem error cant open file for save categorys";
			}
		}
	}
	else
	{
		ofstream save(path_to_db_all_tests);
		if (save.is_open())
		{
			cout << "\nБыл создан файл баззы данных";
			save.close();
			goto ag;
		}
	}
	//Математика Tests/Biologi/Biologi1.txt Алгебра Физика Tests/phisics/Базовый.txt ФизикаБазовая Физика Tests/phisics/Начальный.txt Пробный
}

void testsystem::Admin::ShowTestModulesInDB() const
{
	ifstream load(path_to_db_all_tests);//при старте программы загружаю в память все доступные категории тестирования
	if (load.is_open())
	{
		string s, s1, s2;
		string temp;
		int count = 0;
		while (!load.eof())
		{
			cout << "\n=====================================================================\n";
			load >> s >> s1 >> s2;
			if (s2 == temp)
			{
				load.close();
				return;//словили дубль название выходим, все названия тестов у меня уникальные и повторений нет
			}
			temp = s2;

			cout << "\nНазвание категории : " << s;
			cout << "\nРасположение теста : " << s1;
			cout << "\nНазвание теста : " << s2;
			count++;
		}
		load.close();
	}
	cout << "\n=====================================================================\n";
}

void testsystem::Admin::ShowAllUserFromDB() const
{
	ifstream load(db_all_logins);
	if (load.is_open())
	{
		cout << "\n=====================================================================\n";
		int count = 1;
		cout << "\n                 ПОЛЬЗОВАТЕЛИ ЗАРЕГИСТРИРОВАННЫЕ В СИСТЕМЕ(отображаются только логины)        \n";
		while (!load.eof())
		{

			if (load.peek() == EOF)
			{
				cout << "\n=====================================================================\n";
				load.close();
				return;
			}
			int n;
			char buff[100];
			load.read((char*)& n, sizeof(int));
			load.read(buff, n);
			cout << count++ << ". ";
			cout << buff << endl;
		}

		cout << "\n=====================================================================\n";
		load.close();
	}
	else 
		cout << "\nCant open files";
}


