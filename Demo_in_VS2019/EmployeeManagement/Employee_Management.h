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
	string getUsername() { return Username; }
	string getPassword() { return Password; }
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
	string getUsername() { return ACC.getUsername(); }
	string getPassword() { return ACC.getPassword(); }
	//setter:
	void setNo(int no) { No = no; }
	void setID(int id) { ID = id; }
	void setUS(string username) { ACC.setUsername(username); }
	void setPASS(string password) { ACC.setPass(password); }
	void LoadInforfrom(ifstream& fload);
	void InputInfor();
	void EditInfor();
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
	void view(int index);
	void remove(int index);
private:
	vector<int*> records;
	string filename;
	int nCol;
};

class Employee {
private:
	Infor EInfor;
	double Salary = 0;
	int logday, logmonth, logyear;
	bool record[31];
public:
	Employee();
	void View_Infor_Empl();
	void loadEmplData(Account);
	void loadEmplRecord(int month);
	void checkin();
	void viewCheckin(int month);
	void viewAnnualRecord();
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
	void SaveInfortoTextfile();
	void LoadfromTextfile();
	int findEmplWithID(int id);
	void Add_an_Empl_Manually();
	void Create_List_Empl_Manually();
	void Edit_Infor_of_an_Empl();
	void Remove_an_Empl();
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
	void addRecord(); // no implementation
	void editRecord(); // no implementation
	void clearRecordOfAnEmployee();
	void viewRecords();
	void viewSalaryTable();
};


#endif
