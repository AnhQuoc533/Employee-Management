#ifndef _EMPLOYEE_MANAGEMENT_H_
#define _EMPLOYEE_MAnAGEMENT_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "DIYgraphic.h"
#include "Date.h"
#include "Login.h"
using namespace std;

class Infor {
private:
	Date DoB;
	int ID = 0;
	int No = 0;
	string Name = "";
	string Phone = "";
	string Address = "";
	char Gender = ' ';
	Account ACC;
public:
	Infor() {}
	Infor(Account);
	int getID() { return ID; }
	int getNo() { return No; }
	string getName() { return Name; }

	void LoadInforfrom(ifstream& fload);
	void InputInfor();
	void EditInfor();
	void OutputInfor();

	friend class Staff;
};

class Record {
private:
	vector<int*> records;
	string filename;
	int nCol;
	void reload(string recordName);
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
};

class Employee {
private:
	Infor EInfor;
	double Salary = 0;
	int logday, logmonth, logyear;
	bool record[31];
	void boardsetup();
public:
	Employee();
	Employee(Account);
	string employee_name();
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
	void load_profile();
public:
	Staff(Account);
	~Staff() { delete employeeRecords; }
	void view_profile();
	void section();
	string staff_name();
	//INFORMATION
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
	void Manage_Infor_Menu();
	//RECORD
	void createRecords();
	void editRecordOfAnEmployee();
	void removeRecords();
	void importRecords();
	void addRecord(); // no implementation
	void editRecord(); // no implementation
	void clearRecordOfAnEmployee();
	void viewRecords();
	void RecordMenu();
	void viewSalaryTable();
	void Manage_Record_Menu();
};

#endif