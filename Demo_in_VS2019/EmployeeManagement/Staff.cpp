#include"Employee_Management.h"

void Staff::ImportListEmpfromCsv(ifstream& fload)
{
	string filename;
	string temp;
	Employee anEmpl;
	int tempd = 0, tempm = 0, tempy = 0;
	cout << "Input the name of the csv file: ";
	getline(cin, filename);
	fload.open(filename);
	if (!fload.is_open())
	{
		cout << "Cannot find the file " << filename << "." << endl;
		cout << "Maybe it was deleted or changed the location." << endl;
		return;
	}
	else
	{
		cout << "Openned file " << filename << "successed." << endl;
		cout << "Starting load its data to the program...." << endl;
		while (getline(fload, temp, ','))
		{
			anEmpl.setID(stoi(temp));
			getline(fload, temp, ',');
			anEmpl.setName(temp);
			getline(fload, temp, '/');
			tempd = stoi(temp);
			getline(fload, temp, '/');
			tempm = stoi(temp);
			getline(fload, temp, ',');
			tempy = stoi(temp);
			Date tempDate(tempy, tempm, tempd);
			anEmpl.setDoB(tempDate);
			getline(fload, temp);
			anEmpl.setSalary(stod(temp));
		}
		fload.close();
	}
}