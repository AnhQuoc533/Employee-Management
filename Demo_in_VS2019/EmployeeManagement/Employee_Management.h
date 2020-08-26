#ifndef _EMPLOYEE_MANAGEMENT_H_
#define _EMPLOYEE_MAnAGEMENT_H_

#include<iostream>
#include<vector>
#include<fstream>
#include"Date.h"
#include<sstream>
#include<iomanip>
#include "DIYgraphic.h"
using namespace std;

class Account {
private:
	string Username;
	string Password;
public:
	void setUsername(string username) { Username = username; }
	void setPass(string password) { Password = password; }
};

class Infor {
private:
	int No;
	Date DoB;
	int ID;
	string Name;
	string Phone;
	string Address;
	char Gender;
	Account ACC;
public:
	//getter:
	Infor();
	int getNo() { return No; }
	Date getDoB() { return DoB; }
	int getID() { return ID; }
	string getName() { return Name; }
	string getPhone() { return Phone; }
	string getAddress() { return Address; }
	char getGender() { return Gender; }
	//setter:
	void setNo(int no) { No = no; }
	void setDoB(Date& aDate) { DoB = aDate; }
	void setID(int id) { ID = id; }
	void setName(string name) { Name = name; }
	void setPhone(string phone) { Phone=phone; }
	void setAddress(string address) { Address = address; }
	void setGender(char gender) { Gender = gender; }
	void setUS(string username) { ACC.setUsername(username); }
	void setPASS(string password) { ACC.setPass(password); }
	void LoadInforfrom(ifstream& fload);
	void InputInfor();
	void EditInfor(int checkifBeChanged);
	void OutputInfor();
};

class Record
{
public:
	Record();
	~Record();
	void import(ifstream& fin);
	void edit(int index, unsigned day, bool status);
	void clear(int index);
	int getIndex(int ID);
	bool hasData() { return records.size(); }
	void newBlank(int* arr, int n);
	void clearData();
private:
	vector<int*> records;
	string filename;
	int nCol;
};

class Employee {
private:
	Infor EInfor;
	//int record;
	double Salary = 0;
public:
	Employee();
	void View_Infor_Empl();
	void loadEmplData();
	friend class Staff;
};

class Staff {
private:
	Infor StInfor;
	vector<Employee> ListEmpl;
	Record* employeeRecords;
public:
	Staff();
	~Staff() { delete employeeRecords; }
	void ImportListEmpfromCsv();
	void SaveInfortoTextfile(int& checkifBeChanged);
	void LoadfromTextfile();
	int findEmplWithID(int id);
	void Add_an_Empl_Manually(int& checkifBeChanged);
	void Create_List_Empl_Manually(int& checkifBeChanged);
	void Edit_Infor_of_an_Empl(int& checkifBeChanged);
	void Remove_an_Empl(int& checkifBeChanged);
	void View_list_of_Empl();
	void View_Infor_of_an_Empl();
	void View_Profile();
	void Reset_password_for_empl();
	void Manage_Employee_Menu();
	void StaffMenu();
	void createRecords();
	void editRecords();
	void removeRecords();
	void importRecords();
	void addRecord();
	void editRecord();
	void clearRecordOfAnEmployee();
	void viewRecords();
};


#endif
