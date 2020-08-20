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
};

class Employee {
private:
	Infor EInfor;
	//int record;
	double Salary;
public:
	Employee();
	//getter:
	int getNo() { return EInfor.getNo(); }
	Date getDoB() { return EInfor.getDoB(); }
	int getID() { return EInfor.getID(); }
	string getName() { return EInfor.getName(); }
	string getPhone() { return EInfor.getPhone(); }
	string getAddress() { return EInfor.getAddress(); }
	char getGender() { return EInfor.getGender(); }
	double getSalary() { return Salary; }
	//setter:
	void setNo(int no) { EInfor.setNo(no); }
	void setDoB(Date& dob) { EInfor.setDoB(dob); }
	void setID(int id) { EInfor.setID(id); }
	void setName(string name) { EInfor.setName(name); }
	void setPhone(string phone) { EInfor.setPhone(phone); }
	void setAddress(string address) { EInfor.setAddress(address); }
	void setGender(char gender) { EInfor.setGender(gender); }
	void setSalary(double salary) { Salary = salary; }
	void inputEmpl();
	void outputEmpl();
};

class Staff {
private:
	Infor StInfor;
	vector<Employee> ListEmpl;
public:
	Staff();
	void ImportListEmpfromCsv();
	void Add_an_Empl_Manually();
	void Edit_Infor_of_an_Empl();
	void View_list_of_Empl();
	void View_Infor_of_an_Empl();
	void View_check_in_of_an_employee() {}//not touch yet
	void Reset_password_for_empl() {}//not touch yet
	void StaffMenu();
};


#endif
