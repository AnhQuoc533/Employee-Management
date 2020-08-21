#include"Employee_Management.h"

Record::Record()
{
	Date today;
	ifstream fin;
	int* p;
	filename = "Records-" + (today.toStr()).substr(2, 2) + "-" + (today.toStr()).substr(4, 4) + ".txt";
	fin.open(filename);
	string str, tok;
	istringstream iss;
	nCol = today.Maxdayintmonth() + 1;
	if (fin.is_open())
	{
		while (getline(fin, str))
		{
			iss.str("");
			iss.clear();
			iss.str(str);
			p = new int[nCol];
			for (int i = 0; i < nCol; i++)
			{
				getline(iss, tok, ',');
				p[i] = stoi(tok);
			}
			records.push_back(p);
			p = 0;
		}
	}
}

Record::~Record()
{
}

int* Record::getRecord(int ID)
{
	return nullptr;
}
