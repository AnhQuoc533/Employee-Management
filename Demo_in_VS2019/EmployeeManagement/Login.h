#ifndef _LOGIN_H_
#define _LOGIN_H_

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <conio.h>
#include <Windows.h>
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

int welcome();
void asteriskEncode(string &psw);
int logged();
void clonefile(ifstream&);
int incorrect_psw();
void bar2(int);

#endif