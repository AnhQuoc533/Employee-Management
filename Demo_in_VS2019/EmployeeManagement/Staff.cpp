#include"Employee_Management.h"

Staff::Staff(Account acc) : StInfor(acc)
{
	load_profile();
	employeeRecords = new Record;
}

void Staff::section() {
	int choice;
	while (true) {
		choice = mainmenu.operate("SECTION", "Information\nRecord\nBack\n") + 1;
		switch (choice) {
		case 1:
			Manage_Infor_Menu();
			break;
		case 2:
			Manage_Record_Menu();
			break;
		case 3:
			mainmenu.clear();
			return;
		}
	}
}

void Staff::SaveInfortoTextfile()
{
	ofstream fsave;
	string namefile = "Employee.txt";
	fsave.open(namefile);
	if (!fsave.is_open())
	{
		outputbox.display("Cannot create file.\nSaving canceled");
		return;
	}
	else
	{
		outputbox.display("Saving data to " + namefile + "....\nNOTE:Do not shutdown the program while saving!");
		screenctrl* screen = screenctrl::instance();
		graphical_loader loader(2, screen->getbufferh() - 5, 20, "Save");
		loader.load(30);
		int n = (int)ListEmpl.size();
		for (int i = 0; i < n; i++)
		{
			fsave << ListEmpl[i].EInfor.ID << ",";
			fsave << ListEmpl[i].EInfor.ACC.Password << ",";
			fsave << ListEmpl[i].EInfor.Name << ",";
			if (ListEmpl[i].EInfor.Gender == 'M' || ListEmpl[i].EInfor.Gender == 'm')
			{
				fsave << "M" << ",";
			}
			if (ListEmpl[i].EInfor.Gender == 'F' || ListEmpl[i].EInfor.Gender == 'f')
			{
				fsave << "F" << ",";
			}
			fsave << ListEmpl[i].EInfor.DoB << ",";
			fsave << ListEmpl[i].EInfor.Phone << ",";
			fsave << ListEmpl[i].EInfor.Address;
			if (i < n - 1)
			{
				fsave << endl;
			}
		}
		outputbox.display("Finished saving data to file " + namefile + " succeeded.\nClosing the file....");
		fsave.close();
		if (!fsave.is_open())
		{
			outputbox.display("The file " + namefile + " was closed successfully.");
		}
		else
		{
			outputbox.display("Failed to close file " + namefile);
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
		outputbox.display("Cannot open the file " + namefile);
		return;
	}
	else
	{
		outputbox.display("Opened file " + namefile + " succeeded.\nLoading data to the program....");
		screenctrl* screen = screenctrl::instance();
		graphical_loader loader(2, screen->getbufferh() - 5, 20, "Load");
		loader.load(30);
		while (!fload.eof())
		{
			anEmpl.EInfor.LoadInforfrom(fload);
			anEmpl.EInfor.No = (int)ListEmpl.size() + 1;
			ListEmpl.push_back(anEmpl);
		}
		outputbox.display("Finished loading " + namefile + "\nClosing the file....");
		fload.close();
		if (!fload.is_open())
			outputbox.display("The file " + namefile + " was closed successfully.");
		else
			outputbox.display("Failed to close file " + namefile);
	}
}

void Staff::ImportListEmpfromCsv()
{
	ifstream fload;
	string namefile;
	Employee anEmpl;
	cout << "Input the name of .csv file: ";
	getline(cin, namefile);
	namefile.append(".csv");
	fload.open(namefile);
	if (!fload.is_open())
	{
		outputbox.display("Cannot find the file " + namefile);
		return;
	}
	else
	{
		outputbox.display("Opened file " + namefile + " succeeded.\nLoading data into the program....");
		screenctrl* screen = screenctrl::instance();
		graphical_loader loader(2, screen->getbufferh() - 5, 20, "Load");
		loader.load(30);
		string temp;
		Date tempDate;
		while (!fload.eof())
		{
			getline(fload, temp, ',');
			anEmpl.EInfor.No = stoi(temp);
			getline(fload, temp, ',');
			anEmpl.EInfor.ID = stoi(temp);
			getline(fload, temp, ',');
			anEmpl.EInfor.Name = temp;
			getline(fload, temp, ',');
			anEmpl.EInfor.Gender = temp[0];
			getline(fload, temp, ',');
			anEmpl.EInfor.DoB = tempDate.stoDate(temp);
			getline(fload, temp, ',');
			anEmpl.EInfor.Phone = temp;
			getline(fload, temp);
			anEmpl.EInfor.Address = temp;
			anEmpl.EInfor.ACC.Username = anEmpl.EInfor.ID;
			anEmpl.EInfor.ACC.Password = anEmpl.EInfor.DoB.toStr();
			ListEmpl.push_back(anEmpl);
		}
		outputbox.display("Finished importing " + namefile + "\nClosing the file....");
		fload.close();
		if (!fload.is_open())
		{
			outputbox.display("The file " + namefile + " was closed successfully.");
		}
		else
		{
			outputbox.display("Failed to close file " + namefile);
		}
		outputbox.display("Your data will be saved to a text file now.");
		SaveInfortoTextfile();
	}
}

int Staff::findEmplWithID(int id)
{
	if (id > 0)
	{
		int n = (int)ListEmpl.size();
		for (int i = 0; i < n; i++)
		{
			if (ListEmpl[i].EInfor.ID == id)
			{
				return i;
			}
		}
	}
	return -1;
}

void Staff::Add_an_Empl_Manually()
{
	int choice = 0, n = (int)ListEmpl.size();;
	Employee anEmpl;
	anEmpl.EInfor.InputInfor();
	do
	{
		int index = findEmplWithID(anEmpl.EInfor.ID);
		if (index != -1)
		{
			cout << "ERROR: The employee with the ID " << anEmpl.EInfor.getID() << "is already existed." << endl;
			cout << "Employee information:" << endl;
			ListEmpl[index].View_Infor_Empl();
			system("pause");
			system("CLS");
			//Need Yes/No graphic
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
					outputbox.display("Invalid input. Please input again.");
				}
			} while (id <= 0);
			anEmpl.EInfor.ID = id;
			employeeRecords->newBlank(id);
		}
		else
		{
			outputbox.display("The process was canceled.");
			return;
		}
	} while (choice == 1);
	anEmpl.EInfor.No = (int)ListEmpl.size() + 1;
	anEmpl.EInfor.ACC.Username = to_string(anEmpl.EInfor.ID);
	anEmpl.EInfor.ACC.Password = anEmpl.EInfor.DoB.toStr();
	ListEmpl.push_back(anEmpl);
	outputbox.display("New employee was added successfully.");
}

void Staff::Create_List_Empl_Manually()
{
	int n;
	do
	{
		cout << "Input the number of employees you would like to add: ";
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
	outputbox.display("The process is completed.");
}

void Staff::Edit_Infor_of_an_Empl()
{
	int id, choice = 1;
	do
	{
		cout << "Please input the ID of the employee you want to edit: ";
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
			outputbox.display("The editting will be canceled.");
			return;
		}
		cout << "Are you sure that you want to edit the employee with the ID " << id << "?" << endl;
		graphical_menu yesno;
		yesno.setclear(0);
		choice = yesno.operate("Answer", "Yes\nNo");
	} while (choice == 1);
	int index = findEmplWithID(id);
	if (index == -1)
	{
		outputbox.display("There is no employee possessing the ID " + to_string(id) + " in this list.\nThe process will be canceled.");
		cin.ignore(1);
		return;
	}
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
		cout << "Please input the ID of the employee you want to remove: ";
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
		cout << "Are you sure that you want to delete the employee with the ID " << id << "?" << endl;
		graphical_menu yesno;
		choice = yesno.operate("Confirmation", "Yes\nNo\n");
	} while (choice != 0);
	int index = findEmplWithID(id);
	if (index == -1)
	{
		outputbox.display("There is no employee possessing the ID " + to_string(id) + " in this list.\nThe process will be canceled.");
		cin.ignore(1);
		return;
	}
	int idx = employeeRecords->getIndex(id);
	if (idx == -1)
	{
		outputbox.display("There is no employee possessing the ID " + to_string(id) + " in records database.\nYou should re-check the data.");
	}
	else
		employeeRecords->remove(idx);
	outputbox.display("Start removing....");
	int n = (int)ListEmpl.size();
	for (int i = index + 1; i < n; i++)
	{
		ListEmpl[i].EInfor.No = ListEmpl[i].EInfor.getNo() - 1;
	}
	ListEmpl.erase(ListEmpl.begin() + index);
	outputbox.display("The employee was removed successfully!"); // Thanh added.
}

void Staff::View_list_of_Empl()
{
	string ID, No;
	int space1 = 0, space2 = 0, space3 = 0;
	int n = (int)ListEmpl.size();
	int offset = 0;
	screenctrl* screen = screenctrl::instance();
	int partsize = screen->getbufferh() - 9 - TXTY;

	while (1)
	{
		cout << "LIST OF EMPLOYEES:\n(press up/down to navigate)\n";
		cout << setw(7) << "No" << setw(17) << "ID" << setw(27) << "Name" << endl;
		if (offset != 0) cout << setw(7) << "..." << setw(18) << "..." << setw(25) << "..." << endl;
		for (int i = offset; i < offset + partsize; i++)
		{
			ID.clear();
			No.clear();
			if (ListEmpl[i].EInfor.getNo() < 10)
			{
				No = "0";
			}
			No.append(to_string(ListEmpl[i].EInfor.No));
			if (ListEmpl[i].EInfor.getID() < 10)
			{
				ID = "0";
			}
			ID.append(to_string(ListEmpl[i].EInfor.ID));
			space1 = 5 + (int)No.length();
			space2 = 15 - ((int)No.length() - 2) + (int)ID.length();
			space3 = 23 - ((int)ID.length() - 2) + (int)ListEmpl[i].EInfor.getName().length();
			cout << setw(space1) << No << setw(space2) << ID << setw(space3) << ListEmpl[i].EInfor.Name << endl;
		}
		if (offset + partsize != n) cout << setw(7) << "..." << setw(18) << "..." << setw(25) << "..." << endl;
		char c = _getch();
		if (c == -32)
		{
			c = _getch();
			switch (c)
			{
			case 72: offset = (offset > 0) ? offset - 1 : 0; break;
			case 80: offset = (offset + partsize < n) ? offset + 1 : n - partsize; break;
			}
			outputbox.clearbuffer();
		}
		if (c == '\r')
		{
			return;
		}
	}

}

void Staff::View_Infor_of_an_Empl()
{
	int id;
	cout << "Input the ID of the employee you want to view: ";
	cin >> id;
	if (cin.fail() || id <= 0)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(2000, '\n');
			id = 0;
		}
		outputbox.display("Invalid ID.\nThe process will be canceled.");
		return;
	}
	int index = findEmplWithID(id);
	if (index == -1)
	{
		outputbox.display("There is no employee possessing the ID " + to_string(id) + " in your list.\nThe process will be canceled.");
		cin.ignore(1);
		return;
	}
	cout << "The information of this employee:" << endl;
	ListEmpl[index].View_Infor_Empl();
}

void Staff::Reset_password_for_empl()
{
	int id, choice = 1;
	do
	{
		cout << "Please input the ID of the employee you want to reset password: ";
		cin >> id;
		if (cin.fail() || id <= 0)
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(2000, '\n');
			}
			id = 0;
			outputbox.display("Invalid ID.\nThis process will be canceled.");
			return;
		}
		cout << "Are you sure that you want to reset the password of employee with the ID " << id << "?" << endl;
		graphical_menu yesno;
		choice = yesno.operate("Confirmation", "Yes\nNo\n");
	} while (choice != 0);
	int index = findEmplWithID(id);
	if (index == -1)
	{
		outputbox.display("There is no employee possessing the ID " + to_string(id) + " in your list.\nThe process will be canceled.");
		cin.ignore(1);
		return;
	}
	outputbox.display("Resetting password....");
	ListEmpl[index].EInfor.ACC.Password = ListEmpl[index].EInfor.DoB.toStr();
	outputbox.display("Succeeded!");
}

void Staff::View_Profile()
{
	StInfor.OutputInfor();
}

void Staff::Manage_Infor_Menu()
{
	int choice = 0;
	while (true) {
		choice = mainmenu.operate("LOAD DATA", "Import new list of employee from .csv file\nLoad existed list of employee from your database\nCreate new list of employee manually\nExit");
		switch (choice + 1)
		{
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
			case 4:
			{
				mainmenu.clear();
				return;
			}
		}
		if (ListEmpl.size() == 0) {
			outputbox.display("No employee found. There is nothing to manange!");
			mainmenu.clear();
		}
		else
			break;
	}
	do
	{
		mainmenu.autowarp(0);
		choice = mainmenu.operate("MANAGE INFORMATION", "Exit\nAdd an employee\nEdit information of an employee\nRemove an employee\nView list of employees\nView information of an employee\nReset password of an employee\nCreate new records of a month\nRemove records data\nImport records data from csv file\nEdit record of an employee. \nView records of all employees\nClear record of an employee\nView salary of all employees");
		switch (choice)
		{
			case 0:
			{	
				outputbox.display("Please wait while saving data before returning to the previous menu.");
				SaveInfortoTextfile();
				ListEmpl.clear();
				outputbox.display("Returning to previous menu....");
				mainmenu.clear();
				mainmenu.autowarp(1);
				break;
			}
			case 1:
			{
				Add_an_Empl_Manually();
				break;
			}
			case 2:
			{
				Edit_Infor_of_an_Empl();
				break;
			}
			case 3:
			{
				Remove_an_Empl();
				break;
			}
			case 4:
			{
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
				cout << "Start reseting the password for an employee." << endl;
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
	} while (choice != 0);
}

void Staff::createRecords()
{
	if (employeeRecords->hasData())
	{
		outputbox.display("There's existing records data of this month. You cannot create new records.\nRemove records data of this month if you want to create new records.");
		return;
	}
	int n = (int)ListEmpl.size();
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
		cout << "There is no employee possessing the ID " << ID << " in records database.\n";
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
		cout << "There is no employee possessing the ID " << ID << " in records database.\n";
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
	int n = (int)ListEmpl.size();
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
			cout << "There is no employee possessing the ID " << ListEmpl[i].EInfor.getID() << " in records database.\n";
			cout << "You should recheck the data." << endl;
			continue;
		}
		employeeRecords->view(index);
	}
}

void Staff::Manage_Record_Menu()
{
	ifstream fin;
	vector<string> months;
	string tmp, menuOption;
	int n, choice = 0, choice2 = 0;
	LoadfromTextfile();
	if (ListEmpl.size() == 0) {
		outputbox.display("No employee found. There is nothing to manange!");
		mainmenu.clear();
		return;
	}
	fin.open("Month-Record.txt");
	if (fin.is_open())
	{
		while (getline(fin, tmp))
		{
			months.push_back(tmp);
		}
		fin.close();
	}
	else
	{
		cout << "Cannot load data. Returning to previous menu." << endl;
		fin.close();
		return;
	}
	n = (int)months.size();
	for (int i = 0; i < n; ++i)
	{
		menuOption.append(to_string(i + 1) + ". " + months[i] + '\n');
	}
	menuOption.append(to_string(n + 1) + ". Create new month record\n");
	menuOption.append("0. Back\n");
	while (true)
	{
		choice = mainmenu.operate("Manage Record", menuOption);
		if (choice == 0)
		{
			break;
		}
		else if (choice == (n + 1))
		{
			createRecords();
			break;
		}
		else
		{
			employeeRecords = new Record(months[static_cast<__int64>(choice) - 1]);
			while (true)
			{
				mainmenu.autowarp(0);
				choice2 = mainmenu.operate("Manage Record", "Exit\nImport records data from csv file. \nRemove records data. \nEdit record of an employee. \nView records of all employees. \nClear record of an employee. \nView salary of all employees");
				switch (choice2)
				{
				case 0:
				{
					outputbox.display("Returning to previous menu.");
					mainmenu.clear();
					mainmenu.autowarp(1);
					break;
				}
				case 1:
				{
					importRecords();
					break;
				}
				case 2:
				{
					removeRecords();
					break;
				}
				case 3:
				{
					editRecordOfAnEmployee();
					break;
				}
				case 4:
				{
					viewRecords();
					break;
				}
				case 5:
				{
					clearRecordOfAnEmployee();
					break;
				}
				case 6:
				{
					viewSalaryTable();
					break;
				}
				}
			}
		}
	}
}

void Staff::viewSalaryTable()
{
	int n = (int)ListEmpl.size();
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

string Staff::staff_name() {
	return StInfor.Name;
}

void Staff::load_profile() {
	ifstream f("Staff.txt");
	string tmp;
	while (true) {
		getline(f, tmp, ',');
		if (tmp == StInfor.ACC.Username) {
			getline(f, tmp, ',');
			getline(f, tmp, ',');
			StInfor.Name = tmp;
			getline(f, tmp, ',');
			StInfor.Gender = tmp[0];
			getline(f, tmp, ',');
			StInfor.DoB.stoDate(tmp);
			getline(f, tmp, ',');
			StInfor.Phone = tmp;
			getline(f, tmp);
			StInfor.Address = tmp;
			break;
		}
		else {
			getline(f, tmp);
		}
	}
	f.close();
}

void Staff::view_profile() {
	cout << "Username: " << StInfor.ACC.Username << endl;
	StInfor.OutputInfor();
}