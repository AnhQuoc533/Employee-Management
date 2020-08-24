#include"Employee_Management.h"

Employee::Employee()
{
	Infor anInfor;
	EInfor = anInfor;
	Salary = 0;
}
void Employee::inputEmpl()
{
	EInfor.InputInfor();
	Salary = 0.;
}

void Employee::View_Infor_Empl()
{
	EInfor.OutputInfor();
	//cout << "Salary: " << getSalary() << endl;
}

void Employee::loadEmplData()
{
	ifstream fi("Employee.txt");
	if (fi)
	{
		while (fi.peek() != EOF)
		{
			string s, tok; getline(fi, s);
			istringstream iss(s);
			getline(iss, tok, ',');
			getline(iss, tok, ',');
			if (stoi(tok) == EInfor.getID())
			{
				iss.str(s);
				getline(iss, tok, ','); EInfor.setNo(stoi(tok));
				getline(iss, tok, ','); EInfor.setID(stoi(tok));
				getline(iss, tok, ','); EInfor.setName(tok);
				getline(iss, tok, ','); EInfor.setGender(tok[0]);
				getline(iss, tok, ','); //EInfor.setDoB({ 0,0,0 });
				getline(iss, tok, ','); EInfor.setPhone(tok);
				getline(iss, tok, ','); EInfor.setAddress(tok);
			}
		}		
		fi.close();
	}
}
