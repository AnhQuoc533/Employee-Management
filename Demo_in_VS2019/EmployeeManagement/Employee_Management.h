#ifndef _EMPLOYEE_MANAGEMENT_H_
#define _EMPLOYEE_MAnAGEMENT_H_

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include"Date.h"
using namespace std;

class Infor {
private:
	Date DoB;
	int ID;
	string Name;
	//Login or Account ACC;
public:
	//getter:
	Date getDoB() { return DoB; }
	int getID() { return ID; }
	string getName() { return Name; }
	//Login or Account getACC() { return ACC; }
	//setter:
	void setDoB(Date& aDate) { DoB = aDate; }
	void setID(int id) { ID = id; }
	void setName(string name) { Name = name; }
	//void setACC(Login or Account& acc) { ACC=acc; }
};

class Employee {
private:
	Infor EInfor;
	int record;
	double Salary;
public:
	Date getDoB() { return EInfor.getDoB(); }
	int getID() { return EInfor.getID(); }
	string getName() { return EInfor.getName(); }
	double getSalary() { return Salary; }
	void setDoB(Date& dob) { EInfor.setDoB(dob); }
	void setID(int id) { EInfor.setID(id); }
	void setName(string name) { EInfor.setName(name); }
	void setSalary(double salary) { Salary = salary; }
};

class Staff {
private:
	Infor StInfor;
	vector<Employee> ListEmpl;
public:
	void ImportListEmpfromCsv(ifstream& fload);
	// StaffMenu();
};


#endif
