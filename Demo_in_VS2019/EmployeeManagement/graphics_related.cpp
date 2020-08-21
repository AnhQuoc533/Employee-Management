#include "Employee_Management.h"

void graphics_abstract::warp(int x, int y)
{
	COORD Cursor; Cursor.X = x; Cursor.Y = y;
	SetConsoleCursorPosition(console, Cursor);
}
void graphics_abstract::charColorate(int x)
{
	SetConsoleTextAttribute(console, x);
}
void graphics_abstract::charColorate(int x, int y)
{
	SetConsoleTextAttribute(console, x | y);
}
void graphics_abstract::evaluate(string s, int& m, int& n)
{
	istringstream iss(s);
	string tok;
	getline(iss, tok, '\n');
	m = 0; n = 0;
	while (tok!="")
	{
		int l = tok.length();
		if (l > m) m = l;
		getline(iss, tok, '\n');
		n++;
	}
}