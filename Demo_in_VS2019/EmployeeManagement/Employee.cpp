#include"Employee_Management.h"

//Thanh co gop y gi, them bot ham nao cho an toan, cho on hon thi ong noi tui hoac hung truoc nha.
//Tai co cac ham tui lam truoc de tien lay va gan du lieu cho ben staff a.
//Duoc thi coi nhu tui tui nho ong lam gium cac ham nay de de dang lam viec hon:))
Employee::Employee()
{
	Infor anInfor;
	EInfor = anInfor;
	Salary = 0;
}
void Employee::inputEmpl()
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
	setID(id);
	cin.ignore(1);
	string temp;
	cout << "Input the name: ";
	getline(cin, temp);
	setName(temp);
	char gender;
	do
	{
		cout << "Input the gender: ";
		gender = getchar();
		if (gender != 'M' && gender != 'F')
		{
			cout << "Invalid gender. Please input again." << endl << endl;
		}
	} while (gender != 'M' && gender != 'F');
	setGender(gender);
	Date aDate;
	cout << "Input date of birth:" << endl;
	cin >> aDate;
	setDoB(aDate);
	cin.ignore(1);
	cout << "Input phonenumber: ";
	getline(cin, temp);
	setPhone(temp);
	cout << "Input address: ";
	getline(cin, temp);
	setAddress(temp);
	setSalary(0.0);
}

void Employee::outputEmpl()
{
	cout << "ID: " << getID() << endl;
	cout << "Name: " << getName() << endl;
	cout << "Gender: " << getGender() << endl;
	cout << "Date of birth: " << getDoB() << endl;
	cout << "Phone: " << getPhone() << endl;
	cout << "Address: " << getAddress() << endl;
	//cout << "Salary: " << getSalary() << endl;
}