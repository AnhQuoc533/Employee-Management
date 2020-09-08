#include "Employee_Management.h"

void Infor::LoadInforfrom(ifstream& fload)
{
	string temp;
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
	DoB.stoDate(temp);
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
		cout << "Do you still want to edit this employee?" << endl;
		graphical_menu yesno;
		choice = yesno.operate("Confirmation", "Yes\nNo\n");
	} while (choice == 0);
}