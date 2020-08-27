

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
	void create_account();	//функція яка отримує дані від користувача 
	void show_account() const;	//функція для показу даних на екран
	void modify();	//функція для додавання нових даних
	void dep(int);	//функція прийому суми та додавання суми до балансу 
	void draw(int);	//функція прийому суми та віднімання від суми залишку
	void report() const;	//функція для відображення даних в табличній формі
	int retacno() const;	//функція повернення номера рахунку
	int retdeposit() const;	//функція повернення суми залишку
	char rettype() const;	//функція повернення типу рахунку
};

void account::create_account()
{
	cout << "\nВведіть номер рахунку : ";
	cin >> acno;
	cout << "\n\nВведіть імя власника рахунку : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nВведіть тип рахунку (C/S) : ";
	cin >> type;
	type = toupper(type);
	cout << "\nВведіть початкову суму(>=500 для заощадження та >=1000 for зберігання ) : ";
	cin >> deposit;
	cout << "\n\n\nРахунок створено..";
}

void account::show_account() const
{
	cout << "\nНомер рахунка : " << acno;
	cout << "\nІмя власника рахунку : ";
	cout << name;
	cout << "\nТип рахунку : " << type;
	cout << "\nСума на балансі : " << deposit;
}


void account::modify()
{
	cout << "\nНомер рахунку : " << acno;
	cout << "\nНове імя власника рахунку : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nНовий тип рахунку : ";
	cin >> type;
	type = toupper(type);
	cout << "\nНова сума балансу : ";
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



void write_account();	//функція для запису в бінарний файл
void display_sp(int);	//функція відображення деталей рахунку
void modify_account(int);	//функція для оновлення запису в файл
void delete_account(int);	//функція для видалення запису з файлу
void display_all();		//функція для відображення всіх деталей рахунку
void deposit_withdraw(int, int); // функція депонування / зняття суми для даного рахунку
void intro();	//вступна функція екрану



int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		cout << "\n\n\n\tГОЛОВНЕ МЕНЮ";
		cout << "\n\n\t01. НОВИЙ РАХУНОК";
		cout << "\n\n\t02. СУМА ДЕПОЗИТУ";
		cout << "\n\n\t03. ЗНЯТИ СУМУ";
		cout << "\n\n\t04. ЗАПИТ БАЛАНСУ";
		cout << "\n\n\t05. ВЕСЬ СПИСОК ВЛАСНИКІВ РАХУНКІВ";
		cout << "\n\n\t06. ЗАКРИТИ РАХУНОК";
		cout << "\n\n\t07. ЗМІНИТИ РАХУНОК";
		cout << "\n\n\t08. ВИХІД";
		cout << "\n\n\tВиберіть опцію (1-8) ";
		cin >> ch;
		system("cls");
		switch (ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout << "\n\n\tВведіть номер рахунка : "; cin >> num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout << "\n\n\tВведіть номер рахунка : "; cin >> num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			cout << "\n\n\tВведіть номер рахунка : "; cin >> num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout << "\n\n\tВведіть номер рахунка : "; cin >> num;
			delete_account(num);
			break;
		case '7':
			cout << "\n\n\tВведіть номер рахунка : "; cin >> num;
			modify_account(num);
			break;
		case '8':
			cout << "\n\n\tДякуємо за те що користуєтесь нашою банківською системою";
			break;
		default:cout << "\a";
		}
		cin.ignore();
		cin.get();
	} while (ch != '8');
	return 0;
}



//    	функція для запису в файл


void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat", ios::binary | ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
	outFile.close();
}


//    	функція зчитування конкретного запису з файлу


void display_sp(int n)
{
	account ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "Файл не може бути відкритим !! ";
		return;
	}
	cout << "\nДЕТАЛІ БАЛАНСУ\n";
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
		cout << "\n\nНомера рахунку не існує";
}



//    	функція для зміни запису файлу


void modify_account(int n)
{
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "Файл не може бути відкритим !! ";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(account));
		if (ac.retacno() == n)
		{
			ac.show_account();
			cout << "\n\nВведіть деталі рахунку" << endl;
			ac.modify();
			int pos = (-1) * static_cast<int>(sizeof(account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			cout << "\n\n\t Запис оновлено ";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Запис не знайдено ";
}


//    	функція видалення запису файлу



void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "Файл не може бути відкритим !! ";
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
	cout << "\n\n\tЗапис видалено";
}


//    	функція для відображення всіх списків депозитних рахунків 


void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "Файл не може бути відкритим !! ";
		return;
	}
	cout << "\n\n\t\tСПИСОК ВЛАСНИКІВ РАХУНКІВ\n\n";
	cout << "====================================================\n";
	cout << "Номер рахунку       Імя           Тип рахунку\n";
	cout << "====================================================\n";
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}


//    	функція для внесення та зняття суми 


void deposit_withdraw(int n, int option)
{
	int amt;
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "Файл не може бути відкритим !! ";
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
				cout << "\n\n\tДЛЯ ВНЕСЕННЯ СУМИ ";
				cout << "\n\nВведіть суму яку потрібно внести ";
				cin >> amt;
				ac.dep(amt);
			}
			if (option == 2)
			{
				cout << "\n\n\tЗНЯТИ СУМУ ";
				cout << "\n\nВедіть суму для зняття";
				cin >> amt;
				int bal = ac.retdeposit() - amt;
				if ((bal < 500 && ac.rettype() == 'S') || (bal < 1000 && ac.rettype() == 'C'))
					cout << "Залишок балансу ";
				else
					ac.draw(amt);
			}
			int pos = (-1) * static_cast<int>(sizeof(ac));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			cout << "\n\n\t Запис оновлено";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Запис не знайдено !! ";
}



void intro()
{

	cin.get();
}


