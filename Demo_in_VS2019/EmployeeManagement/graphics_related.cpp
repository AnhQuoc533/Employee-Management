#include "Employee_Management.h"

graphical_textbox outputbox;
graphical_menu mainmenu;
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

int graphics_abstract::getx()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(console, &info);
	return info.dwCursorPosition.X;
}
int graphics_abstract::gety()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(console, &info);
	return info.dwCursorPosition.Y;
}

void graphics_abstract::clearbuffer()
{
	turnCursor(0);
	warp(0, TXTY);
	screenctrl* screen = screenctrl::instance();
	/*for (int i = 0; i < screen->getbufferh() - TXTY - 4; i++)
	{
		for (int j = 0; j < screen->getbufferw(); j++) cout << " ";
		cout << endl;
	}*/
	DWORD written;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(console, &csbi);
	DWORD length = csbi.dwSize.X * (csbi.dwSize.Y-TXTY-5);
	COORD anch{ 0,TXTY };
	FillConsoleOutputCharacter(console, TEXT(' '), length, anch, &written);
	FillConsoleOutputAttribute(console, csbi.wAttributes, length, anch, &written);
	warp(0, TXTY);
	turnCursor(1);	
}

graphical_menu::graphical_menu()
{
	x = getx();	y = gety();
	w = h = border = 0;
	title = content = "";
}

void graphical_menu::init(int posx, int posy, int width, int height)
{
	x = posx; y = posy;
	w = width; h = height;
	box.init(x, y, w, h, border);
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

//void graphical_menu::formoutline(int color)
//{
//	charColorate(color);
//	char hl = (char)196, vl = (char)179, c1 = (char)218, c2 = (char)191, c3 = (char)192, c4 = (char)217;
//	if (border) hl = char(205), vl = char(186), c1 = char(201), c2 = char(187), c3 = char(200), c4 = char(188);
//	for (int i = 1; i < w; i++)
//	{
//		warp(x + i, y); cout << hl;
//		warp(x + i, y + h); cout << hl;
//	}
//	for (int i = 1; i < h; i++)
//	{
//		warp(x, y + i); cout << vl;
//		warp(x + w, y + i); cout << vl;
//	}
//	warp(x, y); cout << c1;
//	warp(x + w, y); cout << c2;
//	warp(x, y + h); cout << c3;
//	warp(x + w, y + h); cout << c4;
//}

int graphical_menu::operate()
{
	screenctrl* screen = screenctrl::instance();
	turnCursor(0);
	evaluate(content, w, h);
	if (title.length() > w) w = (int)title.length()+1;
	if (back)
	{
		back = 0;
		x -= w+2;
	}
	if (x + w > screen->getbufferw())
	{
		x = orix;
		y += h + 2;
	}
	if (halign) x -= w / 2;
	if (valign) y -= h / 2;
	box.init(x, y, w, h, border);
	box.display(TONE2);
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
			lostfocus();
			charColorate(15);
			turnCursor(1);
			if (dynamic) x += w + 2;
			if (willclear)clearbuffer();
			else warp(0, y + h+1);
			return select;
		}
	}
}

int graphical_menu::operate(string tit, string con)
{
	title = tit; content = con;
	return operate();
}

void graphical_menu::clear()
{
	turnCursor(0); if (dynamic) x -= w+2;
	for (int i = 0; i <= h; i++)
	{
		warp(x, y + i);
		for (int j = 0; j <= w; j++) cout << " ";
	}
	turnCursor(1); back = 1;
}

void graphical_menu::lostfocus()
{
	//formoutline(INACT);
	box.display(INACT);
	istringstream iss(content);
	string tok;
	getline(iss, tok, '\n');
	int line_offset = 0, x = this->x + 1, y = this->y + 1;
	for (int j = 0; j < h - 1; j++)
	{
		warp(x, y + line_offset);
		if (line_offset == select)
		{
			SetConsoleTextAttribute(console, 15 | BACKGROUND_INTENSITY);
			for (int i = 0; i < w - 1; i++) cout << " ";
			warp(x, y + line_offset);
			cout << tok << endl;
		}
		else
		{
			charColorate(INACT);
			for (int i = 0; i < w - 1; i++) cout << " ";
			warp(x, y + line_offset);
			cout << tok << endl;
		}
		getline(iss, tok, '\n');
		line_offset++;
	}
	charColorate(INACT);
	warp(this->x + 1, this->y - border);  cout << title;
}

void graphical_menu::setalign(bool hor, bool ver)
{
	halign = hor; valign = ver;
}

graphical_textbox::graphical_textbox()
{
	x = getx(); y = gety();
	w = h = 0;
	select = 0; border = 1;
	content = "";
}

void graphical_textbox::init(int posx, int posy, int width, int height)
{
	x = posx; y = posy;
	w = width; h = height;
	box.init(x, y, w, h, border);
}

void graphical_textbox::wipe()
{
	turnCursor(0);
	for (int i = 0; i < h - 1; i++)
	{
		warp(x + 1, y + 1 + i);
		for (int j = 0; j < w - 2; j++) cout << " ";
	} turnCursor(1);
}
void graphical_textbox::display(string s)
{
	s += " ";
	/*graphical_menu z;
	z.init(x, y, w, h);
	z.formoutline(0xF);*/
	box.display(WHITE);
	wipe();	int w = this->w-5;
	warp(x + 1, y + 1);	cout << " * ";
	int delay_time = 30;
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
					/*z.resize(this->w, h + 1);
					z.formoutline(0xF);*/
					h++;
					box.display(WHITE);
					warp(x + 1, y + 1 + line_index);
				}
				cout << "   ";
			}
		}
		if (i > 5 && GetAsyncKeyState(VK_RETURN) < 0) delay_time = 0;
		Sleep(delay_time);
	}
	if (delay_time==0) cin.ignore();	
	while (_getch() != 13);
	clearbuffer();
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

void graphical_loader::load(int time)
{
	turnCursor(0);
	char bg = (char)219;
	charColorate(WHITE); 
	bool flag = 0;
	if (content[content.length() - 1] == 'e')
	{
		content.erase(content.length() - 1);
		flag = 1;
	}
	warp(x, y - 1); cout << content << "ing...";
	if (flag) content += 'e';
	int breakcount = (rand() % 5)+1;
	int breakpoint = 0;
	warp(x, y);
	for (int i = 0; i < w; i++) cout << bg;
	for (int i = 0; i < w; i++)
	{
		//if (GetAsyncKeyState(VK_RETURN) < 0) cin.ignore();
		int percent = (int)ceil((float)(i + 1) / w * 100);
		if (i == breakpoint)
		{
			Sleep(time * 4);
			if (breakcount > 0)
			{
				breakpoint = rand() % (w - i) + i + 1;
				breakcount--;
			}
		}			
		charColorate(SEMI);	warp(x+i, y);		
		cout << bg;
		if (i < w) charColorate(WHITE);
		warp(x + w + 2, y);
		cout << percent << "%";
		Sleep(time*i/breakpoint);
	}	
	warp(x, y - 1); cout << content << " completed!";
	charColorate(GOOD);
	warp(x, y);		for (int i = 0; i < w; i++) cout << bg;
	Sleep(600);
	charColorate(WHITE);
	warp(x, y);		for (int i = 0; i < w + 6; i++) cout << " ";
	warp(x, y-1);	for (int i = 0; i < 20; i++) cout << " ";
	turnCursor(1);
}

void graphical_loader::reset(int posx, int posy, int width)
{
	x = posx; y = posy; w = width;
}

graphical_box::graphical_box()
{
	x = 0; y = 0;
	w = 0; h = 0;
	border = 0;
}

void graphical_box::init(int posx, int posy, int width, int height, int bor)
{
	x = posx; y = posy;
	w = width; h = height;
	border = bor;
}

void graphical_box::display(int color)
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

graphical_inputbox::graphical_inputbox(int posx, int posy, int width, int height)
{
	x = posx; y = posy;
	w = width; h = height;
	box.init(x, y, w, h, 1);
	box.display(WHITE);
}

void graphical_inputbox::inputhidden(string content, string& var)
{
	warp(x + 1, y + offset++);
	cout << content;
	asteriskEncode(var);
}