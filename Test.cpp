#include "Test.h"

void testsystem::Test::SetTIme(string time)
{
	this->time = time;
}

void testsystem::Test::SetDate(string date)
{
	this->date = date;
}

void testsystem::Test::SetMark(int mark)
{
	this->mark = mark;
}

void testsystem::Test::SetLastNumberQuestion(int number)
{
	last_question_int_test = number;
}

void testsystem::Test::SetFinishedTest(string finish)
{
	test_end = finish;
}

void testsystem::Test::SetTestname(string name_test)
{
	if (name_test.length() > 0)
	{
		testname = name_test;
	}
	else cout << "\nCheck test name";
}

string testsystem::Test::GetTestname() const
{
	return testname;
}

void testsystem::Test::SetFilename(string file)
{
	if (file.length() > 0) filename = file;
	else cout << "\nПроверьте правильность ввода названия файла";
}

void testsystem::Test::SetTotalQuestions(int number)
{
	total_question = number;
}

void testsystem::Test::SetCorrectAnswersNumber(double number)
{
	total_correct_answers = number;
}

string testsystem::Test::GetFilename() const
{
	return filename;
}

string testsystem::Test::GetTIme() const
{
	return time;
}

string testsystem::Test::GetDate() const
{
	return date;
}

int testsystem::Test::GetMark() const
{
	return mark;
}

int testsystem::Test::GetLastNumberQuestion() const
{
	return last_question_int_test;
}

string testsystem::Test::GetFinishedTest() const
{
	return test_end;
}

void testsystem::Test::ShowInfoStat(int y, bool rechenga_x)
{	
	int x2 = 0;
	if (rechenga_x) x2 += 23;
	console.GotoXy(x2, y);
	cout << date;
	console.GotoXy(x2+20, y);
	cout << time;
	console.GotoXy(x2 + 38, y);
	cout << testname;
	console.GotoXy(x2 + 68, y);
	cout << mark;
	console.GotoXy(x2 + 90, y);
	cout << last_question_int_test;
	console.GotoXy(x2 + 111, y);
	cout << test_end ;
	console.GotoXy(x2 + 135, y);
	cout << total_question;
	console.GotoXy(x2 + 160, y);
	cout  << setprecision(3)<< total_correct_answers;
}

int testsystem::Test::GetTotalQuestions() const
{
	return total_question;
}

double testsystem::Test::GetCorrectAnswersNumber() const
{
	return total_correct_answers;
}

void testsystem::Test::ShowQuestions()
{
	ifstream load(filename);
	if (load.is_open())
	{
		while (!load.eof())
		{
			int a = LoadNextQuestion(load);
			if (a == -1) break;
		}
	}
	else cout << "\nCannot open file";

	load.close();
}

float testsystem::Test::LoadNextQuestion(ifstream& load)
{
	setlocale(LC_ALL, "");

	int correct_answer = 0;
	int total_mark = 0;
	int count = 0;
	string s = "";
	vector<int> correct_answers;//храню сколько верных ответов в массиве
	vector<int> users_choice;//запоминаю ответы пользователя и сверяю верно ли он ответил с массивом выше
	do
	{
		s = "";
		getline(load, s);
		if (s.length() == 0) return -1;
		if (s[0] != '*' and s[0] != '<' and s[0] != '>') 	count++;//подсчет количество вопросов
		if (s[0] == '+')//верный ответ
		{
		
			correct_answers.push_back(count);
			string b;
			for (int i = 1; i < s.length(); i++)//убираю + с экрана
			{
				b += s[i];
			}
			s = b;
		}

		if (s[0] == '*')
		{
			string b;
			for (int i = 1; i < s.length(); i++)//убираю + с экрана
			{
				b += s[i];
			}
			s = b;
		}
		if (s != "<" and s != ">")
		{	
			cout << s << endl;//вывел сам вопрос, каунт 0 == метка на начало вопроса < , метка > окончание вопроса, + верные ответы
		}

	} while (s[0] != '>');
	int ans = correct_answers.size();	
	int max = count;
	int total = ans;
	for (int i = 0; i < ans; i++)
	{
	again:
		cout << "\nПрервать тест и вернуться обратно (x)";
		cout << "\nВариантов ответа(" << total << ")" << ", мой выбор: ";
		char g;
		cin >> g;
		if (g == 'x') return -2; //пауза
		if (g - '0' > max or g - '0' < 1 )
		{
			cout << "\nНеверный выбор!";
			goto again;
		}
		for (int i = 0; i < users_choice.size(); i++)
		{
			if (g-'0' == users_choice[i])
			{
				cout << "\nТакой вариант ответа уже внесен!";
				goto again;
			}
		}
		total--;
		users_choice.push_back(g-'0');
	}

	for (int i = 0; i < users_choice.size(); i++)
	{
		for (int c = 0; c < correct_answers.size(); c++)
		{
			if (users_choice[i] == correct_answers[c]) total_mark++;
		}
	}
	correct_answers.clear();
	users_choice.clear();
	if (total_mark != 0)
	{
		float b = (1.f / ans) * total_mark;//каждый вопрос может дать максимум 1 балл , если в вопросе 2 ответа и 4 варианта выбора, 1 / 4 -2  * набранные ответы
		return b;
	}
	else
		return 0;
}

void testsystem::Test::SaveTest(ofstream& s)
{
	int n;
	n = filename.length() + 1;
	s.write((char*)& n, sizeof(int));
	s.write(filename.c_str(), n);

	n = testname.length() + 1;
	s.write((char*)& n, sizeof(int));
	s.write(testname.c_str(), n);
		

	n = time.length() + 1;
	s.write((char*)& n, sizeof(int));
	s.write(time.c_str(), n);


	n = date.length() + 1;
	s.write((char*)& n, sizeof(int));
	s.write(date.c_str(), n);

	n = test_end.length() + 1;
	s.write((char*)& n, sizeof(int));
	s.write(test_end.c_str(), n);


	s.write((char*)& mark, sizeof(int));
	s.write((char*)& last_question_int_test, sizeof(int));
	s.write((char*)& total_question, sizeof(int));
	s.write((char*)& total_correct_answers, sizeof(double));


}

void testsystem::Test::LoadTest(ifstream& s)
{
	char b[200];
	int n;
	s.read((char*)& n, sizeof(int));
	s.read(b, n);
	filename = b;


	s.read((char*)& n, sizeof(int));
	s.read(b, n);
	testname = b;

	s.read((char*)& n, sizeof(int));
	s.read(b, n);
	time = b;

	s.read((char*)& n, sizeof(int));
	s.read(b, n);
	date = b;


	s.read((char*)& n, sizeof(int));
	s.read(b, n);
	test_end = b;


	s.read((char*)& mark, sizeof(mark));
	s.read((char*)& last_question_int_test, sizeof(last_question_int_test));
	s.read((char*)& total_question, sizeof(total_question));
	s.read((char*)& total_correct_answers, sizeof(double));
}



bool testsystem::Test::operator==(string name)
{
	if (testname == name) return true;
	else return false;
}



testsystem::Test::Test(string filename, string testname)
{
	this->filename = filename;
	this->testname = testname;
}


ostream& testsystem::operator<<(ostream& s, const Test& b1)
{
	s << setw(15) << " " << b1.GetDate()  << setw(10)<<  " " << b1.GetTIme() <<    setw(20) << b1.GetTestname() << " " << setw(20) << b1.GetMark() << " " << setw(20) << b1.GetLastNumberQuestion() <<   setw(20) << b1.GetFinishedTest() <<  setw(20) << b1.GetTotalQuestions() << setw(35) << b1.GetCorrectAnswersNumber() << endl;
	return s;// TODO: вставьте здесь оператор return
}
