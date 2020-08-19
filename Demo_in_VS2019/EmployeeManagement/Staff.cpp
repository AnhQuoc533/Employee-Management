#include"Employee_Management.h"

Staff::Staff()
{
	Infor anInfor;
	StInfor = anInfor;
}

void Staff::ImportListEmpfromCsv(ifstream& fload)
{
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
		cout << "Openned file " << filename << "successed." << endl;
		cout << "Starting load its data to the program...." << endl;
		while (getline(fload, temp, ','))
		{
			anEmpl.setID(stoi(temp));
			getline(fload, temp, ',');
			anEmpl.setName(temp);
			getline(fload, temp, '/');
			tempd = stoi(temp);
			getline(fload, temp, '/');
			tempm = stoi(temp);
			getline(fload, temp, ',');
			tempy = stoi(temp);
			Date tempDate(tempy, tempm, tempd);
			anEmpl.setDoB(tempDate);
			getline(fload, temp);
			anEmpl.setSalary(stod(temp));
			ListEmpl.push_back(anEmpl);
			
		}
		fload.close();
	}
}

void Staff::input_List_of_Empl_Manually()
{
	int n;
	do
	{
		cout << "Input the number of the employee: ";
		cin >> n;
		if (cin.fail() || n < 0)
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(2000, '\n');
				n = -1;
			}
			cout << "Invalid input. Please input again." << endl << endl;
		}
	} while (n < 0);
	Employee anEmpl;
	for (int i = 0; i < n; i++)
	{
		anEmpl.inputEmpl();
		ListEmpl.push_back(anEmpl);
	}
}

void Staff::Edit_Infor_of_an_Empl()
{
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
		cout << "Which infor of this employee do you want to edit?" << endl;
		cout << "Enter 0 to cancel." << endl;
		cout << "Enter 1 to edit name." << endl;
		cout << "Enter 2 to edit date of birth" << endl;
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
			cout << "Editing the date of birth of the employee." << endl;
			Date aDate;
			cout << "Input new date of birth for this employee:" << endl;
			cin >> aDate;
			ListEmpl[index].setDoB(aDate);
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
	cout << "Editing is canceled." << endl;
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

void Staff::View_check_in_of_an_employee()
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

}