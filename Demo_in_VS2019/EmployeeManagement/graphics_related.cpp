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

void graphical_menu::display(int select, int width)
{
	istringstream iss(content);
	string tok;
	getline(iss, tok, '\n');
	int line_offset = 0;
	while (tok != "")
	{
		warp(x, y + line_offset);
		if (line_offset == select)
		{
			SetConsoleTextAttribute(console, 15 | BACKGROUND_BLUE);
			for (int i = 0; i < width; i++) cout << " ";
			warp(x, y + line_offset);
			cout << tok << endl;
		}
		else
		{
			charColorate(0xF);
			for (int i = 0; i < width; i++) cout << " ";
			warp(x, y + line_offset);
			cout << tok << endl;
		}
		getline(iss, tok, '\n');
		line_offset++;
	}
	charColorate(0xF);
}

void graphical_menu::formoutline(int b, int color)
{
	charColorate(color);
	char hl = 196, vl = 179, c1 = 218, c2 = 191, c3 = 192, c4 = 217;
	if (b) hl = 205, vl = 186, c1 = 201, c2 = 187, c3 = 200, c4 = 188;
	for (int i = 1; i < w; i++)
	{
		warp(x + i, y); cout << hl;
		warp(x + i, y + h); cout << hl;
	}
	for (int i = 1; i < h; i++)
	{
		warp(x, y + i); cout << vl;
		warp(x + w, y + i); cout << vl;
	}
	warp(x, y); cout << c1;
	warp(x + w, y); cout << c2;
	warp(x, y + h); cout << c3;
	warp(x + w, y + h); cout << c4;
}