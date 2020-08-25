#include"Employee_Management.h"

Record::Record()
{
	Date today;
	ifstream fin;
	bool* p;
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
			p = new bool[nCol];
			for (int i = 0; i < nCol; i++)
			{
				getline(iss, tok, ',');
				p[i] = stoi(tok);
			}
			records.push_back(p);
			p = 0;
		}
	}
	else
	{
		cout << "Cannot not load data.\n";
		cout << "You can now create new records\n";
	}
	fin.close();
}

Record::~Record()
{
	ofstream fout;
	fout.open(filename);
	if (!fout.is_open())
	{
		fout.close();
		cout << "Cannot save data.\n";
		cout << "Current data is now backed up in \"tmp.txt\"\n";
		fout.open("tmp.txt");
	}
	for (int i = 0; i < records.size(); i++)
	{
		fout << records[i][0];
		for (int j = 1; j < nCol; j++)
		{
			fout << "," << records[i][j];
		}
		delete[] records[i];
		records[i] = nullptr;
		fout << endl;
	}
	fout.close();
}

void Record::edit(int ID, unsigned day, bool status)
{
	for (int i = 0; i < records.size(); ++i)
	{
		if (records[i][0] == ID)
		{
			records[i][day] = status;
			return;
		}
	}
}

int* Record::getRecord(int ID)
{
	return nullptr;
}
