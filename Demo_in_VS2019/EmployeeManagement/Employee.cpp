#include"Employee_Management.h"

Employee::Employee()
{
	Infor anInfor;
	EInfor = anInfor;
	Salary = 0;
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
