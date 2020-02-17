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
		cout << "\n��������� ������������ �����!" << endl;
}

void testsystem::AllUser::SetLogin(string login)
{
	if (login.length() > 0)
		this->login = login;
	else
		cout << "\n��������� ������������ �����!" << endl;
}

void testsystem::AllUser::SetPassword(string password)
{
	if (password.length() > 0)
		this->password = password;
	else
		cout << "\n��������� ������������ �����!" << endl;
}

void testsystem::AllUser::SetFio(string fio)
{
	if (fio.length() > 0)
		this->fio = fio;
	else
		cout << "\n��������� ������������ �����!" << endl;
}

void testsystem::AllUser::SetPhone(string phone)
{
	if (phone.length() > 0)
		this->phone = phone;
	else
		cout << "\n��������� ������������ �����!" << endl;
}

void testsystem::AllUser::PhillInfo()
{

	cin.ignore();
	cin.clear();
agh:
	cout << "\n������� ������(x - ������� �������): ";
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
		cout << "\n���������� ������ 3 ������� �������, 3 �����, 3 ��������� �������";
		goto agh;
	}
	cin.ignore();
	cin.clear();
	cout << "\n������� �������/���/��������: ";
	getline(cin, fio);
	cout << "\n������� �������� �����: ";
	getline(cin, adress);
	cout << "\n������� ���������� �������: ";
	getline(cin, phone);
}

void testsystem::AllUser::ShowInfoUser() const
{
	system("cls");
	cout << "                  ���������� � ������������" << endl;
	cout << "�����: " << login << endl;
	cout << "���: " << fio << endl;
	cout << "�����: " << adress << endl;
	cout << "�������: " << phone << endl;

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
		cout << "���� �����           �����            �������� �����             ������            ���������� ��������      ��������       ����� ���������� �������       ���������� �������(%)" << endl;
		while (t != my.end())
		{
			(*t).ShowInfoStat(y);
			t++;
			y++;
		}
	}
	else cout << "\n������ �����������" << endl;
	cout << "\n========================================================================\n";	
	cout << "\n������� �������� �����: ";
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
			if (b.GetFinishedTest() == "���" and _strcmpi((b).GetTestname().c_str(), s.c_str()) == 0) { check = true; };
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
				if ((*t).GetFinishedTest() == "���" and _strcmpi((*t).GetTestname().c_str(), s.c_str()) == 0 and end_current_and_exit)
				{
					int last_question = ((*t)).GetLastNumberQuestion();//������� ����� ������� �� ������� �����������
					int count = 0;
					int user_mark_for_test;
					if (last_question != 0)
					{
						user_mark_for_test = (*t).GetTotalQuestions();
					}
					else  user_mark_for_test = 0;
					int count_of_questions = ((*t)).GetLastNumberQuestion();
					ifstream load((*t).GetFilename());
					if (load.is_open()) //������ ���� �� ������� �������
					{

						while (!load.eof())
						{
							if (count == last_question)
							{
								system("cls");

								cout << "\n==============================" << count_of_questions + 1 << "==============================\n";
								float g = (*t).LoadNextQuestion(load);//�������� � ����� � ����� ������� ������������

								if (g == -1)//��������� ������������� ����������
								{
									break;//������� ������ ������ == ����� �����
								}
								else
									if (g == -2) //pause
									{
										finish = false;
										(*t).SetFinishedTest("���");//������� ����� �� ����� ����� �����
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
								if (s.length() == 0) return -1;//���� ������ ������ ��� ����� ����� == ��������� ����
								if (s[0] == '>') 	count++;//������� ���������� ��������	
							}
						}
						load.close();
						if (user_mark_for_test + ((*t).GetMark()) == 0 and finish)//������� ��� ���� ���� �����
						{
							(*t).SetMark(1);
							(*t).SetCorrectAnswersNumber(0);
							end_current_and_exit = false;
						}
						else
						{
							int k2 = (12 / count_of_questions) * user_mark_for_test;
							(*t).SetMark(k2);// ��������� ����
							double k1 = ((((12.f / count_of_questions) * user_mark_for_test) / 12.f) * 100);//�������� % ������ �������
							(*t).SetCorrectAnswersNumber(k1);
							(*t).SetTotalQuestions(user_mark_for_test);//��������� ������ ������ � �����
							if (finish) 	(*t).SetFinishedTest("��");//
							(*t).SetLastNumberQuestion(count_of_questions);	//�������� ����� ���������� ������� ��� �������������� ����������� �� �����
							end_current_and_exit = false;
						}
					}

				}
				if (!finish) break;
				t++;
			}
			t = my.begin();
			ofstream save;
			save.open("Results/" + login + ".bin", ios::binary);//������������� ���� ���� � ������ ���������� ������ + ������ ����������
			save.clear();
			while (t != my.end())
			{
				(*t).SaveTest(save);
				t++;

			}
			save.close();
		}
	}
	if (!check) 			cout << "\n������ ���� �� ������!" << endl;

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
	cout << "\n                          ���������� ������������" << endl;
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
		cout << "���� �����           �����            �������� �����             ������            ���������� ��������      ��������       ����� ���������� �������       ���������� �������(%)" << endl;
		while (t != my.end())
		{
			(*t).ShowInfoStat(y);
			t++;
			y++;
		}
	}
	else cout << "\n������ �����������" << endl;
	cout << "\n========================================================================\n";
	my.clear();

}

void testsystem::AllUser::CategoGyMenu()
{
res:

	system("cls");
	cout << "                    ��������� ��������� ������������" << endl;
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
	cout << "\n �������� ����� ���������(0-�����): ";
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
	ifstream load("DBTests/db.txt");//��� ������ ��������� �������� � ������ ��� ��������� ��������� ������������
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
				return; //���� ����� �����
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
				i = find_if(categogys.begin(), categogys.end(), [&](const Category& a) {return (_strcmpi(s.c_str(), a.GetNameCategory().c_str()) == 0); });//��� �������� ���������, ����  ����� ���� ������, ���� ���� �������� � ��� ����
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
		cout << "1. �������� ������������" << endl;//++
		cout << "2. �������� ���������� � ������������" << endl;//++
		cout << "3. �������� ����������" << endl;//++
		cout << "4. ���������� �������������" << endl;//++
		cout << "5. ����� � ���� �������" << endl;
		cout << "��� �����: ";
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
		cout << "1. ������� ���� �� ����" << endl;//++
		cout << "2. ������� ������� ���������" << endl;//++
		cout << "3. �������" << endl;
		cout << "��� �����: ";
		cin >> a;
		switch (a)
		{
		case '1':		
			cin.ignore();
			cin.clear();
			cout << "\n������� �������� �����(x - �����): ";
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
			cout << "\n������� �������� ���������(x - �����): ";
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
				load.close();//���� ������ �������
				break;
			}
			if (_strcmpi(s2.c_str(), test_name.c_str()) == 0)//���� ����������
			{
				continue;
			}
			else
			{
				string g = s + " " + s1 + " " + s2; //� ���� ������� ������� ��� ������ ������ � ������ � ������������� ����
				my.push_back(g);
			}
		}
		load.close();
	}
	else
		cout << "\nCant open file ";

	ofstream save(path_to_db_all_tests);
	save.clear();
	sort(my.begin(), my.end(), [&](string s, string s1) { return (s[0] < s1[0]); });//�������� ������� �� �����������
	if (save.is_open())
	{
		for (int i = 0; i < my.size(); i++)
		{
			save << my[i] << endl;
		}
		save.close();
		cout << "\n�������� �������" << endl;
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
				load.close();//���� ������ �������
				break;
			}
			if (_strcmpi(s.c_str(), name_categorys.c_str()) == 0)//���� ����������
			{
				continue;
			}
			else
			{
				string g = s + " " + s1 + " " + s2; //� ���� ������� ������� ��� ������ ������ � ������ � ������������� ����
				my.push_back(g);
			}
		}
		load.close();
	}
	else
		cout << "\nCant open file ";

	ofstream save(path_to_db_all_tests);
	save.clear();
	sort(my.begin(), my.end(), [&](string s, string s1) { return (s[0] < s1[0]); });//�������� ������� �� �����������
	if (save.is_open())
	{
		for (int i = 0; i < my.size(); i++)
		{
			save << my[i] << endl;
		}
		save.close();
		cout << "\n�������� �������" << endl;
	}
	else cout << "\nTrouble With save file\n";
	return;
}

void testsystem::Admin::AddNewUser()
{

beg:
	string us, ps;
	char a;
	cout << "\n=================���������� ������������========================\n";
	cout << "\n������� ��� ������������(x-��������� � ���������� ����): ";
	cout << "\n����: ";
	cin >> us;
	if (us == "x") return;
	ifstream load(source_all_users + "/" + us + ".bin", ios::binary);
	if (load.is_open())
	{
		cout << "\n������������ ��� ���� � �������";
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
		cout << "\n���������� �������, ��� ����������� ������� ����� �������!" << endl;
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
		cout << "1. ���������� ��� ������ ������������������ � ����" << endl;
		cout << "2. ��������� ���������� � ������������" << endl;//++
		cout << "3. �������� ������" << endl; //++
		cout << "4. �������� ���� ����������" << endl;//++
		cout << "5. ������� ���������� ������������(�� ��������)" << endl;//++
		cout << "6. ��������� �������" << endl;
		cout << "��� �����: ";
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
	cout << "\n������� ��� ������������(x-��������� � ���������� ����): ";
	cout << "\n����: ";
	cin >> us;
	if (us == "x") return;
	ifstream load(source_all_users + "/" + us + ".bin", ios::binary);
	if (!load.is_open())
	{
		cout << "\n������������ ���";
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
	cout << "\n                                   ���������� ������������" << endl;
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
		cout << "���� �����           �����            �������� �����             ������            ���������� ��������      ��������       ����� ���������� �������       ���������� �������(%)" << endl;
		while (t != my.end())
		{	
			(*t).ShowInfoStat(y);
			y++;
			t++;
		}
	}
	else cout << "\n������ �����������" << endl;
	cout << "\n==================================================================================================================================================================================== \n";
	my.clear();
	load2.close();
	return;
}

void testsystem::Admin::LoadInfoUserName(string login)
{
	cout << "\n                                   ���������� ������������" << endl;
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
		cout << "���� �����           �����            �������� �����             ������            ���������� ��������      ��������       ����� ���������� �������       ���������� �������(%)" << endl;
		while (t != my.end())
		{
			(*t).ShowInfoStat(y);
			y++;
			t++;
		}
	}
	else cout << "\n������ �����������" << endl;
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
	cout << "\n================���������  ������ ������������=================================\n";
	cout << "\n������� ��� ������������ ��� ��������������(x-��������� � ���������� ����): ";
	cout << "\n����: ";
	cin >> us;
	if (us == "x") return;
	ifstream load(source_all_users + "/" + us + ".bin", ios::binary);
	if (!load.is_open())
	{
		cout << "\n������������ ���";
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
	cout << "\n������� ��� ������������ � �������� ������� ��� ����������(x-��������� � ���������� ����): ";
	cout << "\n����: ";
	cin >> us;
	if (us == "x") return;
	ifstream load(source_all_users + "/" + us + ".bin", ios::binary);
	if (!load.is_open())
	{
		cout << "\n������������ ���,��� �������� ������� ����� ������";
		load.close();
		cin >> a;
		goto beg;
	}
	ofstream save(file_statistics + "/" + us + ".bin", ios::binary);
	if (!save.is_open())
	{
		cout << "\n���������� ��� ��� ������� ������������, ��� �������� ������� ����� ������";
		save.close();
		cin >> a;
		goto beg;
	}
	else
	{
		save.clear();
		save.close();
		cout << endl;
		cout << "\n���������� �������!, ��� �������� ������� ����� ������";
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
	cout << "\n������� ��� ������������ � �������� ������� ����������(x-��������� � ���������� ����): ";
	cout << "\n����: ";
	cin >> us;
	if (us == "x") return;
	ifstream load1(source_all_users + "/" + us + ".bin", ios::binary);
	if (!load1.is_open())
	{
		cout << "\n������������ ���,��� �������� ������� ����� ������";
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
	cout << "\n������� �������� ����� ��� �������� ����������: ";
	getline(cin, testname);
	ifstream load(file_statistics + "/" + us + ".bin", ios::binary);
	if (!load.is_open())
	{
		cout << "\n���������� ��� ��� ������� ������������, ��� �������� ������� ����� ������";
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
			cout << "\n�������, ��� ����������� ������� ����� ������";
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
		cout << "1. ���������� ���� �������������" << endl;//++
		cout << "2. ����������� �� �������� ������" << endl;//++ �������� �������� �� ������� ����� � ����� ���� ������
		cout << "3. ���������� ������������" << endl;//++
		cout << "5. ����� � ���� �������" << endl;
		cout << "��� �����: ";
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
	ifstream load1(db_all_logins, ios::binary);//������ ���� ��� �������� ��� ������������
	multimap<string, Test> multi;//����� ��� ������������ � ��������� ��� ������������
	cout << "������������          ���� �����           �����            �������� �����             ������            ���������� ��������      ��������       ����� ���������� �������       ���������� �������(%)" << endl;
	int y = 3;
	if (load1.is_open())
	{
		while (!load1.eof())//������ ���� � ��������
		{
			if (load1.peek() == EOF) break;
			int n;
			char buff[50];
			load1.read((char*)& n, sizeof(int));
			load1.read(buff, n);
			string a = buff;
			ifstream load2("Results/" + a + ".bin", ios::binary);//�������� ������� ��� ������������
			ofstream save(path_to_save_statistic_user_seraching, ios::app);//���� ���� ����� ��� �������� ����������, ��� ���������
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
					multi.insert(make_pair(a, b1)); //������� ��� ������������ � ���� ������� ��
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
	cout << "����: ";
	cin >> z;
	if (z == 'z')
	{
		ofstream save(path_to_save_statistic_user_seraching);
		multimap<string, Test>::iterator s = multi.begin();
		save << "������������          ���� �����           �����            �������� �����             ������            ���������� ��������      ��������       ����� ���������� �������       ���������� �������(%)" << endl;
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
	cout << "\n������� �������� ����� ��� ������������ ����������: ";
	getline(cin, testname);
	system("cls");
	ifstream load1(db_all_logins, ios::binary);//������ ���� ��� �������� ��� ������������
	multimap<string, Test> multi;//����� ��� ������������ � ��������� ��� ������������
	int y = 3;
	cout << "������������          ���� �����           �����            �������� �����             ������            ���������� ��������      ��������       ����� ���������� �������       ���������� �������(%)" << endl;
	if (load1.is_open())
	{
		while (!load1.eof())//������ ���� � ��������
		{
			if (load1.peek() == EOF) break;
			int n;
			char buff[50];
			load1.read((char*)& n, sizeof(int));
			load1.read(buff, n);
			string a = buff;
			ifstream load2("Results/" + a + ".bin", ios::binary);//�������� ������� ��� ������������
			ofstream save(path_to_save_statistic_user_seraching, ios::app);//���� ���� ����� ��� �������� ����������, ��� ���������
			if (load2.is_open())
			{
				while (!load2.eof())
				{
					if (load2.peek() == EOF) break;
					Test b1;
					b1.LoadTest(load2);
					if (_strcmpi(b1.GetTestname().c_str(), testname.c_str()) == 0)
					{
						multi.insert(make_pair(a, b1)); //������� ��� ������������ � ���� ������� ��	
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
	cout << "����: ";
	cin >> z;
	if (z == 'z')
	{
		ofstream save(path_to_save_statistic_test_seraching +"_"+ testname);
		multimap<string, Test>::iterator s = multi.begin();
		save << "������������          ���� �����           �����            �������� �����             ������            ���������� ��������      ��������       ����� ���������� �������       ���������� �������(%)" << endl;
		while (s != multi.end())
		{
			save << (*s).first << setw(20) << (*s).second;//������ �� ����� � ����� ��������

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
	cout << "\n������� ��� ������������(x-��������� � ���������� ����): ";
	cout << "\n����: ";
	cin >> us;
	if (us == "x") return;
	ifstream load(source_all_users + "/" + us + ".bin", ios::binary);
	if (!load.is_open())
	{
		cout << "\n������������ ���";
		load.close();
		goto beg;
	}
	cout << "\n                                   ���������� ������������" << endl;
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
			mult.insert(make_pair(us,b));// � ����� ���������� ������������� �������� ���������� � ����
			my.push_back(b);//� ������ ������������� ���������� � ���, ������� � ������ ������� ���������
		}
		load2.close();
		list<Test>::iterator t = my.begin();
		int y = 10;
		cout << "���� �����           �����            �������� �����             ������            ���������� ��������      ��������       ����� ���������� �������       ���������� �������(%)" << endl;
		
		while (t != my.end())
		{
			(*t).ShowInfoStat(y);
			y++;
			t++;
		}
	}
	else cout << "\n������ �����������" << endl;
	cout << "\n==================================================================================================================================================================================== \n";
	char z;
	cout << "z - save to file" << endl;
	cout << "x - return" << endl;
	cout << "����: ";
	cin >> z;
	if (z == 'z')
	{
		ofstream save(path_to_save_statistic_user_seraching + "_" + us);
		if (save.is_open())
		{
			save << "������������        ���� �����           �����            �������� �����             ������            ���������� ��������      ��������       ����� ���������� �������       ���������� �������(%)" << endl;
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
		cout << "1. ���������� ���� � ������� � ����� ����" << endl;//++
		cout << "2. ��������� ���� � ������� �� ����� ����" << endl; //
		cout << "3. �������� ������������ ������ ������" << endl; //++
		cout << "4. ��������� �������" << endl;
		cout << "��� �����: ";
		cin >> a;
		switch (a)
		{
		case '1': system("cls");
			cin.ignore();
			cin.clear();
			ShowTestModulesInDB();
			cout << endl;
			cout << "\n������� �������� ���������: ";
			cin >> s;
			cout << "\n������� ������ ���� � �����(Tests/Matematics/Matematic.txt): ";
			cin >> s1;
			cout << "\n������� �������� �����: ";
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
			if (!check)//���� ���� ��������� �� ������� � ��� ����, � ��������� � ����� ���� �������� ��������� ����� � ���� � �����
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
						cout << "\n��� ������ �������!";
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
				Category b{ name_category };//���� ����, �������� ���������, ������� � ��� ����, � ����� ��������� ��� � ����� ����
				categogys.push_back(b);
				b.AddTest(filename_test, testname);
				ofstream save(path_to_db_all_tests, ios::app);//add categorys tol exist DB file for load next time
				if (save.is_open())
				{
					save << name_category << " " << filename_test << " " << testname << endl;
					save.close();
					cout << "\n��� ������ �������!";
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
			cout << "\n��� ������ ���� ����� ������";
			save.close();
			goto ag;
		}
	}
	//���������� Tests/Biologi/Biologi1.txt ������� ������ Tests/phisics/�������.txt ������������� ������ Tests/phisics/���������.txt �������
}

void testsystem::Admin::ShowTestModulesInDB() const
{
	ifstream load(path_to_db_all_tests);//��� ������ ��������� �������� � ������ ��� ��������� ��������� ������������
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
				return;//������� ����� �������� �������, ��� �������� ������ � ���� ���������� � ���������� ���
			}
			temp = s2;

			cout << "\n�������� ��������� : " << s;
			cout << "\n������������ ����� : " << s1;
			cout << "\n�������� ����� : " << s2;
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
		cout << "\n                 ������������ ������������������ � �������(������������ ������ ������)        \n";
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


