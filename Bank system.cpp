

#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;



class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
public:
	void create_account();	//������� ��� ������ ��� �� ����������� 
	void show_account() const;	//������� ��� ������ ����� �� �����
	void modify();	//������� ��� ��������� ����� �����
	void dep(int);	//������� ������� ���� �� ��������� ���� �� ������� 
	void draw(int);	//������� ������� ���� �� �������� �� ���� �������
	void report() const;	//������� ��� ����������� ����� � �������� ����
	int retacno() const;	//������� ���������� ������ �������
	int retdeposit() const;	//������� ���������� ���� �������
	char rettype() const;	//������� ���������� ���� �������
};

void account::create_account()
{
	cout << "\n������ ����� ������� : ";
	cin >> acno;
	cout << "\n\n������ ��� �������� ������� : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\n������ ��� ������� (C/S) : ";
	cin >> type;
	type = toupper(type);
	cout << "\n������ ��������� ����(>=500 ��� ����������� �� >=1000 for ��������� ) : ";
	cin >> deposit;
	cout << "\n\n\n������� ��������..";
}

void account::show_account() const
{
	cout << "\n����� ������� : " << acno;
	cout << "\n��� �������� ������� : ";
	cout << name;
	cout << "\n��� ������� : " << type;
	cout << "\n���� �� ������ : " << deposit;
}


void account::modify()
{
	cout << "\n����� ������� : " << acno;
	cout << "\n���� ��� �������� ������� : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\n����� ��� ������� : ";
	cin >> type;
	type = toupper(type);
	cout << "\n���� ���� ������� : ";
	cin >> deposit;
}


void account::dep(int x)
{
	deposit += x;
}

void account::draw(int x)
{
	deposit -= x;
}

void account::report() const
{
	cout << acno << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}

int account::retacno() const
{
	return acno;
}

int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}



void write_account();	//������� ��� ������ � ������� ����
void display_sp(int);	//������� ����������� ������� �������
void modify_account(int);	//������� ��� ��������� ������ � ����
void delete_account(int);	//������� ��� ��������� ������ � �����
void display_all();		//������� ��� ����������� ��� ������� �������
void deposit_withdraw(int, int); // ������� ����������� / ������ ���� ��� ������ �������
void intro();	//������� ������� ������



int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		cout << "\n\n\n\t������� ����";
		cout << "\n\n\t01. ����� �������";
		cout << "\n\n\t02. ���� ��������";
		cout << "\n\n\t03. ����� ����";
		cout << "\n\n\t04. ����� �������";
		cout << "\n\n\t05. ���� ������ ������ʲ� �����ʲ�";
		cout << "\n\n\t06. ������� �������";
		cout << "\n\n\t07. �̲���� �������";
		cout << "\n\n\t08. ��ղ�";
		cout << "\n\n\t������� ����� (1-8) ";
		cin >> ch;
		system("cls");
		switch (ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout << "\n\n\t������ ����� ������� : "; cin >> num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout << "\n\n\t������ ����� ������� : "; cin >> num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			cout << "\n\n\t������ ����� ������� : "; cin >> num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout << "\n\n\t������ ����� ������� : "; cin >> num;
			delete_account(num);
			break;
		case '7':
			cout << "\n\n\t������ ����� ������� : "; cin >> num;
			modify_account(num);
			break;
		case '8':
			cout << "\n\n\t������ �� �� �� ����������� ����� ���������� ��������";
			break;
		default:cout << "\a";
		}
		cin.ignore();
		cin.get();
	} while (ch != '8');
	return 0;
}



//    	������� ��� ������ � ����


void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat", ios::binary | ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
	outFile.close();
}


//    	������� ���������� ����������� ������ � �����


void display_sp(int n)
{
	account ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "���� �� ���� ���� �������� !! ";
		return;
	}
	cout << "\n����˲ �������\n";
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		if (ac.retacno() == n)
		{
			ac.show_account();
			flag = true;
		}
	}
	inFile.close();
	if (flag == false)
		cout << "\n\n������ ������� �� ����";
}



//    	������� ��� ���� ������ �����


void modify_account(int n)
{
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "���� �� ���� ���� �������� !! ";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(account));
		if (ac.retacno() == n)
		{
			ac.show_account();
			cout << "\n\n������ ����� �������" << endl;
			ac.modify();
			int pos = (-1) * static_cast<int>(sizeof(account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			cout << "\n\n\t ����� �������� ";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n ����� �� �������� ";
}


//    	������� ��������� ������ �����



void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "���� �� ���� ���� �������� !! ";
		return;
	}
	outFile.open("Temp.dat", ios::binary);
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		if (ac.retacno() != n)
		{
			outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat", "account.dat");
	cout << "\n\n\t����� ��������";
}


//    	������� ��� ����������� ��� ������ ���������� ������� 


void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "���� �� ���� ���� �������� !! ";
		return;
	}
	cout << "\n\n\t\t������ ������ʲ� �����ʲ�\n\n";
	cout << "====================================================\n";
	cout << "����� �������       ���           ��� �������\n";
	cout << "====================================================\n";
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}


//    	������� ��� �������� �� ������ ���� 


void deposit_withdraw(int n, int option)
{
	int amt;
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "���� �� ���� ���� �������� !! ";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(account));
		if (ac.retacno() == n)
		{
			ac.show_account();
			if (option == 1)
			{
				cout << "\n\n\t��� �������� ���� ";
				cout << "\n\n������ ���� ��� ������� ������ ";
				cin >> amt;
				ac.dep(amt);
			}
			if (option == 2)
			{
				cout << "\n\n\t����� ���� ";
				cout << "\n\n����� ���� ��� ������";
				cin >> amt;
				int bal = ac.retdeposit() - amt;
				if ((bal < 500 && ac.rettype() == 'S') || (bal < 1000 && ac.rettype() == 'C'))
					cout << "������� ������� ";
				else
					ac.draw(amt);
			}
			int pos = (-1) * static_cast<int>(sizeof(ac));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			cout << "\n\n\t ����� ��������";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n ����� �� �������� !! ";
}



void intro()
{

	cin.get();
}


