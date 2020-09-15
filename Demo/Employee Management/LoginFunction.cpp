#include "Employee_Management.h"
#include "Login.h"

int welcome() {
	int choice;
	screenctrl* screen = screenctrl::instance();
	graphical_menu menu(screen->getbufferw() / 2, screen->getbufferh() / 2-4, 0);
	menu.setalign(1,1);
	choice = menu.operate("EMPLOYEE MANAGEMENT SYSTEM ", "Login\nExit\n") + 1;
	return choice;
}

void asteriskEncode(string &psw) {
	psw = "";
	int buffer;
	while (true) {
		buffer = _getch();
		if (buffer != 13 && buffer != 8)
		{
			putchar(42);
			psw += char(buffer);
		}
		if (buffer == 8 && psw != "")
		{
			psw.erase(psw.end() - 1, psw.end());
			cout << "\b \b";
		}
		if (buffer == 13 && psw != "") {
			cout << endl;
			break;
		}
	}
}

bool Account::login() {
	screenctrl* screen = screenctrl::instance();
	graphical_inputbox inputbox(screen->getbufferw() / 2-15, screen->getbufferh() / 2, 30, 3);
	inputbox.input("USERNAME: ", Username);
	inputbox.inputhidden("PASSWORD: ", Password);
	graphical_loader loader(2, screen->getbufferh() - 5, 20, "Check");
	loader.load(30);
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
		else
			getline(f, tmp);
	}
	return 0;
}

int logged() {
	int choice;
	choice = mainmenu.operate("Commands", "Show privileged actions\nView profile\nChange password\nLog out\n") + 1;
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

int incorrect_psw() {
	int choice;
	outputbox.display("The username or password is incorrect.");
	screenctrl* screen = screenctrl::instance();
	graphical_menu menu(screen->getbufferw() / 2, screen->getbufferh() - 7, 0);
	menu.setalign(1, 1);
	choice = menu.operate("Action", "Try again\nExit\n");
	return choice;
}

//Bug needs fixing!!!
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
			out << tmp << ',';
		}
		getline(ftmp, tmp);
		if (!ftmp.good()) {
			out << tmp;
			break;
		}
		else
			out << tmp << endl;
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
				cout << "Passwords do not match!\n";
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

void Staff::section() {
	int choice;
	while (true) {
		choice = mainmenu.operate("Privileged actions", "Information\nRecord\nBack\n") + 1;
		switch (choice) {
		case 1:
			Manage_Employee_Menu();
			break;
		case 2:

			break;
		case 3:
			mainmenu.clear();
			return;
		}
	}
}

void Account::StaffLogin(int choice) {
	Staff admin(*this);
	while (choice != 4) {
		outputbox.display("WELCOME, STAFF " + capitalize_name(admin.staff_name()));
		choice = logged();
		if (choice == 1)
			admin.section();
		else if (choice == 2)
			admin.view_profile();
		else if (choice == 3)
			changepsw();
	}
}

/*void Account::EmployeeLogin(int choice) {
	StdLogin std;
	getinfoStd(A, std);
	string name = std.fullname;
	transform(name.begin(), name.end(), name.begin(), toupper);
	while (choice != 0) {
		cout << "__________________________________________________________\n\n";
		cout << "WELCOME, " << name << endl << endl;
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
}*/

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

string capitalize_name(string name) {
	transform(name.begin(), name.end(), name.begin(), toupper);
	return name;
}