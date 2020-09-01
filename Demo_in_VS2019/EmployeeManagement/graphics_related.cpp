#include "Employee_Management.h"

graphical_textbox outputbox;
int scrw, scrh;

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
	if (s[s.length()] != '\n') s += '\n';
	istringstream iss(s);
	string tok;
	getline(iss, tok, '\n');
	m = 0; n = 1;
	while (tok != "")
	{
		int l = (int)tok.length();
		if (l > m) m = l;
		getline(iss, tok, '\n');
		n++;
	} m += 2;
}

void graphics_abstract::turnCursor(bool on)
{
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = on;
	cursor.dwSize = 1;
	SetConsoleCursorInfo(console, &cursor);
}

graphical_menu::graphical_menu()
{
	x = y = w = h = border = 0;
	title = content = "";
}

void graphical_menu::init(int posx, int posy, int width, int height)
{
	x = posx; y = posy;
	w = width; h = height;
}

void graphical_menu::set(string t, string s)
{
	title = t; content = s;
}

void graphical_menu::resize(int width, int height)
{
	w = width; h = height;
	warp(x, y + h-1);
	for (int i = 0; i < w; i++) cout << " ";
	warp(x, y + h-1);
}

void graphical_menu::display(string title, string content)
{
	istringstream iss(content);
	string tok;
	getline(iss, tok, '\n');
	int line_offset = 0, x = this->x + 1, y = this->y + 1;
	for (int j = 0;j<h-1;j++)
	{
		warp(x, y + line_offset);
		if (line_offset == select)
		{
			SetConsoleTextAttribute(console, 15 | BACKGROUND_BLUE);
			for (int i = 0; i < w-1; i++) cout << " ";
			warp(x, y + line_offset);
			cout << tok << endl;
		}
		else
		{
			charColorate(0xF);
			for (int i = 0; i < w-1; i++) cout << " ";
			warp(x, y + line_offset);
			cout << tok << endl;
		}
		getline(iss, tok, '\n');
		line_offset++;
	}
	charColorate(0xF);
}

void graphical_menu::formoutline(int color)
{
	charColorate(color);
	char hl = (char)196, vl = (char)179, c1 = (char)218, c2 = (char)191, c3 = (char)192, c4 = (char)217;
	if (border) hl = char(205), vl = char(186), c1 = char(201), c2 = char(187), c3 = char(200), c4 = char(188);
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

int graphical_menu::operate()
{
	screenctrl* screen = screenctrl::instance();
	turnCursor(0);
	evaluate(content, w, h);
	if (x + w > screen->getbufferw())
	{
		x = orix;
		y += h + 2;
	}
	formoutline(TONE2);
	select = 0;

	while (1)
	{
		display();
		charColorate(TONE2);
		warp(x+1, y - border);  cout << title;
		char c = _getch();
		if (c == -32)
		{
			c = _getch();
			switch (c)
			{
			case 72: select = (select > 0) ? select - 1 : 0; break;
			case 80: select = (select < h - 2) ? select + 1 : h - 2; break;
			}
		}
		if ((c >= 48) && (c <= 57))
		{
			int x = c - 48;
			if ((x >= 0) && (x < h)) select = x;
		}
		if (c == '\r')
		{
			charColorate(15);
			turnCursor(1);
			x += w + 2;
			warp(0, 0);
			return select;
		}
	}
}

int graphical_menu::operate(string tit, string con)
{
	title = tit; content = con;
	return operate();
}

graphical_textbox::graphical_textbox()
{
	x = y = w = h = 0;
	select = border = 0;
	content = "";
}

void graphical_textbox::init(int posx, int posy, int width, int height)
{
	x = posx; y = posy;
	w = width; h = height;
}

void graphical_textbox::wipe()
{
	for (int i = 0; i < h - 1; i++)
	{
		warp(x + 1, y + 1 + i);
		for (int j = 0; j < w - 2; j++) cout << " ";
	}
}
void graphical_textbox::display(string s)
{
	s += " ";
	graphical_menu z;
	z.init(x, y, w, h);
	z.formoutline(0xF);
	wipe();	int w = this->w-5;
	warp(x + 1, y + 1);	cout << " * ";
	int delay_time = 50;
	size_t n = s.length();
	for (int i = 0, line_index = 0, chara_count = 0; i < n; i++)
	{
		if (s[i] == '\n')
		{
			line_index++; chara_count = 0;
			warp(x + 1, y + 1 + line_index);
			cout << " * ";
			continue;
		}
		cout << s[i];
		chara_count++;
		if (s[i] == ' ')
		{
			size_t offset = i + (size_t)1;
			size_t location = s.find(' ', offset) - 1;
			if (i!=s.length()-1)
			if (chara_count + location - i > w)
			{
				line_index++; chara_count = 0;
				warp(x + 1, y + 1 + line_index);
				if (line_index > h-2)
				{
					z.resize(this->w, h + 1);
					z.formoutline(0xF);
					warp(x + 1, y + 1 + line_index);
					h++;
				}
				cout << "   ";
			}
		}
		if (i > 5 && GetAsyncKeyState(VK_RETURN) < 0) delay_time = 0;
		Sleep(delay_time);
	}
	if (!delay_time) cin.ignore();
	while (_getch() != 13);
	warp(0, 0);
}

void graphical_textbox::display()
{
	display(content);
}

screenctrl* screenctrl::instance()
{
	if (!inst) inst = new screenctrl;
	return inst;
}

void screenctrl::init(int width, int height)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD newsize;
	RECT r;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND consoleWindow = GetConsoleWindow(),
		window = GetDesktopWindow();

	GetWindowRect(window, &r);
	int xx = r.right / 2 - width / 2,
		yy = r.bottom / 2 - height / 2;
	MoveWindow(consoleWindow, xx, yy, width, height, 1);
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	GetConsoleScreenBufferInfo(console, &csbi);
	newsize.X = csbi.dwSize.X;
	newsize.Y = csbi.srWindow.Bottom - csbi.srWindow.Top+1;//SBInfo.dwSize.Y;
	SetConsoleScreenBufferSize(console, newsize);

	bwidth = csbi.srWindow.Right - csbi.srWindow.Left;
	bheight = csbi.srWindow.Bottom - csbi.srWindow.Top;
}