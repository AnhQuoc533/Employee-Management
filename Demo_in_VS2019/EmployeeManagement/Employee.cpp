#include"Employee_Management.h"

Employee::Employee() {
	time_t now = time(0);
	tm cdate;
	localtime_s(&cdate, &now);
	logday = cdate.tm_mday;
	logmonth = cdate.tm_mon + 1;
	logyear = cdate.tm_year + 1900;
}

Employee::Employee(Account acc) : EInfor(acc) {
	time_t now = time(0);
	tm cdate;
	localtime_s(&cdate, &now);
	logday = cdate.tm_mday;
	logmonth = cdate.tm_mon + 1;
	logyear = cdate.tm_year + 1900;
}

void Employee::View_Infor_Empl()
{
	cout << "ID: " << EInfor.getID() << endl;
	EInfor.OutputInfor();
}

string Employee::employee_name() {
	return EInfor.getName();
}

void Employee::loadEmplData(Account checker)
{
	ifstream fi("Employee.txt");
	bool fail = 1;
	if (fi)
	{
		while (fi.peek() != EOF)
		{
			EInfor.LoadInforfrom(fi);
			if (EInfor.getID() == stoi(checker.getUsername()))
			{
				fail = 0;
				break;
			}
		}
		fi.close();
	}
	if (fail) outputbox.display("Load failed!");
}

bool Employee::loadEmplRecord(int month)
{
	string file = "Record-";
	if (month < 10) file += "0";
	file += to_string(month) + "-" + to_string(logyear) + ".txt";
	ifstream fi(file);
	string input, tok;
	if (fi)
	{
		while (fi.peek() != EOF)
		{
			getline(fi, input);
			istringstream iss(input);
			getline(iss, tok, ',');
			if (tok == to_string(EInfor.getID()))
			{
				int daymax[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
				for (int i = 0; i < daymax[month - 1]; i++)
				{
					getline(iss, tok, ',');
					record[i] = stoi(tok);
				}
				break;
			}
		}
		fi.close();
		return 1;
	}
	return 0;
}

void Employee::checkin()
{
	string file = "Record-";
	if (logmonth < 10) file += "0";
	file += to_string(logmonth) + "-" + to_string(logyear) + ".txt";
	ifstream fi(file);
	string input, tok;
	vector<string> save;
	if (fi)
	{
		while (fi.peek() != EOF)
		{
			getline(fi, input);
			istringstream iss(input);
			getline(iss, tok, ',');
			if (tok == to_string(EInfor.getID()))
			{
				int offset = (int)input.find(",");
				int i = offset + (logday * 2 - 1);
				input[i] = '1';
			}
			save.push_back(input);
		}
		fi.close();
		ofstream fo(file);
		int n = (int)save.size();
		for (int i = 0; i < n; i++) fo << save[i] << endl;
		fo.close();
		outputbox.display("Checked in successfully!");
	}
	else outputbox.display("Cannot load record for check-in.");
}

void Employee::viewCheckin(int month)
{
	if (!loadEmplRecord(month)) return;
	int sep = 5;
	int daymax[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	graphical_box temp;
	string word[] = { "January","February","March","April","May","June","July","August","September","October","November","December" };
	cout << setw(10) << left << word[month - 1] << setw(2) << (char)179;
	for (int i = 0; i < daymax[month - 1]; i++)
	{
		cout << setw(sep);
		if (record[i])
		{
			temp.charColorate(GOOD);
			cout << char(251);
		}
		else
		{
			temp.charColorate(BAD);
			cout << "x";
		}
	}
	cout << endl;
	temp.charColorate(WHITE);
}

void Employee::boardsetup()
{
	int sep = 5;
	cout << left << setw(10) << "Day" << setw(2) << (char)179;
	for (int i = 0; i < 31; i++) cout << setw(sep) << i + 1;
	cout << endl;
	for (int i = 0; i < 31 * 5 + 12; i++)
		if (i == 10) cout << (char)197; else cout << (char)196;
	cout << endl;
}

void Employee::viewCheckin()
{
	cout << "Today is " << logday << "/" << logmonth << "/" << logyear << endl;
	boardsetup();
	viewCheckin(logmonth);
	outputbox.display("Here is your check-in of this month.");
}

void Employee::viewAnnualRecord()
{
	boardsetup();
	for (int i = 1; i < 13; i++)
		viewCheckin(i);
	outputbox.display("Your check-in of this year (" + to_string(logyear) + ").");
}

void Employee::viewAnnualSalary() {
	string word[] = { "January","February","March","April","May","June","July","August","September","October","November","December" };
	int daymax[] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
	int sep = 15; int workcount = 0, scale = 300000;
	cout << left << setw(sep) << "Month" << setw(2) << (char)179 << setw(sep) << "Day worked" << setw(2) << (char)179 << setw(sep) << "Salary" << endl;
	for (int i = 0; i < (sep + 2) * 3; i++) if (i == 15 || i == 32) cout << (char)197; else cout << (char)196;
	cout << endl;
	for (int i = 1; i < 13; i++)
	{
		if (!loadEmplRecord(i)) continue;
		workcount = 0;
		for (int j = 0; j < daymax[i - 1]; j++) if (record[j]) workcount++;
		cout << left << setw(sep) << word[i - 1] << setw(2) << (char)179 << setw(sep) << workcount << setw(2) << (char)179 << setw(sep) << workcount * scale << endl;
	}
	outputbox.display("This is your salary of this year.");
}

void Employee::EmployeeMenu()
{
	while (true)
	{
		mainmenu.autowarp(0);
		int choice = mainmenu.operate("COMMANDS", "Check in\nView check-in Result\nView annual salary\nView annual record\nBack");
		switch (choice)
		{
		case 0: checkin(); break;
		case 1: viewCheckin(); break;
		case 2: viewAnnualSalary(); break;
		case 3: viewAnnualRecord(); break;
		case 4: mainmenu.clear(); mainmenu.autowarp(1); return;
		}
	}
}