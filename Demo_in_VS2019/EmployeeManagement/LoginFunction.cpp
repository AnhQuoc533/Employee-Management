#include "Employee_Management.h"
#include "Login.h"

int welcome() {
	screenctrl* screen = screenctrl::instance();
	graphical_menu menu(screen->getbufferw() / 2, screen->getbufferh() / 2-4, 0);
	menu.setalign(1,1);
	return menu.operate("EMPLOYEE MANAGEMENT SYSTEM", "Login\nExit");
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
	return mainmenu.operate("COMMANDS", "Show privileged actions\nView profile\nChange password\nLog out") + 1;
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
	outputbox.display("The username or password is incorrect.");
	screenctrl* screen = screenctrl::instance();
	graphical_menu menu(screen->getbufferw() / 2, screen->getbufferh() - 7, 0);
	menu.setalign(1, 1);
	return menu.operate("ACTION", "Try again\nExit\n");
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
		cout << "Input current password: ";
		asteriskEncode(tmp1);
		if (tmp1 != Password) {
			outputbox.display("The password is incorrect.");
			screenctrl* screen = screenctrl::instance();
			graphical_menu menu(screen->getbufferw() / 2, screen->getbufferh() - 7, 0);
			menu.setalign(1, 1);
			choice = menu.operate("ACTION", "Try again\nBack");
			if (choice)
				return;
		}
		else {
			cout << "Input new password: ";
			asteriskEncode(tmp1);
			cout << "Input new password again: ";
			asteriskEncode(tmp2);
			if (tmp1 != tmp2) {
				outputbox.display("Passwords do not match!");
				screenctrl* screen = screenctrl::instance();
				graphical_menu menu(screen->getbufferw() / 2, screen->getbufferh() - 7, 0);
				menu.setalign(1, 1);
				choice = mainmenu.operate("ACTION", "Try again\nBack");
				if (choice)
					return;
				else {
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
	outputbox.display("Your password is changed successfully.");
}

void Account::StaffLogin(int choice) {
	Staff admin(*this);
	while (choice != 4) {		
		outputbox.display("WELCOME, STAFF " + capitalize_name(admin.staff_name()));
		choice = logged();
		if (choice != 1)
			mainmenu.setpos(OFX, OFY);
		if (choice == 1)
			admin.section();
		else if (choice == 2)
			admin.view_profile();
		else if (choice == 3)
			changepsw();
	}
}

void Account::EmployeeLogin(int choice) {
	Employee client(*this);
	client.loadEmplData(*this);
	while (choice != 4) {
		outputbox.display("WELCOME, " + capitalize_name(client.employee_name()));
		choice = logged();
		if (choice != 1)
			mainmenu.setpos(OFX, OFY);
		if (choice == 1)
			client.EmployeeMenu();
		else if (choice == 2)
			client.View_Infor_Empl();
		else if (choice == 3)
			changepsw();
	}
}

string capitalize_name(string name) {
	transform(name.begin(), name.end(), name.begin(), toupper);
	return name;
}