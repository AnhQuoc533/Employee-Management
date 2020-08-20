#include"Employee_Management.h"

Staff::Staff()
{
	Infor anInfor;
	StInfor = anInfor;
}

void Staff::ImportListEmpfromCsv()
{
	ifstream fload;
	string filename;
	string temp;
	Employee anEmpl;
	int tempd = 0, tempm = 0, tempy = 0;
	cout << "Input the name of the csv file: ";
	getline(cin, filename);
	fload.open(filename);
	if (!fload.is_open())
	{
		cout << "Cannot find the file " << filename << "." << endl;
		cout << "Maybe it was deleted or changed the location." << endl;
		return;
	}
	else
	{
		cout << "Openned file " << filename << " successed." << endl;
		cout << "Starting load its data to the program...." << endl;
		while (getline(fload, temp, ','))
		{
			anEmpl.setNo(stoi(temp));
			getline(fload, temp, ',');
			anEmpl.setID(stoi(temp));
			getline(fload, temp, ',');
			anEmpl.setName(temp);
			getline(fload, temp, ',');
			anEmpl.setGender(temp[0]);
			getline(fload, temp, '/');
			tempd = stoi(temp);
			getline(fload, temp, '/');
			tempm = stoi(temp);
			getline(fload, temp, ',');
			tempy = stoi(temp);
			Date tempDate(tempy, tempm, tempd);
			anEmpl.setDoB(tempDate);
			getline(fload, temp, ',');
			anEmpl.setPhone(temp);
			getline(fload, temp);
			anEmpl.setAddress(temp);
			ListEmpl.push_back(anEmpl);
		}
		cout << endl << "Finished importing " << filename << "." << endl;
		cout << "Closing the file...." << endl;
		fload.close();
		cout << "The file " << filename << " was closed successedfully." << endl;
	}
}

void Staff::Add_an_Empl_Manually()
{
	cout << "Start adding...." << endl;
	int choice = 0, n = ListEmpl.size();;
	Employee anEmpl;
	anEmpl.inputEmpl();
	do
	{
		for (int i = 0; i < n; i++)
		{
			if (ListEmpl[i].getID() == anEmpl.getID())
			{
				cout << "The employee with the ID " << anEmpl.getID() << "is already existed." << endl;
				cout << "Here is his/her information:" << endl;
				ListEmpl[i].outputEmpl();
				cout << "Enter 1 to input the ID again or any key to cancel the addition: ";
				cin >> choice;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(2000, '\n');
					choice = -1;
				}
				break;
			}
		}
		if (choice == 1)
		{
			int id;
			do
			{
				cout << "Input the ID: ";
				cin >> id;
				if (cin.fail() || id <= 0)
				{
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(2000, '\n');
						id = 0;
					}
					cout << "Invalid input. Please input again." << endl << endl;
				}
			} while (id <= 0);
			anEmpl.setID(id);
		}
		else
		{
			cout << "The addition was canceled." << endl;
			return;
		}
	} while (choice == 1);
	anEmpl.setNo(ListEmpl.size() + 1);
	ListEmpl.push_back(anEmpl);
}

void Staff::Edit_Infor_of_an_Empl()
{
	cout << "Start editing...." << endl;
	int id;
	cout << "Input the ID of the employee who you want to edit his/her information: ";
	cin >> id;
	if (cin.fail() || id <= 0)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(2000, '\n');
			id = 0;
		}
		cout << "Invalid ID." << endl;
		cout << "The editing will be canceled." << endl;
		return;
	}
	int n = ListEmpl.size();
	int index = -1;
	for (int i = 0; i < n; i++)
	{
		if (id == ListEmpl[i].getID())
		{
			index = i;
			break;
		}
	}
	if (index == -1)
	{
		cout << "There is no employee that has the ID " << id << "in this list." << endl;
		cout << "The editing will be canceled." << endl;
		return;
	}
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
			cout << "Editing is canceled." << endl;
			break;
		}
		case 1:
		{
			cout << "Editing the name of the employee." << endl;
			string name;
			cout << "Input the new name for this employee: ";
			cin.ignore(1);
			getline(cin, name);
			ListEmpl[index].setName(name);
			break;
		}
		case 2:
		{
			cin.ignore(1);
			char gender;
			cout << "Editing the gender of the employee." << endl;
			cout << "Input new gender: ";
			gender = getchar();
			ListEmpl[index].setGender(gender);
			break;
		}
		case 3:
		{
			cout << "Editing the date of birth of the employee." << endl;
			Date aDate;
			cout << "Input the new date of birth for this employee:" << endl;
			cin >> aDate;
			ListEmpl[index].setDoB(aDate);
			break;
		}
		case 4:
		{
			cout << "Editing the phone of the employee." << endl;
			string phone;
			cout << "Input the new phone for this employee: ";
			cin.ignore(1);
			getline(cin, phone);
			ListEmpl[index].setPhone(phone);
			break;
		}
		case 5:
		{
			cout << "Editing the address of the employee." << endl;
			string address;
			cout << "Input the new address for this employee: ";
			cin.ignore(1);
			getline(cin, address);
			ListEmpl[index].setAddress(address);
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
	cout << "The employee after edited:" << endl;
	ListEmpl[index].outputEmpl();
	cout << endl;
}

void Staff::View_list_of_Empl()
{
	int n = ListEmpl.size();
	for (int i = 0; i < n; i++)
	{
		ListEmpl[i].outputEmpl();
		cout << endl;
	}
}

void Staff::View_Infor_of_an_Empl()
{
	int id;
	cout << "Input the ID of the employee who you want to view his/her information: ";
	cin >> id;
	if (cin.fail() || id <= 0)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(2000, '\n');
			id = 0;
		}
		cout << "Invalid ID." << endl;
		cout << "The viewing will be canceled." << endl;
		return;
	}
	int n = ListEmpl.size();
	int index = -1;
	for (int i = 0; i < n; i++)
	{
		if (id == ListEmpl[i].getID())
		{
			index = i;
			break;
		}
	}
	if (index == -1)
	{
		cout << "There is no employee that has the ID " << id << "in this list." << endl;
		cout << "The viewing will be canceled." << endl;
		return;
	}
	cout << "The information of this employee is:" << endl;
	ListEmpl[index].outputEmpl();
}

void Staff::StaffMenu()
{
	//Test import xong comment lai nhu luc dau r test tiep ham add, xong r tu do test luon cac ham khac
	//Gop y gi nhan lien qua Mess giup^^.
	ImportListEmpfromCsv();
	cout << endl;
	View_list_of_Empl();
}