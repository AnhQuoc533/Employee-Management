#include "Date.h"

Date::Date()
{
	time_t now = time(NULL);
	tm cdate;
	localtime_s(&cdate, &now);
	day = cdate.tm_mday;
	month = cdate.tm_mon + 1;
	year = cdate.tm_year + 1900;
}

Date::Date(int y)
{
	year = y;
	month = 1;
	day = 1;
}

Date::Date(int y, int m)
{
	year = y;
	if (m > 12 || m <= 0)
	{
		cout << "Invalid month." << endl;
		exit(0);
	}
	month = m;
	day = 1;
}

int Date::Maxdayintmonth()
{
	int max = 31;
	if (month == 2)
	{
		if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		{
			max = 29;
		}
		else
		{
			max = 28;
		}
	}
	else
	{
		if (month == 4 || month == 6 || month == 9 || month == 11)
		{
			max = 30;
		}
	}
	return max;
}

Date::Date(int y, int m, int d)
{
	year = y;
	if (m > 12 || m <= 0)
	{
		cout << "Invalid month." << endl;
		exit(0);
	}
	month = m;
	int max = this->Maxdayintmonth();
	if (d > max || d <= 0)
	{
		cout << "Invalid day." << endl;
		exit(0);
	}
	day = d;
}

Date Date::Tomorrow()
{
	int maxd = this->Maxdayintmonth();
	Date nextd;
	nextd.day = day + 1;
	nextd.month = month;
	nextd.year = year;
	if (day == maxd)
	{
		nextd.day = 1;
		nextd.month = month + 1;
		if (month == 12)
		{
			nextd.month = 1;
			nextd.year = year + 1;
		}
	}
	return nextd;
}

Date Date::Yesterday()
{
	Date pred;
	pred.day = day - 1;
	pred.month = month;
	pred.year = year;
	if (day == 1)
	{
		pred.month = month - 1;
		if (month == 1)
		{
			pred.month = 12;
			pred.year = year - 1;
		}
		pred.day = pred.Maxdayintmonth();
	}
	return pred;
}

int Date::Comparewith(const Date& D)
{
	if (year > D.year)
	{
		return 1;
	}
	else
	{
		if (year < D.year)
		{
			return -1;
		}
		else
		{
			if (month > D.month)
			{
				return 1;
			}
			else
			{
				if (month < D.month)
				{
					return -1;
				}
				else
				{
					if (day > D.day)
					{
						return 1;
					}
					else
					{
						if (day < D.day)
						{
							return -1;
						}
						else
						{
							return 0;
						}
					}
				}
			}
		}
	}
}

bool Date::operator==(const Date& D)
{
	if (this->Comparewith(D) == 0)
	{
		return true;
	}
	return false;
}

bool Date::operator!=(const Date& D)
{
	if (this->Comparewith(D) == 0)
	{
		return false;
	}
	return true;
}

bool Date::operator>=(const Date& D)
{
	if (this->Comparewith(D) == 1 || this->Comparewith(D) == 0)
	{
		return true;
	}
	return false;
}

bool Date::operator>(const Date& D)
{
	if (this->Comparewith(D) == 1)
	{
		return true;
	}
	return false;
}

bool Date::operator<=(const Date& D)
{
	if (this->Comparewith(D) == -1 || this->Comparewith(D) == 0)
	{
		return true;
	}
	return false;
}

bool Date::operator<(const Date& D)
{
	if (this->Comparewith(D) == -1)
	{
		return true;
	}
	return false;
}

Date Date::operator+(const int a)
{
	int count = 1;
	Date temp1(year, month, day);
	long temp = (long)temp1;
	temp = temp + a;
	temp1.ConverLongtoDate(temp);
	/*Date temp2;
	while (count <= a)
	{
		temp2=temp1.Tomorrow();
		count++;
		temp1 = temp2;
	}*/
	return temp1;
}

Date Date::operator-(const int a)
{
	int count = 1;
	Date temp1(year, month, day);
	long temp = (long)temp1;
	temp = temp - a;
	temp1.ConverLongtoDate(temp);
	/*Date temp2;
	while (count <= a)
	{
		temp2 = temp1.Yesterday();
		count++;
		temp1 = temp2;
	}*/
	return temp1;
}

Date& Date::operator++()
{
	Date temp = this->Tomorrow();
	year = temp.year;
	month = temp.month;
	day = temp.day;
	return *this;
}

Date Date::operator++(int)
{
	Date temp1(year, month, day);
	Date temp2 = this->Tomorrow();
	year = temp2.year;
	month = temp2.month;
	day = temp2.day;
	return temp1;
}

Date& Date::operator--()
{
	Date temp = this->Yesterday();
	year = temp.year;
	month = temp.month;
	day = temp.day;
	return *this;
}

Date Date::operator--(int)
{
	Date temp1(year, month, day);
	Date temp2 = this->Yesterday();
	year = temp2.year;
	month = temp2.month;
	day = temp2.day;
	return temp1;
}

ostream& operator<<(ostream& ost, const Date& D)
{
	if (D.day < 10)
	{
		ost << "0" << D.day;
	}
	else
	{
		ost << D.day;
	}
	if (D.month < 10)
	{
		ost << "/0" << D.month;
	}
	else
	{
		ost << "/" << D.month;
	}
	ost << "/" << D.year;
	return ost;
}

istream& operator>>(istream& ist, Date& D)
{
	do
	{
		cout << "Input year: ";
		cin >> D.year;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(2000, '\n');
			cout << "Invalid year. Please input again." << endl;
			D.year = -1;
		}
	} while (D.year == -1);
	do
	{
		cout << "Input month (from 1 to 12): ";
		cin >> D.month;
		if (cin.fail() || D.month > 12 || D.month <= 0)
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(2000, '\n');
				D.month = 0;
			}
			cout << "Invalid month. Please input again." << endl;
		}
	} while (D.month > 12 || D.month <= 0);
	int maxd = D.Maxdayintmonth();
	do
	{
		cout << "Input day (from 1 to " << maxd << "): ";
		cin >> D.day;
		if (cin.fail() || D.day > maxd || D.day <= 0)
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(2000, '\n');
				D.day = 0;
			}
			cout << "Invalid day. Please input again." << endl;
		}
	} while (D.day > maxd || D.day <= 0);
	return ist;
}

Date::operator int()
{
	int count = 0;
	Date setd(year, 1, 1);
	while (setd.month < month)
	{
		count = count + setd.Maxdayintmonth();
		setd.month++;
	}
	count = count + day - 1;
	return count;
}

Date::operator long()
{
	long count = 0;
	Date setd(1, 1, 1);
	while (setd.year < year)
	{
		if (setd.year % 4 == 0 && setd.year % 100 != 0 || setd.year % 400 == 0)
		{
			count = count + 366;
		}
		else
		{
			count = count + 365;
		}
		setd.year++;
	}
	while (setd.month < month)
	{
		count = count + setd.Maxdayintmonth();
		setd.month++;
	}
	count = count + day - 1;
	return count;
}

void Date::ConverLongtoDate(const long a)
{
	long count = a;
	year = 1;
	month = 1;
	day = 1;
	while (count >= 365)
	{
		if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		{
			count = count - 366;
		}
		else
		{
			count = count - 365;
		}
		year++;
	}
	while (count >= this->Maxdayintmonth())
	{
		count = count - this->Maxdayintmonth();
		month++;
	}
	day = day + count;
}

Date& Date::operator+=(const int a)
{
	Date tempd(year, month, day);
	long temp = (long)tempd;
	temp = temp + a;
	tempd.ConverLongtoDate(temp);
	year = tempd.year;
	month = tempd.month;
	day = tempd.day;
	return *this;
}

Date& Date::operator-=(const int a)
{
	Date tempd(year, month, day);
	long temp = (long)tempd;
	temp = temp - a;
	tempd.ConverLongtoDate(temp);
	year = tempd.year;
	month = tempd.month;
	day = tempd.day;
	return *this;
}

Date& Date::stoDate(string str)
{
	int index = 0, d = 0, m = 0, y = 0, n = (int)str.length();
	string tempd, tempm, tempy;
	for (index; index < n; index++)
	{
		if (str[index] == '/')
		{
			index++;
			break;
		}
		else tempd += str[index];
	}
	d = stoi(tempd);
	for (index; index < n; index++)
	{
		if (str[index] == '/')
		{
			index++;
			break;
		}
		else tempm += str[index];
	}
	m = stoi(tempm);
	for (index; index < n; index++)
	{
		tempy += str[index];
	}
	y = stoi(tempy);
	Date aDate(y, m, d);
	*this = aDate;
	return *this;
}

string Date::toStr()
{
	string str;
	if (day < 10)
	{
		str += '0';
	}
	str.append(to_string(day));
	if (month < 10)
	{
		str += '0';
	}
	str.append(to_string(month));
	if (year < 1000)
	{
		str.append("0");
	}
	if (year < 100)
	{
		str.append("0");
	}
	if (year < 10)
	{
		str.append("0");
	}
	str.append(to_string(year));
	return str;
}