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
			anEmpl.EInfor.setNo(stoi(temp));
			getline(fload, temp, ',');
			anEmpl.EInfor.setID(stoi(temp));
			getline(fload, temp, ',');
			anEmpl.EInfor.setName(temp);
			getline(fload, temp, ',');
			anEmpl.EInfor.setGender(temp[0]);
			getline(fload, temp, '/');
			tempd = stoi(temp);
			getline(fload, temp, '/');
			tempm = stoi(temp);
			getline(fload, temp, ',');
			tempy = stoi(temp);
			Date tempDate(tempy, tempm, tempd);
			anEmpl.EInfor.setDoB(tempDate);
			getline(fload, temp, ',');
			anEmpl.EInfor.setPhone(temp);
			getline(fload, temp);
			anEmpl.EInfor.setAddress(temp);
			ListEmpl.push_back(anEmpl);
		}
		cout << endl << "Finished importing " << filename << "." << endl;
		cout << "Closing the file...." << endl;
		fload.close();
		cout << "The file " << filename << " was closed successedfully." << endl;
	}
}

int Staff::findEmplWithID(int id)
{
	int n = ListEmpl.size();
	for (int i = 0; i < n; i++)
	{
		if (ListEmpl[i].EInfor.getID() == id)
		{
			return i;
		}
	}
	return -1;
}

void Staff::Add_an_Empl_Manually()
{
	cout << "Start adding...." << endl;
	int choice = 0, n = ListEmpl.size();;
	Employee anEmpl;
	anEmpl.inputEmpl();
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
	ListEmpl.push_back(anEmpl);
}

void Staff::Edit_Infor_of_an_Empl()
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
			id = 0;
		}
		cout << "Invalid ID." << endl;
		cout << "The editing will be canceled." << endl;
		return;
	}
	int index = findEmplWithID(id);
	if (index == -1)
	{
		cout << "There is no employee that has the ID " << id << "in this list." << endl;
		cout << "The editing will be canceled." << endl;
		return;
	}
	cout << "Start editing...." << endl;
	ListEmpl[index].editEmplInfor();
	cout << "The employee after edited:" << endl;
	ListEmpl[index].View_Infor_Empl();
	cout << endl;
}

void Staff::Remove_an_Empl()
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
			id = 0;
		}
		cout << "Invalid ID." << endl;
		cout << "The removing will be canceled." << endl;
		return;
	}
	int index = findEmplWithID(id);
	if (index == -1)
	{
		cout << "There is no employee that has the ID " << id << "in this list." << endl;
		cout << "The removing will be canceled." << endl;
		return;
	}
	cout << "Start removing...." << endl;
	int n = ListEmpl.size();
	for (int i = index + 1; i < n; i++)
	{
		ListEmpl[i].EInfor.setNo(ListEmpl[i].EInfor.getNo() - 1);
	}
	ListEmpl.erase(ListEmpl.begin() + index);
}

void Staff::View_list_of_Empl()
{
	int n = ListEmpl.size();
	for (int i = 0; i < n; i++)
	{
		ListEmpl[i].View_Infor_Empl();
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
		if (id == ListEmpl[i].EInfor.getID())
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
	ListEmpl[index].View_Infor_Empl();
}

void Staff::StaffMenu()
{
	//Test import xong comment lai nhu luc dau r test tiep ham add, xong r tu do test luon cac ham khac
	//Gop y gi nhan lien qua Mess giup^^.
	ImportListEmpfromCsv();
	cout << endl;
	View_list_of_Empl();
	cout << endl;
	Add_an_Empl_Manually();
	Edit_Infor_of_an_Empl();
	View_list_of_Empl();
	cout << endl;
	Remove_an_Empl();
	cout << endl << "List of Empl after remove an Employee:" << endl;
	View_list_of_Empl();
}