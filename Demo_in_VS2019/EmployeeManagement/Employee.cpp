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
	EInfor.InputInfor();
	Salary = 0.;
}

void Employee::View_Infor_Empl()
{
	EInfor.OutputInfor();
	//cout << "Salary: " << getSalary() << endl;
}