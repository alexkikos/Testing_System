#include "Category.h"

void testsystem::Category::SetNameCategory(string name_category)
{
	if (name_category.length() > 0)
	{
		this->name_category = name_category;
	}
	else cout << "\nCheck names category";
}

string testsystem::Category::GetNameCategory() const
{
	return name_category;
}

void testsystem::Category::ShowCategory() const
{
	cout << name_category << endl;

}

void testsystem::Category::ShowTestInCategory()
{
	if (tests.size() > 0)
	{
		system("cls");
		cout << "\n               СПИСОК ДОСТУПНЫХ ТЕСТОВ" << endl;
		cout << "\n===============================================================\n";
		list<Test>::iterator t = tests.begin();
		int count = 1;
		while (t != tests.end())
		{
			cout << count++ << ". " << (*t++).GetTestname() << endl;
		}	
		cout << "\n===============================================================\n";
	}
}

int testsystem::Category::BeginTest(string name_test, string login)
{
	system("cls");
	list<Test>::iterator t = tests.begin();
	bool c = false;
	while (t != tests.end())
	{
		if (_strcmpi((*t).GetTestname().c_str(),name_test.c_str()) == 0 )
		{
			c = true;
			break;
		}
		t++;
	}
	if (c)
	{

		float user_mark_for_test = 0;//количество заработанных балов во время прохождения теста
		int count_of_questions = 0;	//количество вопросов в тесте
		int g2 = 1;
		bool finish = true;//логическай переменная закончили тест или нет, чтобы вносить соотв результат
		ifstream load((*t).GetFilename());//гружу нужный файл с тестом
		if (load.is_open())
		{
			while (!load.eof())
			{
				system("cls");
	
				cout << "\n==============================" << g2++ << "==============================\n";
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
		}
		system("cls");
		load.close();	
		if (user_mark_for_test == 0)//отметка что тест сдан плохо
		{
			(*t).SetMark(1);
			(*t).SetCorrectAnswersNumber(0);	
		}
		else
		{
			(*t).SetMark((12 / count_of_questions) * user_mark_for_test);// набранные балы
			double k1 = ((( (12.f / count_of_questions) * user_mark_for_test) / 12.f) * 100);//вычисляю % верных ответов
			(*t).SetCorrectAnswersNumber( k1);
		}
		time_t a = time(0);//записываю время сдачи теста
		tm *ltm = localtime(&a);
		string g = to_string(ltm->tm_hour)+":";
		g += to_string(ltm->tm_min) + ":";
		g+=to_string(ltm->tm_sec);
		(*t).SetDate(__DATE__);
		(*t).SetTIme(g);
		(*t).SetLastNumberQuestion(count_of_questions);	//сохраняю номер последнего вопроса для восстановления прохождения по тесту
		(*t).SetTotalQuestions(user_mark_for_test);//записываю верные ответы в тесте
		if (finish) (*t).SetFinishedTest("Да");//метка успешного прохождения теста
		ofstream save;
		save.open("Results/" + login + ".bin", ios::binary | ios::app);//дописываем результат теста в пользователский файл результатов
		if (save.is_open())
		{		
			(*t).SaveTest(save);	
		}
		save.close();
		return 0;
	}
	else return -1;

}



bool testsystem::Category::FindTestName(string test_name)
{
	list<Test>::iterator s = tests.begin();
	s = find(tests.begin(), tests.end(), test_name);
	if (s != tests.end())
	{
		return true;
	}
	else return false;
}

//добавления теста из под админ панели
void testsystem::Category::AddTest()
{
	rep:
	string s, s1;
	cout << "\nПуть к файлу с тестом: ";
	cin >> s;
	ifstream test(s);
	if (!test.is_open())
	{
		cout << "\nФайл не найден";
		goto rep;
	}
	else
		test.close();
	cout << "\nНазвание теста: ";
	cin >> s1;
	Test a{ s,s1 };
	tests.push_back(a);

}

void testsystem::Category::Menu(string login)
{
	system("cls");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "\n==========================" << name_category << "=========================================\n";
	char a = ' ';
	int b;
	string name;
	while (a != '3')
	{
		cout << endl;
		cout << "1. Просмотреть список доступных тестов" << endl;
		cout << "2. Пройти тест" << endl;
		cout << "3. Вернуться обратно" << endl;
		cout << "Мой выбор: ";
		cin >> a;
		switch (a)
		{
		case '1': ShowTestInCategory(); break;
		case '2':
			ShowTestInCategory();
			cout << endl;
			cout << "Введите название теста (x - назад): ";
			cin.clear();
			cin.ignore();
			getline(cin, name);
			if (name == "x")
			{
				system("cls"); 
				return;
			}
 			b = BeginTest(name, login);
			if (b < 0) cout << "\nПроверьте правильность ввода названия теста!";
			break;
		case '3': system("cls"); return;break;
		default: system("cls");
			break;
		}
	}
	system("cls");
}

void testsystem::Category::ShowTestResult()
{
	list<Test>::iterator b = tests.begin();
	int y = 5;
	while (b != tests.end())
	{
	
		(*b).ShowInfoStat(y);
		y++;
		b++;
	}
}

bool testsystem::Category::AddTest(string filename, string testname)
{
	ifstream load(filename);
	if (!load.is_open())
	{
		cout << "\nПроверьте правильность пути к файлу, не могу его открыть";
		load.close();
		return false;
	}
	else load.close();
	list<Test>::iterator h = tests.begin();
	
	h = find_if(tests.begin(), tests.end(), [&](const Test& s1) { return (_strcmpi(testname.c_str(),s1.GetTestname().c_str())==0); });
	if (h != tests.end())
	{
		
		return false;
	}
	else
	{
		h = tests.begin();
		h = find_if(tests.begin(), tests.end(), [&](const Test& s1) { return (_strcmpi(filename.c_str(), s1.GetFilename().c_str()) == 0); });
		if (h != tests.end())
		{
			cout << "\nТакой файл с тестом существует";
			return false;
		}
		else
		{
			Test b{ filename, testname };
			tests.push_back(b);
			return true;
		}
	}

}

void testsystem::Category::LoadCategory(ifstream& load)
{
	int n;
	load.read((char*)& n, sizeof(int));
	char buff[100];
	load.read(buff, n);
	name_category = buff;	
}



bool testsystem::Category::operator==(string name)
{
	if (this->name_category == name) return true;
	else return false;
}

testsystem::Category::Category(string name_categogy, string testfile, string testname)
{
	SetNameCategory(name_categogy);
	Test a { testfile,testname };
	tests.push_back(a);

}

testsystem::Category::Category()
{

}

testsystem::Category::Category(string name_category)
{
	this->name_category = name_category;

}

testsystem::Category::~Category()
{
	tests.clear();
}
