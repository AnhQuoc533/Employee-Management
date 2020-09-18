#include "Employee_Management.h"
#include "Login.h"
screenctrl* screenctrl::inst = NULL;
SingletonDestroyer screenctrl::destroyer;

int main() {
	screenctrl* screen = screenctrl::instance();
	screen->init(WIDTH, HEIGHT);
	mainmenu.setpos(OFX, OFY);
	graphical_loader loader(1, screen->getbufferh() / 2, screen->getbufferw() - 6, "Load");
	outputbox.init(1, screen->getbufferh() - 4, screen->getbufferw() - 1, 4);
	loader.load(10);

	int choice = -1;
	while (true) {
		if (welcome())
			return 0;
		Account A;
		while (!A.login()) {
			choice = incorrect_psw();
			if (choice)
				return 0;
		}
		system("cls");
		if (!A.get_role())
			A.StaffLogin(choice);
		else
			A.EmployeeLogin(choice);
		system("cls");
	}
}