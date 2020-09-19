#include"Employee_Management.h"

Staff::Staff(Account acc) : StInfor(acc), employeeRecords(nullptr) {
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

void Staff::section() {
	int choice;
	while (true) {
		choice = mainmenu.operate("STAFF MENU", "Information\nRecord\nBack\n") + 1;
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

void Staff::SaveInfortoTextfile(string waytoSave)
{
	ofstream fsave;
	string namefile = "Employee.txt";
	if (waytoSave == "overwrite")
	{
		fsave.open(namefile);
	}
	else
	{
		fsave.open(namefile, ios::app);
	}
	if (!fsave.is_open())
	{
		outputbox.display("Cannot create file.\nSaving canceled");
		return;
	}
	else
	{
		if (waytoSave == "Not overwrite")
		{
			if (fsave.beg != fsave.end)
			{
				fsave << endl;
			}
		}
		outputbox.display("Saving data to " + namefile + "....\nDO NOT shutdown the program while saving!");
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
		if (fsave.is_open())
		{
			outputbox.display("Failed to close file " + namefile);
		}
	}
}

void Staff::LoadInforInRecord()
{
	ifstream fload;
	string namefile = "Employee.txt";
	fload.open(namefile);
	if (!fload.is_open())
	{
		outputbox.display("Cannot open the file " + namefile);
		return;
	}
	else
	{
		Employee anEmpl;
		while (fload.peek() != EOF)
		{
			anEmpl.EInfor.LoadInforfrom(fload);
			anEmpl.EInfor.No = (int)ListEmpl.size() + 1;
			ListEmpl.push_back(anEmpl);
		}
		fload.close();
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
		while (fload.peek() != EOF)
		{
			anEmpl.EInfor.LoadInforfrom(fload);
			anEmpl.EInfor.No = (int)ListEmpl.size() + 1;
			ListEmpl.push_back(anEmpl);
		}
		outputbox.display("Finished loading " + namefile + "\nClosing the file....");
		fload.close();
		if (fload.is_open())
		{
			outputbox.display("Failed to close file " + namefile);
		}
	}
}

void Staff::ImportListEmpfromCsv()
{
	ifstream fload;
	string namefile;
	Employee anEmpl;
	cout << "Input the name of csv file: ";
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
		while (fload.peek() != EOF)
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
		if (fload.is_open())
		{
			outputbox.display("Failed to close file " + namefile);
		}
		outputbox.display("Your data will be saved to a text file now.");
		int choice = 0;
		choice = mainmenu.operate("Saving Method", "Overwrite existing data\nAdd to existing data\n");
		switch (choice + 1)
		{
		case 1:
		{
			SaveInfortoTextfile("overwrite");
			break;
		}
		case 2:
		{
			SaveInfortoTextfile("Not overwrite");
			break;
		}		
		}
		mainmenu.clear();
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
			outputbox.display("ERROR: The employee with the ID " + to_string(anEmpl.EInfor.getID()) + " is already existed.");
			cout << "Employee information:" << endl;
			ListEmpl[index].View_Infor_Empl();
			graphical_menu menu;
			choice = 1-menu.operate("Action", "Try again\nBack\n");
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
					outputbox.display("Invalid input. Please input again.");
				}
			} while (id <= 0);
			anEmpl.EInfor.ID = id;			
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
	employeeRecords->newBlank(anEmpl.EInfor.ID);
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
	/*cout << "Are you sure that you want to edit the employee with the ID " << id << "?" << endl;
	graphical_menu yesno;
	yesno.setclear(0);
	choice = yesno.operate("Answer", "Yes\nNo");*/
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
	if (idx!=-1)
		employeeRecords->remove(idx);
	outputbox.display("Start removing....");
	int n = (int)ListEmpl.size();
	for (int i = index + 1; i < n; i++)
	{
		ListEmpl[i].EInfor.No = ListEmpl[i].EInfor.getNo() - 1;
	}
	ListEmpl.erase(ListEmpl.begin() + index);
	outputbox.display("The employee was removed successfully!");
}

void Staff::View_list_of_Empl()
{
	string ID, No;
	int space1 = 0, space2 = 0, space3 = 0;
	int n = (int)ListEmpl.size();
	int offset = 0;
	screenctrl* screen = screenctrl::instance();
	int partsize = screen->getbufferh() - 11 - TXTY;
	graphical_box temp;

	while (true)
	{
		temp.turnCursor(0);
		cout << "LIST OF EMPLOYEES:\n(press up/down to navigate)\n";
		cout << right << setw(10) << "No" << setw(3) << (char)179 << setw(15) << "ID" << setw(3) << (char)179 << setw(5) << " " << left << setw(20) << "Name" << endl;
		for (int i = 0; i < 17 + 27 + 20; i++)
			if (i == 12 || i == 13 + 25 - 8)
			{
				if (offset == 0) cout << (char)197;
				else cout << (char)193;
			}
			else cout << (char)196;
		cout << endl;
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
			space2 = 15 - ((int)No.length() - 2) + (int)ID.length() - 7;
			space3 = 23 - ((int)ID.length() - 2) + (int)ListEmpl[i].EInfor.getName().length() - 9;
			cout << right << setw(10) << No << setw(3) << (char)179 << setw(15) << ID << setw(3) << (char)179 << setw(5) << " " << left << setw(20) << ListEmpl[i].EInfor.Name << endl;
		}
		if (offset + partsize != n) cout << right << setw(10) << "..." << setw(3) << (char)179 << setw(15) << "..." << setw(3) << (char)179 << setw(5) << " " << left << setw(20) << "..." << endl;
		char c = _getch();
		if (c == -32)
		{
			c = _getch();
			switch (c)
			{
			case 72: offset = (offset > 0) ? offset - 1 : 0; break;
			case 80: offset = (offset + partsize < n) ? offset + 1 : n - partsize; break;
			}
		}
		if (c == '\r')
		{
			temp.turnCursor(1);
			return;
		}
		outputbox.clearbuffer();
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
		choice = mainmenu.operate("LOAD DATA", "Import new list of employee from csv file\nLoad existed list of employee from database\nCreate new list of employee manually\nBack\n");
		switch (choice + 1)
		{
			case 1:
			{
				ImportListEmpfromCsv();
				mainmenu.autowarp(0);
				mainmenu.clear();
				mainmenu.autowarp(1);
				ListEmpl.clear();
				continue;
				break;
			}
			case 2:
			{
				LoadfromTextfile();
				employeeRecords = new Record;
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
			if (employeeRecords) {
				delete employeeRecords;
				employeeRecords = nullptr;
				mainmenu.autowarp(0);
				mainmenu.clear();
				mainmenu.autowarp(1);
			}
			continue;
		}		
		while (choice != 7)
		{
			mainmenu.autowarp(0);
			choice = mainmenu.operate("MANAGE INFORMATION", "Add an employee\nEdit information of an employee\nRemove an employee\nView list of employees\nView information of an employee\nReset password of an employee\nSave and Back") + 1;
			switch (choice)
			{
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
					Reset_password_for_empl();
					break;
				}
				case 7:
				{
					exit_infor_menu();
					break;
				}
			}
		}
	}
}

void Staff::exit_infor_menu() {
	outputbox.display("Please wait while saving data before returning to the previous menu.");
	SaveInfortoTextfile("overwrite");
	ListEmpl.clear();
	if (employeeRecords) {
		delete employeeRecords;
		employeeRecords = nullptr;
	}
	outputbox.display("Returning to previous menu....");
	mainmenu.clear();
	mainmenu.autowarp(1);
}

string Staff::load_month(vector<string>& months) {
	ifstream fin;
	string tmp;
	months.clear();
	fin.open("Month-Record.txt");
	if (fin.is_open())
	{
		while (getline(fin, tmp, ','))
		{
			months.push_back(tmp);
		}
		fin.close();
	}
	else
	{
		outputbox.display("Cannot load data.\nReturning to previous menu....");
		return tmp;
	}
	tmp.clear();
	for (int i = 0; i < (int)months.size(); ++i)
	{
		tmp += months[i] + '\n';
	}
	tmp += "Create new month record\nBack";
	return tmp;
}

void Staff::Manage_Record_Menu() {
	LoadInforInRecord();
	if (ListEmpl.size() == 0) {
		outputbox.display("No employee found in database. There is nothing to manange!");
		outputbox.display("Returning to previous menu....");
		mainmenu.clear();
		return;
	}
	vector<string> months;
	string option;
	int n, choice;
	while (true) {
		option = load_month(months);
		if (option.empty()) {
			ListEmpl.clear();
			mainmenu.clear();
			return;
		}
		choice = mainmenu.operate("MONTH RECORD", option);
		n = (int)months.size();
		if (choice == n)
		{
			while (true) {
				cout << "Input the month you want to create its record (MM-YYYY): ";
				getline(cin,option);
				if (valid_month_record(option))
					break;
				outputbox.display("Invalid input. Please try again.");
			}
			outputbox.display("Creating new record....");
			employeeRecords = new Record(option);
			if (createRecords()) {
				if (add_month(option, n)) {
					screenctrl* screen = screenctrl::instance();
					graphical_loader loader(2, screen->getbufferh() - 5, 20, "Load");
					loader.load(30);
					outputbox.display("New month was added successfully.");
				}
				else {
					delete employeeRecords;
					continue;
				}
			}
			else {
				delete employeeRecords;
				continue;
			}
		}
		else if (choice == (n + 1))
		{
			outputbox.display("Returning to previous menu....");
			mainmenu.clear();
			return;
		}
		else
		{
			employeeRecords = new Record(months[choice]);
		}
		choice = 0;
		while (choice != 8)
		{
			mainmenu.autowarp(0);
			choice = mainmenu.operate("MANAGE RECORD", "Import record data from csv file\nEdit record of an employee\nClear record of an employee\nView record of all employees\nView salary of all employees\nAdd comment to an employee\nView all of your comments\nSave and back") + 1;
			switch (choice)
			{
				case 1:
				{
					importRecords();
					break;
				}
				case 2:
				{
					editRecordOfAnEmployee();
					break;
				}
				case 3:
				{
					clearRecordOfAnEmployee();
					break;
				}
				case 4:
				{
					viewRecords();
					break;
				}
				case 5:
				{
					viewSalaryTable();
					break;
				}
				case 6:
				{
					add_cmt();
					break;
				}
				case 7:
				{
					view_cmt();
					break;
				}
				case 8:
				{
					outputbox.display("Please wait while saving data before returning to the previous menu.");
					delete employeeRecords;
					screenctrl* screen = screenctrl::instance();
					graphical_loader loader(2, screen->getbufferh() - 5, 20, "Save");
					loader.load(30);
					outputbox.display("Returning to previous menu....");
					mainmenu.clear();
					mainmenu.autowarp(1);
					ListEmpl.clear();
					break;
				}
			}
		}
	}
}

bool Staff::add_month(string month, int n) {
	ofstream f("Month-Record.txt", ios::app);
	if (f.is_open()) {
		if (n)
			f << ',' << month;
		else
			f << month;
		f.close();
		return true;
	}
	else {
		outputbox.display("Cannot add month.");
		return false;
	}
}

bool Staff::valid_month_record(const string& month) {
	if (month.size() != 7 || month[2] != '-')
		return false;
	for (int i = 0; i < 7; ++i) {
		if (i == 2)
			continue;
		if (month[i] < 48 || month[i]> 57)
			return false;
	}
	string m(month, 0, 2);
	string y(month, 3, 4);
	if (stoi(m) < 1 || stoi(m) > 12 || stoi(y) < 1)
		return false;
	return true;
}

bool Staff::createRecords()
{
	if (employeeRecords->hasData())
	{
		outputbox.display("There is existing record data of this month. You cannot create new record.");
		mainmenu.autowarp(0);
		mainmenu.clear();
		mainmenu.autowarp(1);
		return false;
	}
	int n = (int)ListEmpl.size();
	int* arr = new int[n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = ListEmpl[i].EInfor.getID();
	}
	employeeRecords->newBlank(arr, n);
	delete[] arr;
	outputbox.display("A blank record has been created.");
	return true;
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
		outputbox.display("There is no employee possessing the ID " +to_string(ID)+ " in record database.");
		return;
	}
	cout << "Input the day of month: ";
	cin >> day;
	if (day < 1 || day>today.Maxdayintmonth())
	{
		cout << "Invalid input day. (1 - " << today.Maxdayintmonth() << ")\n";
		return;
	}
	cout << "Input the status of the employee\n";
	graphical_menu menu;
	status = 1 - menu.operate("Status", "Present\nAbsent");
	employeeRecords->edit(index, day, status);
	outputbox.display("The record of an employee was edited successfully.");
}

void Staff::removeRecords()
{
	if (employeeRecords->hasData())
	{
		employeeRecords->clearData();
	}
}

void Staff::importRecords()
{
	ifstream fin;
	string filename;
	cout << "Input the name of the csv file: ";
	getline(cin, filename);
	filename.append(".csv");
	fin.open(filename);
	if (!fin.is_open())
	{
		outputbox.display("Cannot import data from " + filename);
	}
	else
	{
		removeRecords();
		screenctrl* screen = screenctrl::instance();
		outputbox.display("Openned file " + filename + " successfully.\nLoading data to the program...");
		graphical_loader loader(2, screen->getbufferh() - 5, 20, "Load");
		loader.load(30);
		employeeRecords->import(fin);
		outputbox.display("Finished importing " + filename);
	}
	fin.close();
}

void Staff::clearRecordOfAnEmployee()
{
	int ID, index;
	cout << "Input the ID of the employee that you want to clear record: ";
	cin >> ID;
	index = employeeRecords->getIndex(ID);
	if (index == -1)
	{
		outputbox.display("There is no employee possessing the ID " + to_string(ID) + " in record database.");
		return;
	}
	employeeRecords->clear(index);
	outputbox.display("Record of the employee was cleared successfully.");
}

void Staff::viewRecords()
{
	int index;
	int n = (int)ListEmpl.size();
	int offset = 0;
	screenctrl* screen = screenctrl::instance();
	int partsize = screen->getbufferh() - 8 - TXTY;
	graphical_box temp;
	while (1)
	{
		temp.turnCursor(0);
		cout << left << setw(10) << "   " << setw(2) << (char)179;
		for (int i = 1; i <= employeeRecords->number_of(); ++i)
		{
			cout << setw(5) << i;
		}
		cout << endl;
		for (int i = 0; i < employeeRecords->number_of() * 5 + 12; i++)
			if (i == 10) cout << (char)197; else cout << (char)196;
		cout << endl;
		for (int i = offset; i < offset+partsize; ++i)
		{
			index = employeeRecords->getIndex(ListEmpl[i].EInfor.getID());
			if (index == -1)
			{
				outputbox.display("There is no employee possessing the ID " + to_string(ListEmpl[i].EInfor.getID()) + " in record database.");
				continue;
			}
			employeeRecords->view(index);
		}
		char c = _getch();
		if (c == -32)
		{
			c = _getch();
			switch (c)
			{
			case 72: offset = (offset > 0) ? offset - 1 : 0; break;
			case 80: offset = (offset + partsize < n) ? offset + 1 : n - partsize; break;
			}
		}
		if (c == '\r')
		{
			temp.turnCursor(1);
			return;
		}
		outputbox.clearbuffer();
	}
}

void Staff::viewSalaryTable()
{
	int n = (int)ListEmpl.size();
	int total = 0;
	int offset = 0, salary, index;
	screenctrl* screen = screenctrl::instance();
	int partsize = screen->getbufferh() - 9 - TXTY;
	graphical_box temp;
	for (int i=0;i<n;i++) total += employeeRecords->calcSalary(i);
	graphical_textbox totalbox(screen->getbufferw() * 2 / 3, screen->getbufferh() / 2, 50, 3, 0);
	totalbox.setfocus(0);	
	while (true)
	{
		totalbox.display("Total salary: " + to_string(total));
		temp.turnCursor(0);
		cout << "Salary table\n(press up/down to navigate)\n";
		cout << left << setw(10) << "ID" << setw(2) << (char)179 << setw(28) << "Name" << setw(2) << (char)179 << right << setw(12) << "Salary" << endl;
		for (int i = 0; i < 30+2*12; i++)
			if (i == 10||i==40) cout << (char)197; else cout << (char)196;
		cout << endl;
		for (int i = offset; i < offset+partsize; ++i)
		{
			index = employeeRecords->getIndex(ListEmpl[i].EInfor.getID());
			if (index == -1)
			{
				outputbox.display("There is no employee possessing the ID " + to_string(ListEmpl[i].EInfor.getID()) + " in records database.\nYou should recheck the data.");
				continue;
			}
			salary = employeeRecords->calcSalary(index);
			cout << left << setw(10) << ListEmpl[i].EInfor.getID() << setw(2) << (char)179;
			cout << setw(28) << ListEmpl[i].EInfor.getName() << setw(2) << (char)179;
			cout << right << setw(12) << salary << endl;
		}
		char c = _getch();
		if (c == -32)
		{
			c = _getch();
			switch (c)
			{
			case 72: offset = (offset > 0) ? offset - 1 : 0; break;
			case 80: offset = (offset + partsize < n) ? offset + 1 : n - partsize; break;
			}
		}
		if (c == '\r')
		{
			temp.turnCursor(1);
			return;
		}
		outputbox.clearbuffer();
	}		
}

string Staff::staff_name() {
	return StInfor.Name;
}

void Staff::view_profile() {
	cout << "Username: " << StInfor.ACC.Username << endl;
	StInfor.OutputInfor();
}

void Staff::add_cmt() {
	int ID, index, money;
	string cmt;
	cout << "Input the ID of the employee: ";
	cin >> ID;
	index = employeeRecords->getIndex(ID);
	if (index == -1)
	{
		outputbox.display("There is no employee possessing the ID " + to_string(ID) + " in record database.");
		return;
	}
	graphical_menu menu;
	index = menu.operate("Action", "Reward\nFine");
	cout << "Input the amount of money: ";
	cin >> money;
	if (index)
		money = -money;
	cout << "Input your reason: ";
	cin.ignore(1);
	getline(cin, cmt);
	save_cmt(ID, money, cmt);
}

void Staff::save_cmt(int id, int money, string cmt) {
	ofstream f("Comment.txt", ios::app);
	if (f.is_open()) {
		outputbox.display("Saving your comment....");
		screenctrl* screen = screenctrl::instance();
		graphical_loader loader(2, screen->getbufferh() - 5, 20, "Save");
		loader.load(30);
		f.seekp(f.beg, f.end);
		if (f.tellp() != 0)
			f << endl;
		f << employeeRecords->month_record() << ',' << id << ',' << money << ',' << cmt;
		f.close();
		outputbox.display("Your comment was saved successfully!");
	}
	else
		outputbox.display("Failed to save your comment.");
}
// Graphics
void Staff::view_cmt() {
	ifstream f("Comment.txt");
	string tmp;
	if (f.is_open()) {
		cout << right << setw(20) << "Employee" << setw(2) << (char)179 << right << setw(20) << "Bonus/Fine" << setw(2) << (char)179 << setw(5) << " " << left << setw(20) << "Comment" << endl;
		for (int i = 0; i < 30 + 3 * 12; i++)
			if (i == 21 || i == 43) cout << (char)197; else cout << (char)196;
		cout << endl;
		while (f.good()) {
			getline(f, tmp, ',');
			if (tmp == employeeRecords->month_record()) {
				graphical_box z;
				z.charColorate(WHITE);
				getline(f, tmp, ',');
				cout << right << setw(20) << tmp << setw(2) << (char)179;
				getline(f, tmp, ',');
				if (stoi(tmp) < 0) z.charColorate(BAD);
				else z.charColorate(GOOD);
				cout << right << setw(20) << tmp;
				getline(f, tmp);
				z.charColorate(WHITE);
				cout << setw(2) << (char)179 << setw(5) << " " << left << setw(12) << tmp << endl;
			}
			else
				getline(f, tmp);
		}
		f.close();
	}
	else
		outputbox.display("Failed to load your comments.");
}