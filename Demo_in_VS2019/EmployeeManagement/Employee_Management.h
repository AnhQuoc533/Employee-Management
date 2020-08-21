#ifndef _EMPLOYEE_MANAGEMENT_H_
#define _EMPLOYEE_MAnAGEMENT_H_

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include"Date.h"
#include<sstream>
using namespace std;

class Infor {
private:
	int No;
	Date DoB;
	int ID;
	string Name;
	string Phone;
	string Address;
	char Gender;
	//Login or Account ACC;
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
	//Login or Account getACC() { return ACC; }
	//setter:
	void setNo(int no) { No = no; }
	void setDoB(Date& aDate) { DoB = aDate; }
	void setID(int id) { ID = id; }
	void setName(string name) { Name = name; }
	void setPhone(string phone) { Phone=phone; }
	void setAddress(string address) { Address = address; }
	void setGender(char gender) { Gender = gender; }
	//void setACC(Login or Account& acc) { ACC=acc; }
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
	int* getRecord(int ID);
private:
	vector<int*> records;
};

class Employee {
private:
	Infor EInfor;
	//int record;
	double Salary;
public:
	Employee();
	void inputEmpl();
	void editEmplInfor() { EInfor.EditInfor(); }
	void View_Infor_Empl();
	void loadEmplData();
	friend class Staff;
};

class Staff {
private:
	Infor StInfor;
	vector<Employee> ListEmpl;
public:
	Staff();
	void ImportListEmpfromCsv();
	void SavetoTextfile();
	void LoadfromTextfile();
	int findEmplWithID(int id);
	void Add_an_Empl_Manually();
	void Edit_Infor_of_an_Empl();
	void Remove_an_Empl();
	void View_list_of_Empl();
	void View_Infor_of_an_Empl();
	void View_Profile();
	void Reset_password_for_empl() {}//not touch yet
	void Manage_Employee_Menu();
	void StaffMenu();
	/*void createRecords();
	void editRecords();
	void removeRecords();
	void importRecords();
	void addRecord();
	void editRecord();
	void clearRecord();
	void viewRecords();*/
};


#endif
