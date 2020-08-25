#include"Employee_Management.h"

Infor::Infor()
{
	No = 0;
	Date aDate(1900, 1, 1);
	DoB = aDate;
	ID = 0;
	Name = "Unkown";
	Phone= "Unkown";
	Address= "Unkown";
}

void Infor::LoadInforfrom(ifstream& fload)
{
	string temp;
	int tempd = 0, tempm = 0, tempy = 0;
	getline(fload, temp, ',');
	setNo(stoi(temp));
	getline(fload, temp, ',');
	setID(stoi(temp));
	getline(fload, temp, ',');
	setName(temp);
	getline(fload, temp, ',');
	setGender(temp[0]);
	getline(fload, temp, ',');
	Date tempDate;
	tempDate.stoDate(temp);
	setDoB(tempDate);
	getline(fload, temp, ',');
	setPhone(temp);
	getline(fload, temp);
	setAddress(temp);
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
			cout << "Invalid input. Please input again." << endl << endl;
		}
	} while (ID <= 0);
	cin.ignore(1);
	cout << "Input the name: ";
	getline(cin, Name);
	do
	{
		cout << "Input the gender: ";
		Gender = getchar();
		if (Gender != 'M' && Gender != 'F')
		{
			cout << "Invalid gender. Please input again." << endl << endl;
		}
	} while (Gender != 'M' && Gender != 'F');
	cout << "Input date of birth:" << endl;
	cin >> DoB;
	cin.ignore(1);
	cout << "Input phone number: ";
	getline(cin, Phone);
	cout << "Input address: ";
	getline(cin, Address);
}

void Infor::OutputInfor()
{
	cout << "No: " << No << endl;
	cout << "ID: " << ID << endl;
	cout << "Name: " << Name << endl;
	cout << "Gender: " << Gender << endl;
	cout << "Date of birth: " << DoB << endl;
	cout << "Phone: " << Phone << endl;
	cout << "Address: " << Address << endl;
}

void Infor::EditInfor()
{
	int choice = -1;
	do
	{
		cout << endl << "Which infor of this employee do you want to edit?" << endl;
		cout << "Enter 0 to cancel." << endl;
		cout << "Enter 1 to edit name." << endl;
		cout << "Enter 2 to edit gender." << endl;
		cout << "Enter 3 to edit date of birth." << endl;
		cout << "Enter 4 to edit phone." << endl;
		cout << "Enter 5 to edit address." << endl;
		cout << "Your choice: ";
		cin >> choice;
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
		cout << endl;
		switch (choice)
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
			cin.ignore(1);
			cout << "Editing the gender of the employee." << endl;
			cout << "Input new gender: ";
			Gender = getchar();
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
			cout << "Editing the phone of the employee." << endl;
			cout << "Input the new phone for this employee: ";
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
		cout << "Enter 1 to continue or any key to exit: ";
		cin >> choice;
		if (cin.fail() || choice != 1)
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(2000, '\n');
			}
			choice = 0;
		}
	} while (choice != 0);
}