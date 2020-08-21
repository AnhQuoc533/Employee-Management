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
void graphics_abstract::evaluate(string bstr, int& m, int& n)
{
	const char* s = bstr.c_str();
	char* p, * ntok = 0, * str = new char[strlen(s) + 1];
	strcpy_s(str, strlen(s) + 1, s);
	p = strtok_s(str, "\n", &ntok);
	m = 0; n = 0;
	while (p)
	{
		int l = strlen(p);
		if (l > m) m = l;
		p = strtok_s(0, "\n", &ntok);
		n++;
	}
	delete[] str;
}