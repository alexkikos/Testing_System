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
		cout << "\n               ������ ��������� ������" << endl;
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

		float user_mark_for_test = 0;//���������� ������������ ����� �� ����� ����������� �����
		int count_of_questions = 0;	//���������� �������� � �����
		int g2 = 1;
		bool finish = true;//���������� ���������� ��������� ���� ��� ���, ����� ������� ����� ���������
		ifstream load((*t).GetFilename());//����� ������ ���� � ������
		if (load.is_open())
		{
			while (!load.eof())
			{
				system("cls");
	
				cout << "\n==============================" << g2++ << "==============================\n";
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
		}
		system("cls");
		load.close();	
		if (user_mark_for_test == 0)//������� ��� ���� ���� �����
		{
			(*t).SetMark(1);
			(*t).SetCorrectAnswersNumber(0);	
		}
		else
		{
			(*t).SetMark((12 / count_of_questions) * user_mark_for_test);// ��������� ����
			double k1 = ((( (12.f / count_of_questions) * user_mark_for_test) / 12.f) * 100);//�������� % ������ �������
			(*t).SetCorrectAnswersNumber( k1);
		}
		time_t a = time(0);//��������� ����� ����� �����
		tm *ltm = localtime(&a);
		string g = to_string(ltm->tm_hour)+":";
		g += to_string(ltm->tm_min) + ":";
		g+=to_string(ltm->tm_sec);
		(*t).SetDate(__DATE__);
		(*t).SetTIme(g);
		(*t).SetLastNumberQuestion(count_of_questions);	//�������� ����� ���������� ������� ��� �������������� ����������� �� �����
		(*t).SetTotalQuestions(user_mark_for_test);//��������� ������ ������ � �����
		if (finish) (*t).SetFinishedTest("��");//����� ��������� ����������� �����
		ofstream save;
		save.open("Results/" + login + ".bin", ios::binary | ios::app);//���������� ��������� ����� � ��������������� ���� �����������
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

//���������� ����� �� ��� ����� ������
void testsystem::Category::AddTest()
{
	rep:
	string s, s1;
	cout << "\n���� � ����� � ������: ";
	cin >> s;
	ifstream test(s);
	if (!test.is_open())
	{
		cout << "\n���� �� ������";
		goto rep;
	}
	else
		test.close();
	cout << "\n�������� �����: ";
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
		cout << "1. ����������� ������ ��������� ������" << endl;
		cout << "2. ������ ����" << endl;
		cout << "3. ��������� �������" << endl;
		cout << "��� �����: ";
		cin >> a;
		switch (a)
		{
		case '1': ShowTestInCategory(); break;
		case '2':
			ShowTestInCategory();
			cout << endl;
			cout << "������� �������� ����� (x - �����): ";
			cin.clear();
			cin.ignore();
			getline(cin, name);
			if (name == "x")
			{
				system("cls"); 
				return;
			}
 			b = BeginTest(name, login);
			if (b < 0) cout << "\n��������� ������������ ����� �������� �����!";
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
		cout << "\n��������� ������������ ���� � �����, �� ���� ��� �������";
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
			cout << "\n����� ���� � ������ ����������";
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
