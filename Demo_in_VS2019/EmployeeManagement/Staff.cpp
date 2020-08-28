#include"Employee_Management.h"

Staff::Staff()
{
	Infor anInfor;
	StInfor = anInfor;
	employeeRecords = new Record;
}

void Staff::SaveInfortoTextfile(int& checkifBeChanged)
{
	ifstream fload;
	ofstream fsave;
	string namefile;
	int choice = 0;
	cout << "Input the name of the file (please do not put the type of file): ";
	getline(cin, namefile);
	namefile.append(".txt");
	fload.open(namefile);
	if (fload.is_open())
	{
		fload.close();
		cout << "The file " << namefile << " has already existed." << endl;
		cout << "Do you want to overwrite it?" << endl;
		cout << "1.Yes\n2.No (Cancel save)\n";
		do
		{
			cout << "Your choice: ";
			cin >> choice;
			if (cin.fail() || choice < 1 || choice > 2)
			{
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(2000, '\n');
					choice = 0;
				}
				cout << "Invalid choice. Please choose again" << endl << endl;
			}
		} while (choice < 1 || choice>2);
		if (choice == 2)
		{
			cout << "The file was not saved." << endl;
			return;
		}
	}
	fsave.open(namefile);
	if (!fsave.is_open())
	{
		cout << "Cannot create file." << endl;
		cout << "Canceled saving." << endl;
		return;
	}
	else
	{
		cout << "Saving data to file " << namefile << "...." << endl;
		cout << "Do not shutdown the program while we are saving for you." << endl;
		int n = ListEmpl.size();
		for (int i = 0; i < n; i++)
		{
			fsave << ListEmpl[i].EInfor.getNo() << ",";
			fsave << ListEmpl[i].EInfor.getID() << ",";
			fsave << ListEmpl[i].EInfor.getName() << ",";
			fsave << ListEmpl[i].EInfor.getGender() << ",";
			fsave << ListEmpl[i].EInfor.getDoB() << ",";
			fsave << ListEmpl[i].EInfor.getPhone() << ",";
			fsave << ListEmpl[i].EInfor.getAddress();
			if (i < n - 1)
			{
				fsave << endl;
			}
		}
		cout << "Finished saving data to file " << namefile << " successed." << endl;
		cout << "Closing the file...." << endl;
		fsave.close();
		cout << "The file " << namefile << " was closed successfully." << endl;
		checkifBeChanged = 0;
	}
}

void Staff::LoadfromTextfile()
{
	ifstream fload;
	string namefile;
	Employee anEmpl;
	cout << "Input the name of the file you want to load its data (do not input the type of the file): ";
	getline(cin, namefile);
	namefile.append(".txt");
	fload.open(namefile);
	if (!fload.is_open())
	{
		cout << "Cannot find the file " << namefile << "." << endl;
		cout << "Maybe it was deleted or changed the location." << endl;
		return;
	}
	else
	{
		cout << "Openned file " << namefile << " successed." << endl;
		cout << "Starting load its data to the program...." << endl;
		while (!fload.eof())
		{
			anEmpl.EInfor.LoadInforfrom(fload);
			ListEmpl.push_back(anEmpl);
		}
		cout << endl << "Finished loading " << namefile << "." << endl;
		cout << "Closing the file...." << endl;
		fload.close();
		cout << "The file " << namefile << " was closed successfully." << endl;
	}
}

void Staff::ImportListEmpfromCsv()
{
	ifstream fload;
	string namefile;
	Employee anEmpl;
	cout << "Input the name of the csv file (do not input the type of the file): ";
	getline(cin, namefile);
	namefile.append(".csv");
	fload.open(namefile);
	if (!fload.is_open())
	{
		cout << "Cannot find the file " << namefile << "." << endl;
		cout << "Maybe it was deleted or changed the location." << endl;
		return;
	}
	else
	{
		cout << "Openned file " << namefile << " successed." << endl;
		cout << "Starting load its data to the program...." << endl;
		while (!fload.eof())
		{
			anEmpl.EInfor.LoadInforfrom(fload);
			anEmpl.EInfor.setUS(to_string(anEmpl.EInfor.getID()));
			anEmpl.EInfor.setPASS(anEmpl.EInfor.getDoB().toStr());
			ListEmpl.push_back(anEmpl);
		}
		cout << endl << "Finished importing " << namefile << "." << endl;
		cout << "Closing the file...." << endl;
		fload.close();
		cout << "The file " << namefile << " was closed successfully." << endl;
		cout << "Your data will be saved to a text file now." << endl << endl;
		int temp = 1;
		SaveInfortoTextfile(temp);
	}
}

int Staff::findEmplWithID(int id)
{
	if (id > 0)
	{
		int n = ListEmpl.size();
		for (int i = 0; i < n; i++)
		{
			if (ListEmpl[i].EInfor.getID() == id)
			{
				return i;
			}
		}
	}
	return -1;
}

void Staff::Add_an_Empl_Manually(int& checkifBeChanged)
{
	int choice = 0, n = ListEmpl.size();;
	Employee anEmpl;
	anEmpl.EInfor.InputInfor();
	do
	{
		int index = findEmplWithID(anEmpl.EInfor.getID());
		if (index != -1)
		{
			cout << endl << "ERROR: The employee with the ID " << anEmpl.EInfor.getID() << "is already existed." << endl;
			cout << "Here is his/her information:" << endl;
			ListEmpl[index].View_Infor_Empl();
			cout << "Enter 1 to input the ID again or any key to cancel the addition: ";
			cin >> choice;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(2000, '\n');
				choice = -1;
			}
		}
		else break;
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
			anEmpl.EInfor.setID(id);
		}
		else
		{
			cout << "The addition was canceled." << endl;
			return;
		}
	} while (choice == 1);
	anEmpl.EInfor.setNo(ListEmpl.size() + 1);
	anEmpl.EInfor.setUS(to_string(anEmpl.EInfor.getID()));
	anEmpl.EInfor.setPASS(anEmpl.EInfor.getDoB().toStr());
	ListEmpl.push_back(anEmpl);
	checkifBeChanged = 1;
}

void Staff::Create_List_Empl_Manually(int& checkifBeChanged)
{
	int n;
	checkifBeChanged = 0;
	do
	{
		cout << "Input the number of employees you would like to add in this new list: ";
		cin >> n;
		if (cin.fail() || n < 0)
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(2000, '\n');
				n = -1;
			}
			cout << "Invalid input. Please input again." << endl;
		}
	} while (n < 0);
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "Input information of employee number " << i + 1 << ":" << endl;
		Add_an_Empl_Manually(checkifBeChanged);
		cout << endl;
	}
	cout << "The addition is completed." << endl;
}

void Staff::Edit_Infor_of_an_Empl(int& checkifBeChanged)
{
	int id;
	cout << "Please input the ID of the employee who you want to edit his/her information first: ";
	cin >> id;
	if (cin.fail() || id <= 0)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(2000, '\n');
		}
		id = 0;
		cout << "Invalid ID." << endl;
		cout << "The editing will be canceled." << endl;
		return;
	}
	int index = findEmplWithID(id);
	if (index == -1)
	{
		cout << "There is no employee that has the ID " << id << "in this list." << endl;
		cout << "The editing will be canceled." << endl;
		cin.ignore(1);
		return;
	}
	system("CLS");
	cout << "Start editing...." << endl;
	ListEmpl[index].EInfor.EditInfor(checkifBeChanged);
	cout << "The employee after edited:" << endl;
	ListEmpl[index].View_Infor_Empl();
	cout << endl;
}

void Staff::Remove_an_Empl(int& checkifBeChanged)
{
	int id;
	cout << "Please input the ID of the employee who you want to remove his/her information first: ";
	cin >> id;
	if (cin.fail() || id <= 0)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(2000, '\n');
		}
		id = 0;
		cout << "Invalid ID." << endl;
		cout << "The removing will be canceled." << endl;
		return;
	}
	int index = findEmplWithID(id);
	if (index == -1)
	{
		cout << "There is no employee that has the ID " << id << "in this list." << endl;
		cout << "The removing will be canceled." << endl;
		cin.ignore(1);
		return;
	}
	int idx = employeeRecords->getIndex(id);
	if (idx == -1)
	{
		cout << "There is no employee that has the ID " << id << " in records database.\n";
		cout << "You should recheck the data." << endl;
		return;
	}
	cout << "Start removing...." << endl;
	int n = ListEmpl.size();
	for (int i = index + 1; i < n; i++)
	{
		ListEmpl[i].EInfor.setNo(ListEmpl[i].EInfor.getNo() - 1);
	}
	ListEmpl.erase(ListEmpl.begin() + index);
	employeeRecords->remove(idx);
	checkifBeChanged = 1;
}

void Staff::View_list_of_Empl()
{
	string ID, No;
	int space1 = 0, space2 = 0, space3 = 0;
	cout << setw(7) << "No" << setw(17) << "ID" << setw(27) << "Name" << endl;
	int n = ListEmpl.size();
	for (int i = 0; i < n; i++)
	{
		ID.clear();
		No.clear();
		if (ListEmpl[i].EInfor.getNo() < 10)
		{
			No = "0";
		}
		No.append(to_string(ListEmpl[i].EInfor.getNo()));
		if (ListEmpl[i].EInfor.getID() < 10)
		{
			ID = "0";
		}
		ID.append(to_string(ListEmpl[i].EInfor.getID()));
		space1 = 5 + No.length();
		space2 = 15 - (No.length() - 2) + ID.length();
		space3 = 23 - (ID.length() - 2) + ListEmpl[i].EInfor.getName().length();
		cout << setw(space1) << No << setw(space2) << ID << setw(space3) << ListEmpl[i].EInfor.getName() << endl;
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
	int index = findEmplWithID(id);
	if (index == -1)
	{
		cout << "There is no employee that has the ID " << id << " in your list." << endl;
		cout << "The viewing will be canceled." << endl;
		cin.ignore(1);
		return;
	}
	cout << "The information of this employee is:" << endl;
	ListEmpl[index].View_Infor_Empl();
}

void Staff::Reset_password_for_empl()
{
	int n = ListEmpl.size(), id;
	cout << "Input the ID of the employee who you want to reset his/her password: ";
	cin >> id;
	if (cin.fail() || id <= 0)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(2000, '\n');
			id = 0;
		}
		cout << "Invalid ID. This functionality will be canceled." << endl;
		return;
	}
	int index = findEmplWithID(id);
	if (index == -1)
	{
		cout << "There is no employee that has the ID " << id << " in your list." << endl;
		cout << "This functionality will be canceled." << endl;
		cin.ignore(1);
		return;
	}
	cout << "Resetting password...." << endl;
	ListEmpl[index].EInfor.setPASS(ListEmpl[index].EInfor.getDoB().toStr());
	cout << "Successed." << endl;
	cout << "The password of this employee's account right now is his/her date of birth." << endl;
}

void Staff::View_Profile()
{
	StInfor.OutputInfor();
}

void Staff::Manage_Employee_Menu()
{
	int choice, choice2 = -1, choice3 = 0, checkifBeChanged = 0;
	do
	{
		cout << "******************************MANAGE EMPLOYEE MENU******************************" << endl;
		cout << "0.Exit\n1.Import new list of employee from .csv file\n2.Load existed list of employee from your device\n3.Create new list of employee manually\n";
		cout << "Your choice: ";
		cin >> choice;
		if (choice != 0)
		{
			cin.ignore(1);
		}
		system("CLS");
		switch (choice)
		{
		case 0:
		{
			cout << "Returning to *Staff menu*....\n";
			break;
		}
		case 1:
		{
			ImportListEmpfromCsv();
			break;
		}
		case 2:
		{
			LoadfromTextfile();
			break;
		}
		case 3:
		{
			Create_List_Empl_Manually(checkifBeChanged);
			break;
		}
		default:
		{
			cout << "Invalid choice." << endl;
			break;
		}
		}
		system("pause");
		system("CLS");
		if (choice == 0)
		{
			return;
		}
		int n = ListEmpl.size();
		if (n == 0 && choice > 0 && choice <= 3)
		{
			cout << "There is nothing do to manage here." << endl;
			choice2 = 0;
		}
		else
		{
			cout << "Here is your list:" << endl;
			View_list_of_Empl();
			system("pause");
			system("CLS");
			choice2 = 1;
		}
		do
		{
			if (choice2 > 0)
			{
				do
				{
					cout << "What do you want to do next:" << endl;
					cout << "0. Exit " << endl;
					cout << "1. Add an employee to the list manually." << endl;
					cout << "2. Edit an employee's information." << endl;
					cout << "3. Remove an employee from the list." << endl;
					cout << "4. View list of employees." << endl;
					cout << "5. View information of an employee." << endl;
					cout << "6. Reset password for an employee." << endl;
					cout << "7. Save." << endl;
					cout << "Your choice: ";
					cin >> choice2;
					system("CLS");
					if (cin.fail() || choice2 < 0 && choice2 > 6)
					{
						if (cin.fail())
						{
							cin.clear();
							cin.ignore(2000, '\n');
							choice2 = -1;
						}
						cout << "Invalid choice. Please chosse again." << endl;
					}
				} while (choice < 0 || choice > 6);
				switch (choice2)
				{
				case 0:
				{
					choice3 = 0;
					if (checkifBeChanged == 1)
					{		
						cout << "You haven't saved your work. Do you want to save it?" << endl;
						cout << "NOTE: If you don't save, your work will be clear after you return previous menu." << endl;
						cout << "Input 1 to cancel exit and please choose option 7 to save";
						cout << " or any key to exit without saving." << endl;
						cout << "Your choice: ";
						cin >> choice3;
						if (cin.fail() || choice3 != 1)
						{
							if (cin.fail())
							{
								cin.clear();
								cin.ignore(2000, '\n');
							}
							choice3 = 0;
							system("CLS");
						}
						if (choice3 == 1)
						{
							choice2 = 1;
						}
					}
					if (choice3 != 1)
					{
						cout << "Returning to previous menu." << endl;
					}
					break;
				}
				case 1:
				{
					cout << "Start adding an employee to the list manually." << endl;
					Add_an_Empl_Manually(checkifBeChanged);
					break;
				}
				case 2:
				{
					cout << "Start editing an employee's information." << endl;
					Edit_Infor_of_an_Empl(checkifBeChanged);
					break;
				}
				case 3:
				{
					cout << "Start removing an employee from the list." << endl;
					Remove_an_Empl(checkifBeChanged);
					break;
				}
				case 4:
				{
					cout << "Your list of employees:" << endl;
					View_list_of_Empl();
					break;
				}
				case 5:
				{
					View_Infor_of_an_Empl();
					break;
				}
				case 6:
				{
					cout << "Start reseting the password for your employee." << endl;
					break;
				}
				case 7:
				{
					cin.ignore(1);
					cout << "Start saving your data." << endl;
					SaveInfortoTextfile(checkifBeChanged);
					break;
				}
				}
			}
			system("pause");
			system("CLS");
		} while (choice2 > 0);
		ListEmpl.clear();
	} while (choice != 0);
}

void Staff::StaffMenu()
{
	int choice;
	do
	{
		cout << "Staff menu:\n1.View profile\n2.Change password\n3.Change to manage employee menu\n4.Log out\n";
		cout << "Your choice: ";
		cin >> choice;
		system("CLS");
		switch (choice)
		{
		case 1:
		{
			cout << "Your profile:" << endl;
			break;
		}
		case 2:
		{
			cout << "Start changing your password." << endl;
			break;
		}
		case 3:
		{
			cout << "Changing to manage employee menu...." << endl;
			system("CLS");
			Manage_Employee_Menu();
			break;
		}
		case 4:
		{
			cout << "Logging out...." << endl;
			cout << "Finished logging out." << endl;
			break;
		}
		default:
		{
			cout << "Invalid choice." << endl;
			break;
		}
		}
		if (choice != 3)
		{
			system("pause");
			system("CLS");
		}
	} while (choice != 4);
	//LoadfromTextfile();
	//View_list_of_Empl();
}

void Staff::createRecords()
{
	if (employeeRecords->hasData())
	{
		cout << "There's existing records data of this month. You cannot create new records.\n";
		cout << "Remove records data of this month If you really want to create new records.\n";
		return;
	}
	int n = ListEmpl.size();
	int* arr = new int[n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = ListEmpl[i].EInfor.getID();
	}
	employeeRecords->newBlank(arr, n);
	delete[] arr;
	cout << "A blank record has been created\n";
}

void Staff::editRecords()
{
}

void Staff::removeRecords()
{
	if (employeeRecords->hasData())
	{
		employeeRecords->clearData();
		cout << "Removed records data successfully\n";
	}
	else
	{
		cout << "There's no records data to remove\n";
	}
}

void Staff::importRecords()
{
	ifstream fin;
	string filename;
	cout << "Input the name of the csv file (do not input the type of the file): ";
	getline(cin, filename);
	filename.append(".csv");
	fin.open(filename);
	if (!fin.is_open())
	{
		cout << "Cannot find the file " << filename << ".\n";
		cout << "Cannot import data.\n";
	}
	else
	{
		cout << "Openned file " << filename << " successfully.\n";
		cout << "Starting load its data to the program...\n";
		employeeRecords->import(fin);
		cout << endl << "Finished importing " << filename << ".\n";
	}
	fin.close();
}

void Staff::addRecord()
{
}

void Staff::editRecord()
{
}

void Staff::clearRecordOfAnEmployee()
{
	int ID, index;
	cout << "Input the ID of the employee tat you want to clear record: ";
	cin >> ID;
	index = employeeRecords->getIndex(ID);
	if (index == -1)
	{
		cout << "There is no employee that has the ID " << ID << " in records database.\n";
		cout << "You should recheck the data.\n";
		return;
	}
	employeeRecords->clear(index);
	cout << "Cleared record of an employee\n";
}

void Staff::viewRecords()
{
	Date today;
	int index;
	int n = ListEmpl.size();
	int maxDay = today.Maxdayintmonth();
	cout << "Day" << setw(8);
	for (int i = 1; i <= maxDay; ++i)
	{
		cout << i << setw(3);
	}
	cout << endl;
	for (int i = 0; i < n; ++i)
	{
		index = employeeRecords->getIndex(ListEmpl[i].EInfor.getID());
		if (index == -1)
		{
			cout << "There is no employee that has the ID " << ListEmpl[i].EInfor.getID() << " in records database.\n";
			cout << "You should recheck the data." << endl;
			continue;
		}
		employeeRecords->view(index);
	}
}
