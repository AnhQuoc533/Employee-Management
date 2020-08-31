#ifndef _LOGINHEADER_H_
#define _LOGINHEADER_H_

#include "Date.h"
#include "Employee_Management.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <conio.h>
#include <Windows.h>
using namespace std;

class User {
	string username, password;
	int role;
};
class StdLogin
{
	int ID;
	string fullname, gender, classname;
	Date DoB;
};
class Staff {
	string fullname;
	int gender;
};

void asteriskEncode(string &psw);
bool login(User &A);
bool openfiles(User &A, string name, string psw);
int track(ifstream &f, int role, User &A, string name, string psw);
void getinfoStaff(User A, Staff &admin);
void getinfoStd(User A, StdLogin &std);
void changeData(User A, ofstream &out);
void changepswInFile(User A);
void changepsw(User &A);
void changepswInClassFile(User A, string classname);
void changepswStd(User &A, string classname);
void StaffLog(User &A, int choice);
void StdLog(User &A, int choice);
int welcome();
void section();
void bar2(int n);
int logged();
void clonefile(ifstream &in);
#endif