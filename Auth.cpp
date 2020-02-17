#include "Auth.h"

void testsystem::Auth::Rega()
{
beg:
	string us, ps;
	cout << "\n������� ��� ������������(x - �������): ";
	cin >> us;
	if (us == "x") return;
	ifstream load(source_all_users + "/" + us + ".bin", ios::binary);
	if (load.is_open())
	{
		cout << "\n������������ ���";
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
		userspace.UserSpaceMenu(b);

	}

}

void testsystem::Auth::UserLogin()
{
	system("cls");
	char a = ' ';
	cout << endl;
	while (a != '3')
	{
		cout << "1. ����� � �������" << endl;
		cout << "2. �����������" << endl;
		cout << "3. ����� � ���� �������" << endl;
		cout << "��� �����: ";
		cin >> a;
		switch (a)
		{
		case '1': ConnectToAccount(); break;
		case '2': 	system("cls"); Rega(); break;
		case '3': return; break;
		default:
			break;
		}
	}
	system("cls");
}

void testsystem::Auth::Menu()
{
	char a = ' ';
	while (a != '3')
	{
		switch (a)
		{
		case '1': system("cls"); UserLogin(); break;
		case '2': system("cls"); LoginAdmin(); break;
		default:
			break;
		}
		cout << "1. ������������" << endl;
		cout << "2. �����" << endl;
		cout << "3. �����" << endl;
		cout << "��� �����: ";
		cin >> a;
	}
	system("cls");
}

void testsystem::Auth::LoginAdmin()
{
beg:

	string us, ps;
	cout << "\n������� ��� ������������(x - �������): ";
	cin >> us;
	if (us == "x") return;
	if (us != "admin")
	{
		cout << "\n������������ ���";
		goto beg;
	}
	else
	{
		ifstream load(source_all_users + "/" + us + ".bin", ios::binary);
		cout << "\n������� ������: ";
		cin >> ps;
		int n;
		string a;
		char buff[200];
		load.read((char*)& n, sizeof(int));//login
		load.read(buff, n);
		load.read((char*)& n, sizeof(int));//pass
		load.read(buff, n);
		a = buff;
		if (a != ps)
		{
			cout << "\n�������� ������!";
			load.close();
			goto beg;
		}
		else {
			load.close();  adminspace.Menu();
		}
	}
}

void testsystem::Auth::ConnectToAccount()
{

beg:

	string us, ps;
	cout << "\n������� ��� ������������(� - �����): ";
	cin >> us;
	if (us == "x") return;
	ifstream load(source_all_users + "/" + us + ".bin", ios::binary);
	if (!load.is_open())
	{
		cout << "\n������������ ���";
		load.close();
		goto beg;
	}
	else
	{
		cout << "\n������� ������: ";
		cin >> ps;
		int n;
		string a;
		char buff[200];
		load.read((char*)& n, sizeof(int));//login
		load.read(buff, n);
		load.read((char*)& n, sizeof(int));//pass
		load.read(buff, n);
		a = buff;
		if (a != ps)
		{
			cout << "\n�������� ������!";
			load.close();
			goto beg;
		}
		else
		{
			load.close();
			ifstream load(source_all_users + "/" + us + ".bin", ios::binary);
			if (load.is_open())
			{
				AllUser b{ "1" };
				b.LoadLogin(load);
				load.close();
				userspace.UserSpaceMenu(b);
			}
		}
	}
}



testsystem::Auth::Auth(string source_file, string db_all_logins)
{
	source_all_users = source_file;
	this->db_all_logins = db_all_logins;

}
