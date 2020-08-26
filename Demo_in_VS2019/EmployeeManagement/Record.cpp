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
	int size = records.size();
	fout.open(filename);
	if (!fout.is_open())
	{
		fout.close();
		cout << "Cannot save data.\n";
		cout << "Current data is now backed up in \"tmp.txt\"\n";
		fout.open("tmp.txt");
	}
	for (int i = 0; i < size; i++)
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

void Record::import(ifstream& fin)
{
	int* p;
	string str, tok;
	istringstream iss;
	getline(fin, str);
	while (getline(fin, str))
	{
		iss.str("");
		iss.clear();
		iss.str(str);
		getline(iss, tok, ',');
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

void Record::edit(int index, unsigned day, bool status)
{
	records[index][day] = status;
}

void Record::clear(int index)
{
	int tmp = records[index][0];
	delete[] records[index];
	records[index] = new int[nCol]();
	records[index][0] = tmp;
}

int Record::getIndex(int ID)
{
	int size = records.size();
	for (int i = 0; i < size; ++i)
	{
		if (records[i][0] == ID)
		{
			return i;
		}
	}
	return -1;
}

void Record::newBlank(int* arr, int n)
{
	int* p;
	for (int i = 0; i < n; ++i)
	{
		p = new int[nCol]();
		p[0] = arr[i];
		records.push_back(p);
		p = 0;
	}
}
