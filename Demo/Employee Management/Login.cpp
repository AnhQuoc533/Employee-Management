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
			choice = incorrect_psw();
			if (choice == 0)
				return 0;
			system("cls");
		}
		system("cls");
		if (!A.get_role()) {
			A.StaffLogin(choice);
		}
		else {
			//A.EmployeeLogin(choice);
		}
		system("cls");
	}
}