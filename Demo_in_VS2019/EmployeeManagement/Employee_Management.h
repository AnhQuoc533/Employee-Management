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
	int role;
public:
	string getUsername() { return Username; }
	string getPassword() { return Password; }
	int get_role() { return role; }

	void asteriskEncode();
	bool login();
	bool openfiles();
	int track(ifstream &f);
	void changeData(ofstream &out);
	void changepswInFile();
	void changepsw();
	void StaffLogin(int choice);
	void EmployeeLogin(int choice);

	friend class Staff;
	friend class Infor;
};

class Infor {
private:
	int No = 0;
	Date DoB(1900, 1, 1);
	int ID = 0;
	string Name = "";
	string Phone = "";
	string Address = "";
	char Gender = ' ';
	Account ACC;
public:
	//getter:
	int getNo() { return No; }
	int getID() { return ID; }
	string getName() { return Name; }
	string getUsername() { return ACC.getUsername(); }
	string getPassword() { return ACC.getPassword(); }
	void LoadInforfrom(ifstream& fload);
	void InputInfor();
	void EditInfor();
	void OutputInfor();
	friend class Staff;
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
	void newBlank(int ID);
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
	bool loadEmplRecord(int month);
	void checkin();
	void viewCheckin(int month);
	void viewCheckin();
	void viewAnnualRecord();
	void viewAnnualSalary() {}
	void EmployeeMenu();
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
	void editRecordOfAnEmployee();
	void removeRecords();
	void importRecords();
	void addRecord(); // no implementation
	void editRecord(); // no implementation
	void clearRecordOfAnEmployee();
	void viewRecords();
	void viewSalaryTable();
};

#endif
