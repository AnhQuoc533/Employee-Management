#ifndef _DATE_H_
#define _DATE_H_

#include<iostream>
#include<Windows.h>
using namespace std;

class Date {
public:
	Date();
	Date(int y);
	Date(int y, int m);
	int Maxdayintmonth();
	Date(int y, int m, int d);
	Date Tomorrow();
	Date Yesterday();
	int Comparewith(const Date& D);
	bool operator==(const Date& D);
	bool operator!=(const Date& D);
	bool operator>=(const Date& D);
	bool operator>(const Date& D);
	bool operator<=(const Date& D);
	bool operator<(const Date& D);
	Date operator+(const int a);
	Date operator-(const int a);
	Date& operator++();
	Date operator++(int);
	Date& operator--();
	Date operator--(int);
	friend ostream& operator<<(ostream& ost, const Date& D);
	friend istream& operator>>(istream& ist, Date& D);
	operator int();
	operator long();
	void ConverLongtoDate(const long a);
	Date& operator+=(const int a);
	Date& operator-=(const int a);
private:
	int month, day, year;
};


#endif
