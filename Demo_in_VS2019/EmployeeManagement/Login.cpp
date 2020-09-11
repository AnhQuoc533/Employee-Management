#include "Employee_Management.h"
#include "Login.h"
screenctrl* screenctrl::inst = NULL;

int main() {
	screenctrl* screen = screenctrl::instance();
	screen->init(WIDTH, HEIGHT);
	
	mainmenu.setpos(OFX, OFY);
	
	graphical_loader loader(1, screen->getbufferh()/2, screen->getbufferw()-6, "Load");
	loader.load(10);
	
	outputbox.init(1, screen->getbufferh() - 4, screen->getbufferw()-1, 4);
	outputbox.display("Welcome");

	//loader.reset(2, screen->getbufferh() - 5, 20);
	//loader.load(50);

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