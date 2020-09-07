#include"Employee_Management.h"

void Infor::LoadInforfrom(ifstream& fload)
{
	string temp;
	int tempd = 0, tempm = 0, tempy = 0;
	getline(fload, temp, ',');
	ID = stoi(temp);
	ACC.Username = temp;
	getline(fload, temp, ',');
	ACC.Password = temp;
	getline(fload, temp, ',');
	Name = temp;
	getline(fload, temp, ',');
	Gender = temp[0];
	getline(fload, temp, ',');
	Date tempDate;
	tempDate.stoDate(temp);
	DoB = tempDate;
	getline(fload, temp, ',');
	Phone = temp;
	getline(fload, temp);
	Address = temp;
}

void Infor::InputInfor()
{
	do
	{
		cout << "Input the ID: ";
		cin >> ID;
		if (cin.fail() || ID <= 0)
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(2000, '\n');
				ID = 0;
			}
			outputbox.display("Invalid input. Please input again." ) ;
		}
	} while (ID <= 0);
	cin.ignore(1);
	cout << "Input the name: ";
	getline(cin, Name);
	graphical_menu genmenu;
	genmenu.setclear(0);
	int choice = genmenu.operate("Gender", "Male\nFemale\n");
	if (choice == 0) Gender = 'M'; else Gender = 'F';
	//do
	//{
	//	/*cout << "Input the gender (please input m or M for Male and f or F for female): ";
	//	Gender = getchar();
	//	if (Gender != 'M' && Gender != 'F' && Gender != 'm' && Gender != 'f')
	//	{
	//		cout << "Invalid gender. Please input again." << endl << endl;
	//		cin.ignore(1);
	//	}*/
	//} while (Gender != 'M' && Gender != 'F' && Gender != 'm' && Gender != 'f');
	cout << "Input date of birth:" << endl;
	cin >> DoB;
	cin.ignore(1);
	cout << "Input phone number: ";
	getline(cin, Phone);
	cout << "Input address: ";
	getline(cin, Address);
	ACC.Username = to_string(ID);
	ACC.Password = DoB.toStr();
}

void Infor::OutputInfor()
{
	cout << "ID: " << ID << endl;
	cout << "Name: " << Name << endl;
	cout << "Gender: ";
	if (Gender == 'M' || Gender == 'm')
	{
		cout << "Male" << endl;
	}
	if (Gender == 'F' || Gender == 'f')
	{
		cout << "Female" << endl;
	}
	cout << "Date of birth: " << DoB << endl;
	cout << "Phone: " << Phone << endl;
	cout << "Address: " << Address << endl;
}

void Infor::EditInfor()
{
	int choice = -1;
	do
	{
		cout << "Which infor of this employee do you want to edit?" << endl;
		graphical_menu menu;
		choice = menu.operate("Field", "Name\nGender\nDate of birth\nPhone number\nAddress\n");
		/*cout << "Enter 0 to cancel." << endl;
		cout << "Enter 1 to edit name." << endl;
		cout << "Enter 2 to edit gender." << endl;
		cout << "Enter 3 to edit date of birth." << endl;
		cout << "Enter 4 to edit phone." << endl;
		cout << "Enter 5 to edit address." << endl;
		cout << "Your choice: ";
		cin >> choice;
		system("CLS");
		if (cin.fail() || choice < 0)
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(2000, '\n');
				choice = -1;
			}
			cout << "Invalid choice. Please choose again." << endl << endl;
		}
		cout << endl;*/
		switch (choice+1)
		{
		case 0:
		{
			cin.ignore(1);
			cout << "Editing is canceled." << endl;
			break;
		}
		case 1:
		{
			cout << "Editing the name of the employee." << endl;
			cout << "Input the new name for this employee: ";
			cin.ignore(1);
			getline(cin, Name);
			break;
		}
		case 2:
		{
			//cin.ignore(1);
			cout << "Editing the gender of the employee." << endl;
			graphical_menu menu;
			menu.setclear(0);
			int choice = menu.operate("Gender", "Male\nFemale\n");
			if (choice == 0) Gender = 'M'; else Gender = 'F';
			/*cout << "Input new gender: ";
			Gender = getchar();*/
			break;
		}
		case 3:
		{
			cout << "Editing the date of birth of the employee." << endl;
			cout << "Input the new date of birth for this employee:" << endl;
			cin >> DoB;
			break;
		}
		case 4:
		{
			cout << "Editing the phonenumber of the employee." << endl;
			cout << "Input the new phonenumber for this employee: ";
			cin.ignore(1);
			getline(cin, Phone);
			break;
		}
		case 5:
		{
			cout << "Editing the address of the employee." << endl;
			cout << "Input the new address for this employee: ";
			cin.ignore(1);
			getline(cin, Address);
			break;
		}
		default:
		{
			cout << "Invalid choice." << endl;
			break;
		}
		}
		//if (choice != 0)
		{
			cout << "Do you still want to edit this employee?" << endl;
			graphical_menu yesno;
			choice = yesno.operate("Confirmation", "Yes\nNo\n");
			/*cout << "Enter 1 to continue or any key to exit: ";
			cin >> choice;
			if (cin.fail() || choice != 1)
			{
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(2000, '\n');
				}
				choice = 0;
			}*/
		}
		//system("CLS");
	} while (choice == 0);
}