#include "Employee_Management.h"
#include "Login.h"

int welcome() {
	int choice;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "\t\t\t\t\t\t\t" << "*************************************************************\n";
	SetConsoleTextAttribute(h, 13);
	cout << "\t\t\t\t\t\t\t\t\t " << "____________________________\n\n";
	cout << "\t\t\t\t\t\t\t\t\t" << "| EMPLOYEE MANAGEMENT SYSTEM |\n";
	cout << "\t\t\t\t\t\t\t\t\t " << "____________________________\n\n";
	SetConsoleTextAttribute(h, 10);
	cout << "\t\t\t\t\t\t\t\t\t" << "1. <Log in>\n";
	SetConsoleTextAttribute(h, 12);
	cout << "\t\t\t\t\t\t\t\t\t" << "0. <Exit>\n\n";
	SetConsoleTextAttribute(h, 15);
	cout << "\t\t\t\t\t\t\t" << "*************************************************************\n";
	cout << "\t\t\t\t\t\t\t\t\t" << "Choose your action: ";
	cin >> choice;
	return choice;
}

void Account::asteriskEncode() {
	Password = "";
	int buffer;
	while (true) {
		buffer = _getch();
		if (buffer != 13 && buffer != 8)
		{
			putchar(42);
			Password += char(buffer);
		}
		if (buffer == 8 && Password != "")
		{
			Password.erase(Password.end() - 1, Password.end());
			cout << "\b \b";
		}
		if (buffer == 13 && Password != "") {
			cout << endl;
			break;
		}
	}
}

bool Account::login() {
	string name, psw;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 14);
	cout << "\n\n";
	cout << "\t\t\t\t\t\t\t\t\t" << "USERNAME: ";
	SetConsoleTextAttribute(h, 15);
	cin >> name;
	SetConsoleTextAttribute(h, 14);
	cout << "\t\t\t\t\t\t\t\t\t" << "PASSWORD: ";
	SetConsoleTextAttribute(h, 15);
	asteriskEncode();
	bar2(20);
	return openfiles();
}

bool Account::openfiles() {
	int check;
	ifstream f;
	f.open("Staff.txt");
	role = 0;
	check = track(f);
	f.close();
	if (check == 1)
		return true;
	if (check == -1)
		return false;
	f.open("Employee.txt");
	role = 1;
	check = track(f);
	f.close();
	if (check == 1)
		return true;
	if (check == -1)
		return false;
	return false;
}

int Account::track(ifstream &f) {
	string tmp;
	while (f.good()) {
		getline(f, tmp, ',');
		if (tmp == Username) {
			getline(f, tmp, ',');
			if (tmp == Password)
				return 1;
			else
				return -1;
		}
		else {
			getline(f, tmp);
		}
	}
	return 0;
}

int logged() {
	int choice;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "1. Show privileged actions\n";
	cout << "2. View profile\n";
	cout << "3. Change password\n";
	SetConsoleTextAttribute(h, 12);
	cout << "0. Log out\n\n";
	SetConsoleTextAttribute(h, 15);
	cout << "Choose your action: ";
	cin >> choice;
	system("cls");
	return choice;
}

void clonefile(ifstream &in) {
	ofstream ftmp;
	ftmp.open("temp.txt");
	string tmp;
	while (true) {
		getline(in, tmp);
		if (!in.good()) {
			ftmp << tmp;
			break;
		}
		else
			ftmp << tmp << endl;
	}
	ftmp.close();
}

void Account::changeData(ofstream &out) {
	ifstream ftmp;
	ftmp.open("temp.txt");
	string tmp;
	while (true) {
		getline(ftmp, tmp, ',');
		if (tmp == Username) {
			out << tmp << ',';
			out << Password << ',';
			getline(ftmp, tmp, ',');
		}
		else {
			if (!ftmp.good()) {
				out << tmp;
				break;
			}
			else
				out << tmp << endl;
		}
	}
	ftmp.close();
	remove("temp.txt");
}

void Account::changepswInFile() {
	string txt;
	if (role == 0)
		txt = "Staff.txt";
	if (role == 1)
		txt = "Employee.txt";
	ifstream fin;
	fin.open(txt);
	clonefile(fin);
	fin.close();
	ofstream fout;
	fout.open(txt);
	changeData(fout);
	fout.close();
}

void Account::changepsw() {
	string tmp1, tmp2;
	int choice;
	while (true) {
		cout << "Enter current password: ";
		asteriskEncode(tmp1);
		if (tmp1 != Password) {
			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

			SetConsoleTextAttribute(h, 12);
			cout << "The password is incorrect.\n";
			SetConsoleTextAttribute(h, 15);
			cout << "1. Try again\t\t0. Back\n";
			cout << "Choose your action:\t";
			cin >> choice;
			if (choice == 0)
				return;
			system("cls");
		}
		else {
			cout << "Enter new password: ";
			asteriskEncode(tmp1);
			cout << "Enter new password again: ";
			asteriskEncode(tmp2);
			if (tmp1 != tmp2) {
				HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(h, 12);
				cout << "Password does not match!\n";
				SetConsoleTextAttribute(h, 15);
				cout << "1. Try again\t\t0. Back\n";
				cout << "Choose your action:\t";
				cin >> choice;
				if (choice == 0)
					return;
				else {
					system("cls");
					continue;
				}
			}
			else {
				Password = tmp1;
				changepswInFile();
				break;
			}
		}
	}
}

void section() {
	int choice;
	while (true) {
		cout << "__________________________________________________________\n\n";
		cout << "\t\t1. Information\n";
		cout << "\t\t2. Record\n";
		cout << "\t\t0. Back\n";
		cout << "__________________________________________________________\n\n";
		cout << "Choose a section: ";
		cin >> choice;
		system("cls");
		switch (choice) {
		case 1:

			break;
		case 2:

			break;
		case 0:
			return;
		}
	}
}

void StaffLog(User &A, int choice) {
	Staff admin;
	getinfoStaff(A, admin);
	string name = admin.fullname;
	transform(name.begin(), name.end(), name.begin(), toupper);
	while (choice != 0) {
		cout << "__________________________________________________________\n\n";
		cout << "\t\tWELCOME, STAFF " << name << endl << endl;
		cout << "__________________________________________________________\n\n";
		choice = logged();
		if (choice == 1) {
			section();
		}
		if (choice == 2) {
			cout << "__________________________________________________________\n\n";
			cout << "Username: " << A.username << endl;
			cout << "Fullname: " << admin.fullname << endl;
			cout << "Gender: " << ((admin.gender == 0) ? "Male\n" : "Female\n");
			cout << "__________________________________________________________\n";
			system("pause");
		}
		if (choice == 3) {
			changepsw(A);
		}
		system("cls");
	}
}

void StdLog(User &A, int choice) {
	StdLogin std;
	getinfoStd(A, std);
	string name = std.fullname;
	transform(name.begin(), name.end(), name.begin(), toupper);
	while (choice != 0) {
		cout << "__________________________________________________________\n\n";
		cout << "WELCOME, STUDENT " << name << endl << endl;
		cout << "__________________________________________________________\n\n";
		choice = logged();
		if (choice == 1) {
			int id = stoi(A.username);

		}
		if (choice == 2) {
			cout << "__________________________________________________________\n\n";
			cout << "ID: " << A.username << endl;
			cout << "Fullname: " << std.fullname << endl;
			cout << "Gender: " << std.gender << endl;
			cout << "Day of Birth:" << (std.DoB.day > 9 ? " " : " 0") << std.DoB.day;
			cout << (std.DoB.month > 9 ? "/" : "/0") << std.DoB.month;
			cout << '/' << std.DoB.year << endl;
			cout << "Class: " << std.classname << endl;
			cout << "__________________________________________________________\n";
			system("pause");
		}
		if (choice == 3) {
			changepswStd(A, std.classname);
		}
		system("cls");
	}
}

void bar2(int n)
{
	const char a = (char)177, b = (char)177;
	cout << "\n\n\n\t\t\t\t\t\t\t\t\t\tLOADING.....";
	cout << "\n\n\n";
	cout << "\t\t\t\t\t\t\t\t\t";
	cout << "0% ";
	for (int i = 0; i <= 25; i++)
	{
		cout << a;
		Sleep(n);
	}
	cout << "\r";
	cout << "\t\t\t\t\t\t\t\t\t";
	for (int i = 0; i <= 25; i++)
	{
		cout << b;
		Sleep(n);
	}
	cout << " 100%" << endl;
	cout << "\n\t\t\t\t\t\t\t\t\t\t  DONE!\n\n";
}
