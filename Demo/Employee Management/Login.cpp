#include "Employee_Management.h"
#include "Login.h"
screenctrl* screenctrl::inst = NULL;

int main() {
	int choice = -1;
	while (true) {
		if (welcome() != 1)
			return 0;
		system("cls");
		Account A;
		while (!A.login()) {
			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(h, 12);
			cout << "\t\t\t\t\t\t\t\t" << "  The username or password is incorrect.\n";
			SetConsoleTextAttribute(h, 10);
			cout << "\t\t\t\t\t\t\t\t" << "\t1. Try again\t";
			SetConsoleTextAttribute(h, 12);
			cout << "0.Exit\n";
			SetConsoleTextAttribute(h, 15);
			cout << " \t\t\t\t\t\t\t\t  Choose your action: ";
			cin >> choice;
			if (choice == 0)
				return 0;
			system("cls");
		}
		system("cls");
		if (!A.get_role()) {
			A.StaffLogin(choice);
		}
		else if (A.get_role()) {
			A.EmployeeLogin(choice);
		}
		system("cls");
	}
}