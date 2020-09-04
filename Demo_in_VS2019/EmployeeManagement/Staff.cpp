#include"Employee_Management.h"

Staff::Staff()
{
	Infor anInfor;
	StInfor = anInfor;
	employeeRecords = new Record;
}

void Staff::SaveInfortoTextfile()
{
	ofstream fsave;
	string namefile = "Employee.txt";
	fsave.open(namefile);
	if (!fsave.is_open())
	{
		outputbox.display("Cannot create file.\nCanceled saving");
		return;
	}
	else
	{
		outputbox.display("Saving data to file "+ namefile+"....\n*NOTE:Do not shutdown the program while we are saving for you.*");
		int n = ListEmpl.size();
		for (int i = 0; i < n; i++)
		{
			fsave << ListEmpl[i].EInfor.getID() << ",";
			fsave << ListEmpl[i].EInfor.getPassword() << ",";
			fsave << ListEmpl[i].EInfor.getName() << ",";
			if (ListEmpl[i].EInfor.getGender() == 'M' || ListEmpl[i].EInfor.getGender() == 'm')
			{
				fsave << "M" << ",";
			}
			if (ListEmpl[i].EInfor.getGender() == 'F' || ListEmpl[i].EInfor.getGender() == 'f')
			{
				fsave << "F" << ",";
			}
			fsave << ListEmpl[i].EInfor.getDoB() << ",";
			fsave << ListEmpl[i].EInfor.getPhone() << ",";
			fsave << ListEmpl[i].EInfor.getAddress();
			if (i < n - 1)
			{
				fsave << endl;
			}
		}
		outputbox.display("Finished saving data to file "+ namefile + " successed.\nClosing the file....");
		fsave.close();
		if (!fsave.is_open())
		{
			outputbox.display("The file " + namefile + " was closed successfully.");
		}
		else
		{
			outputbox.display("Failed to close file " + namefile + "." );
		}
	}
}

void Staff::LoadfromTextfile()
{
	ifstream fload;
	string namefile = "Employee.txt";
	Employee anEmpl;
	fload.open(namefile);
	if (!fload.is_open())
	{
		outputbox.display("Cannot find the file " + namefile + ".\nMaybe it was deleted or changed the location.");
		return;
	}
	else
	{
		outputbox.display("Openned file " + namefile + " successed.\nStarting load its data to the program....");
		screenctrl* screen = screenctrl::instance();
		graphical_loader loader(2, screen->getbufferh() - 5, 20, "Load");
		loader.load(30);
		while (!fload.eof())
		{
			anEmpl.EInfor.LoadInforfrom(fload);
			anEmpl.EInfor.setNo(ListEmpl.size() + 1);
			ListEmpl.push_back(anEmpl);
		}
		outputbox.display("Finished loading " + namefile + ".\nClosing the file....");
		fload.close();
		if (!fload.is_open())
		{
			outputbox.display("The file " + namefile + " was closed successfully.");
		}
		else
		{
			outputbox.display("Failed to close file " + namefile + "." );
		}
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
		outputbox.display("Cannot find the file " + namefile + ".\nMaybe it was deleted or changed the location.");
		return;
	}
	else
	{
		outputbox.display("Openned file " + namefile + " successed.\nStarting load its data to the program....");
		screenctrl* screen = screenctrl::instance();
		graphical_loader loader(2, screen->getbufferh() - 5, 20, "Load");
		loader.load(30);
		while (!fload.eof())
		{
			anEmpl.EInfor.LoadInforfrom(fload);
			anEmpl.EInfor.setNo(ListEmpl.size() + 1);
			ListEmpl.push_back(anEmpl);
		}
		outputbox.display("Finished importing " + namefile + ".\nClosing the file....");
		fload.close();
		if (!fload.is_open())
		{
			outputbox.display("The file " + namefile + " was closed successfully.");
		}
		else
		{
			outputbox.display("Failed to close file " + namefile + "." ) ;
		}
		outputbox.display("Your data will be saved to a text file now." );
		SaveInfortoTextfile();
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

void Staff::Add_an_Empl_Manually()
{
	int choice = 0, n = ListEmpl.size();;
	Employee anEmpl;
	anEmpl.EInfor.InputInfor();
	do
	{
		//system("CLS");
		int index = findEmplWithID(anEmpl.EInfor.getID());
		if (index != -1)
		{
			cout << "ERROR: The employee with the ID " << anEmpl.EInfor.getID() << "is already existed." << endl;
			cout << "Here is his/her information:" << endl;
			ListEmpl[index].View_Infor_Empl();
			system("pause");
			system("CLS");
			cout << "Enter 1 to input the ID again or any key to cancel the addition: ";
			cin >> choice;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(2000, '\n');
				choice = -1;
			}
			system("CLS");
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
					outputbox.display("Invalid input. Please input again." );
				}
			} while (id <= 0);
			anEmpl.EInfor.setID(id);
			employeeRecords->newBlank(id);
		}
		else
		{
			outputbox.display("The addition was canceled." );
			return;
		}
	} while (choice == 1);
	anEmpl.EInfor.setNo(ListEmpl.size() + 1);
	anEmpl.EInfor.setUS(to_string(anEmpl.EInfor.getID()));
	anEmpl.EInfor.setPASS(anEmpl.EInfor.getDoB().toStr());
	ListEmpl.push_back(anEmpl);
	outputbox.display("New employee was added successfully." );
}

void Staff::Create_List_Empl_Manually()
{
	int n;
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
		Add_an_Empl_Manually();
		cout << endl;
	}
	outputbox.display("The addition is completed." );
}

void Staff::Edit_Infor_of_an_Empl()
{
	int id, choice = 1;
	do
	{
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
			outputbox.display("The editting will be canceled." ) ;
			return;
		}
		//system("CLS");
		cout << "Are you sure that you want to edit the employee with the ID " << id << "?" << endl;
		graphical_menu yesno;
		yesno.setclear(0);
		choice = yesno.operate("Answer", "Yes\nNo");
		//do
		//{
		//	
		//	/*cout << "Enter 1 to continue or 2 to input the ID again." << endl;
		//	cout << "Your choice: ";*/
		//	//cin >> choice;
		//	/*if (cin.fail() || choice != 1 && choice != 2)
		//	{
		//		if (cin.fail())
		//		{
		//			cin.clear();
		//			cin.ignore(2000, '\n');
		//		}
		//		choice = 0;
		//		cout << "Invalid choice. Please input again.";
		//		system("CLS");
		//	}*/
		//} while (choice == 0);
		//system("CLS");
	} while (choice == 1);
	int index = findEmplWithID(id);
	if (index == -1)
	{
		outputbox.display("There is no employee that has the ID " + to_string(id) + " in this list.\nThe editing will be canceled.");
		cin.ignore(1);
		return;
	}
	//system("CLS");
	outputbox.display("Start editing....");
	ListEmpl[index].EInfor.EditInfor();
	cout << "The employee after edited:" << endl;
	ListEmpl[index].View_Infor_Empl();
	cout << endl;
}

void Staff::Remove_an_Empl()
{
	int id, choice = 1;
	do
	{
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
			outputbox.display("Invalid ID.\nThe removing will be canceled.");
			return;
		}
		//system("CLS");
		cout << "Are you sure that you want to delete the employee with the ID " << id << "?" << endl;
		graphical_menu yesno;
		choice = yesno.operate("Confirmation", "Yes\nNo\n");
		/*do
		{
			cout << "Enter 1 to continue or 2 to input the ID again." << endl;
			cout << "Your choice: ";
			cin >> choice;
			if (cin.fail() || choice != 1 && choice != 2)
			{
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(2000,'\n');
				}
				choice = 0;
				cout << "Invalid choice. Please input again.";
				system("CLS");
			}
		} while (choice == 0);
		system("CLS");*/
	} while (choice != 0);
	int index = findEmplWithID(id);
	if (index == -1)
	{
		outputbox.display("There is no employee that has the ID " + to_string(id) + " in this list.\nThe removing will be canceled." );
		cin.ignore(1);
		return;
	}
	int idx = employeeRecords->getIndex(id);
	if (idx == -1)
	{
		outputbox.display("There is no employee that has the ID " + to_string(id) + " in records database.\nYou should recheck the data.");
	}
	else
		employeeRecords->remove(idx);
	outputbox.display("Start removing....");
	int n = ListEmpl.size();
	for (int i = index + 1; i < n; i++)
	{
		ListEmpl[i].EInfor.setNo(ListEmpl[i].EInfor.getNo() - 1);
	}
	ListEmpl.erase(ListEmpl.begin() + index);
	outputbox.display("Removed Successfully!"); // Thanh added.
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
		outputbox.display("Invalid ID.\nThe viewing will be canceled." );
		return;
	}
	int index = findEmplWithID(id);
	if (index == -1)
	{
		outputbox.display("There is no employee that has the ID " + to_string(id) + " in your list.\nThe viewing will be canceled." ) ;
		cin.ignore(1);
		return;
	}
	cout << "The information of this employee is:" << endl;
	ListEmpl[index].View_Infor_Empl();
}

void Staff::Reset_password_for_empl()
{
	int id, choice = 1;
	do
	{
		cout << "Please input the ID of the employee who you want to reset his/her password first: ";
		cin >> id;
		if (cin.fail() || id <= 0)
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(2000, '\n');
			}
			id = 0;
			outputbox.display("Invalid ID.\nThis functionality will be canceled." ) ;
			return;
		}
		//system("CLS");
		cout << "Are you sure that you want to reset the password of employee with the ID " << id << "?" << endl;
		graphical_menu yesno;
		choice = yesno.operate("Confirmation", "Yes\nNo\n");
		/*do
		{
			cout << "Enter 1 to continue or 2 to input the ID again." << endl;
			cout << "Your choice: ";
			cin >> choice;
			if (cin.fail() || choice != 1 && choice != 2)
			{
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(2000, '\n');
				}
				choice = 0;
				outputbox.display("Invalid choice. Please input again.");
				system("CLS");
			}
		} while (choice == 0);
		system("CLS");*/
	} while (choice != 0);
	int index = findEmplWithID(id);
	if (index == -1)
	{
		outputbox.display("There is no employee that has the ID " + to_string(id) + " in your list.\nThis functionality will be canceled." ) ;
		cin.ignore(1);
		return;
	}
	outputbox.display("Resetting password....");
	ListEmpl[index].EInfor.setPASS(ListEmpl[index].EInfor.getDoB().toStr());
	outputbox.display("Successed.\nThe password of this employee's account right now is his/her date of birth.");
}

void Staff::View_Profile()
{
	StInfor.OutputInfor();
}

void Staff::Manage_Employee_Menu()
{
	int choice, choice2 = -1, choice3 = 0;
	do
	{
		choice = mainmenu.operate("Manage Employee", "Import new list of employee from .csv file\nLoad existed list of employee from your device\nCreate new list of employee manually\nExit");
		/*if (choice != 0)
		{
			cin.ignore(1);
		}*/
		//system("CLS");
		switch (choice+1)
		{
		case 4:
		{
			//cout << "Returning to *Staff menu*....\n";
			mainmenu.clear();
			return;
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
			Create_List_Empl_Manually();
			break;
		}
		default:
		{
			cout << "Invalid choice." << endl;
			break;
		}
		}
		//system("pause");
		//system("CLS");
		/*if (choice == 0)
		{
			return;
		}*/
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
			//system("pause");
			//system("CLS");
			choice2 = 1;
		}
		do
		{
			if (choice2 >= 0)
			{
				do
				{
					mainmenu.autowarp(0);
					choice2 = mainmenu.operate("Manage Employee", "Add an employee to the list manually.\nEdit an employee's information.\nRemove an employee from the list.\nView list of employees.\nView information of an employee.\nReset password for an employee. \nCreate new records of a month. \nRemove records data. \nImport records data from csv file. \nEdit record of an employee. \nView records of all employees. \nClear record of an employee. \nView salary of all employees");
					//system("CLS");
					/*if (cin.fail() || choice2 < 0 && choice2 > 6)
					{
						if (cin.fail())
						{
							cin.clear();
							cin.ignore(2000, '\n');
							choice2 = -1;
						}
						cout << "Invalid choice. Please chosse again." << endl;
					}*/
				} while (choice < 0 || choice > 6); // need changes?
				switch (choice2+1)
				{
				case 99:
				{
					cin.ignore(1);
					cout << "Please save your work before return to the previous menu." << endl;
					SaveInfortoTextfile();
					ListEmpl.clear();
					//system("pause");
					//system("CLS");
					cout << "Returning to previous menu." << endl;
					break;
				}
				case 1:
				{
					cout << "Start adding an employee to the list manually." << endl;
					Add_an_Empl_Manually();
					break;
				}
				case 2:
				{
					cout << "Start editing an employee's information." << endl;
					Edit_Infor_of_an_Empl();
					break;
				}
				case 3:
				{
					cout << "Start removing an employee from the list." << endl;
					Remove_an_Empl();
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
					Reset_password_for_empl();
					break;
				}
				case 7:
				{
					createRecords();
					break;
				}
				case 8:
				{
					removeRecords();
					break;
				}
				case 9:
				{
					importRecords();
					break;
				}
				case 10:
				{
					editRecordOfAnEmployee();
					break;
				}
				case 11:
				{
					viewRecords();
					break;
				}
				case 12:
				{
					clearRecordOfAnEmployee();
					break;
				}
				case 13:
				{
					viewSalaryTable();
					break;
				}
				}
			}
			//system("pause");
			//system("CLS");
		} while (choice2+1 != 7);
	} while (choice != 0);
}

void Staff::StaffMenu()
{
	int choice;
	do
	{
		choice = mainmenu.operate("Staff menu","View profile\nChange password\nChange to manage employee menu\nLog out\n");
		//system("CLS");
		switch (choice+1)
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
			//cout << "Changing to manage employee menu...." << endl;
			//system("CLS");
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
		/*if (choice != 3)
		{
			system("pause");
			system("CLS");
		}*/
	} while (choice != 4);
	//LoadfromTextfile();
	//View_list_of_Empl();
}

void Staff::createRecords()
{
	if (employeeRecords->hasData())
	{
		outputbox.display("There's existing records data of this month. You cannot create new records.\nRemove records data of this month If you really want to create new records.");
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

void Staff::editRecordOfAnEmployee()
{
	int ID, index, day, status;
	Date today;
	cout << "Input the ID of the employee that you want to edit record: ";
	cin >> ID;
	index = employeeRecords->getIndex(ID);
	if (index == -1)
	{
		cout << "There is no employee that has the ID " << ID << " in records database.\n";
		cout << "You should recheck the data.\n";
		return;
	}
	cout << "Input the day of month: ";
	cin >> day;
	if (day < 1 || day>today.Maxdayintmonth())
	{
		cout << "Invalid input day. (1 - " << today.Maxdayintmonth() << ")\n";
		return;
	}
	cout << "Input the status of the employee (1 - Present; 0 - Absent): ";
	cin >> status;
	employeeRecords->edit(index, day, status);
	cout << "Updated record of an employee\n";
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
	cout << "Input the ID of the employee that you want to clear record: ";
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

void Staff::viewSalaryTable()
{
	int n = ListEmpl.size();
	double total = 0;
	cout << "\n\tSalary table of all employees\n\n";
	cout << left << setw(12) << "ID" << setw(30) << "Name" << right << setw(12) << "Salary" << endl;
	cout << "______________________________________________________\n";
	for (int i = 0; i < n; ++i)
	{
		cout << left << setw(12) << ListEmpl[i].EInfor.getID();
		cout << setw(30) << ListEmpl[i].EInfor.getName();
		cout << right << setw(12) << ListEmpl[i].Salary << endl;
		total += ListEmpl[i].Salary;
	}
	cout << "______________________________________________________\n";
	cout << "Total salary: " << setw(39) << total << endl;
}
