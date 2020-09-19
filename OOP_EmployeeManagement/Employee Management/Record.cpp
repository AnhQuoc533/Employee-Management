#include"Employee_Management.h"

Record::Record()
{
	Date today;
	ifstream fin;
	int* p;
	filename = "Record-" + (today.toStr()).substr(2, 2) + "-" + (today.toStr()).substr(4, 4) + ".txt";
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
	fin.close();
}

Record::Record(string recordName)
{
	Date day(stoi(recordName.substr(3, 4)), stoi(recordName.substr(0, 2)), 1);
	ifstream fin;
	int* p;
	filename = "Record-" + recordName + ".txt";
	fin.open(filename);
	string str, tok;
	istringstream iss;
	nCol = day.Maxdayintmonth() + 1;
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
	fin.close();
}

Record::~Record()
{
	ofstream fout;
	int size = (int)records.size();
	if (size == 0)
		return;
	fout.open(filename);
	if (!fout.is_open())
	{
		fout.close();
		outputbox.display("Cannot save record data.\nCurrent data is now backed up in tmp.txt");
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
	int size = (int)records.size();
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

void Record::newBlank(int ID)
{
	int* p = new int[nCol]();
	p[0] = ID;
	records.push_back(p);
}

void Record::clearData()
{
	int size = (int)records.size();
	for (int i = 0; i < size; ++i)
	{
		delete[] records[i];
	}
	records.clear();
}

void Record::view(int index)
{
	graphical_box temp;
	cout << setw(10) << records[index][0] << setw(2) << (char)179;
	for (int i = 1; i < nCol; ++i)
	{
		cout << setw(5);
		if (records[index][i])
		{
			temp.charColorate(GOOD);
			cout << char(251);
		}
		else
		{
			temp.charColorate(BAD);
			cout << "x";
		}
	}
	temp.charColorate(WHITE);
	cout << endl;
}

void Record::remove(int index)
{
	delete[] records[index];
	records.erase(records.begin() + index);
}

int Record::calcSalary(int index)
{
	int salary = 0;
	for (int i = 1; i < nCol; ++i)
	{
		salary += records[index][i] * 300000;
	}
	return salary + addition(records[index][0]);
}

int Record::addition(int id) {
	int bonus = 0;
	string tmp;
	ifstream f("Comment.txt");
	if (f.is_open()) {
		while (f.good()) {
			getline(f, tmp, ',');
			if (tmp == month_record()) {
				getline(f, tmp, ',');
				if (tmp == to_string(id)) {
					getline(f, tmp, ',');
					bonus += stoi(tmp);
					getline(f, tmp);
				}
				else
					getline(f, tmp);
			}
			else
				getline(f, tmp);
		}
		f.close();
		return bonus;
	}
	else
		return 0;
}