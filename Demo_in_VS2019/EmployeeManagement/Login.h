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
	int role = 1;
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
void asteriskEncode(string&);
int logged();
void clonefile(ifstream&);
int incorrect_psw();
string capitalize_name(string);

#endif