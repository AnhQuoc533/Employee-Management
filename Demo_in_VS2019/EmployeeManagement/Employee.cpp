#include"Employee_Management.h"

Employee::Employee()
{
	Infor anInfor;
	EInfor = anInfor;
	Salary = 0;
	// for testing
	EInfor.setID(19127109);
	time_t now = time(0);	tm cdate;
	localtime_s(&cdate, &now);
	logday = cdate.tm_mday;
	logmonth = cdate.tm_mon + 1;
	logyear = cdate.tm_year + 1900;
}

void Employee::View_Infor_Empl()
{
	EInfor.OutputInfor();
	//cout << "Salary: " << getSalary() << endl;
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
			//string s, tok; getline(fi, s);
			//istringstream iss(s);
			//getline(iss, tok, ',');
			//getline(iss, tok, ',');
			//if (stoi(tok) == EInfor.getID())
			//{
			//	iss.str(s);
			//	getline(iss, tok, ','); EInfor.setNo(stoi(tok));
			//	getline(iss, tok, ','); EInfor.setID(stoi(tok));
			//	getline(iss, tok, ','); EInfor.setName(tok);
			//	getline(iss, tok, ','); EInfor.setGender(tok[0]);
			//	getline(iss, tok, ','); //EInfor.setDoB({ 0,0,0 });
			//	getline(iss, tok, ','); EInfor.setPhone(tok);
			//	getline(iss, tok, ','); EInfor.setAddress(tok);
			//}
		}		
		fi.close();
	}
	if (fail) cout << "'Load failed!\n";
}

void Employee::loadEmplRecord(int month)
{
	string file = "Records-";
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
				for (int i = 0; i < 31; i++)
				{
					getline(iss, tok, ',');
					record[i] = stoi(tok);
				}
				break;
			}
		}
		fi.close();
		outputbox.display("Load successfully!");
	}
	else outputbox.display("Can't load record for check-in.");
}

void Employee::checkin()
{
	string file = "Records-";
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
				int offset = input.find(",");
				int i = offset + (logday * 2 - 1);
				input[i] = '1';				
			}
			save.push_back(input);
		}
		fi.close();
		ofstream fo(file);
		for (int i = 0; i < save.size(); i++) fo << save[i] << endl;
		fo.close();
		outputbox.display("Checkin successfully!");
	}
	else cout << "Can't load record for check-in.\n";
}

void Employee::viewCheckin(int month)
{
	loadEmplRecord(month);
	int sep = 5;
	cout << "Month: " << month << left << setw(10) << "\nDay";
	for (int i = 0; i < 31; i++) cout << setw(sep) << i + 1;

	cout << setw(10) << left << "\nStatus: ";
	for (int i = 0; i < 31; i++)
	{
		cout << setw(sep);
		if (record[i]) cout << "Yes"; else cout << "No";
	}
}

void Employee::viewCheckin()
{
	viewCheckin(logmonth);
}

void Employee::viewAnnualRecord()
{
	for (int i = 1; i < 13; i++)
	{
		viewCheckin(i);
	}
}
