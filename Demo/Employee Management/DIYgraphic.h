#ifndef GRAPHICS_HEADER
#define GRAPHICS_HEADER

#include <Windows.h>
#include <conio.h>
using namespace std;

#define TONE1 1
#define TONE2 9
#define INACT 8
#define GOOD 0xA
#define BAD 0xC
#define WHITE 15
#define WIDTH 1380
#define HEIGHT 768
#define OFX 10
#define OFY 5
#define TXTY 21
#define SEMI 6

class graphics_abstract
{
protected:
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
public:
	void warp(int x, int y);
	void charColorate(int x);
	void charColorate(int x, int y);
	void evaluate(string bstr, int& m, int& n);
	void turnCursor(bool on);
	int getx();
	int gety();
	void clearbuffer();
};

class graphical_box : public graphics_abstract
{
private:
	int x, y, w, h, border;
public:
	graphical_box();
	void init(int posx, int posy, int width, int height, int bor);
	void display(int color);
};

class screenctrl
{
private:
	int swidth = 0, sheight = 0;
	int bwidth = 0, bheight = 0;
	static screenctrl* inst;
	screenctrl() {}
public:
	static screenctrl* instance();
	void init(int width, int height);
	int getbufferw() { return bwidth; }
	int getbufferh() { return bheight; }
};

class graphical_menu : public graphics_abstract
{
private:
	string content, title; bool back = 0, dynamic = 1, willclear = 1;
	int x, y, w, h, border, select = 0, orix = 0;
	bool halign = 0, valign = 0;
	graphical_box box;
public:
	graphical_menu();
	graphical_menu(int posx, int posy, int bor) :
		x(posx), orix(posx), y(posy), w(0), h(0), border(bor) {	box.init(x, y, w, h, 0); }
	void init(int posx, int posy, int width, int height);
	void setpos(int xx, int yy) { x = xx; y = yy; }
	void set(string t, string s);
	void resize(int width, int height);
	void display() { display(title, content); }
	void display(string title, string content);
	//void formoutline(int color);
	int operate();
	int operate(string tit, string con);
	void clear();
	int getnextline() { return y + h + 2; }
	void autowarp(bool enable) { dynamic = enable; }
	void setclear(bool enable) { willclear = enable; }
	void lostfocus();
	void setalign(bool hor, bool ver);
};

class graphical_textbox : public graphics_abstract
{
private:
	string content;
	int x, y, w, h, border, select = 0;
	graphical_box box;
public:
	graphical_textbox();
	graphical_textbox(int posx, int posy, int width, int height, int bor) :
		x(posx), y(posy), w(width), h(height), border(bor) {box.init(x, y, w, h, border);}
	void init(int posx, int posy, int width, int height);
	void set(string s) { content = s; }
	void wipe();
	void display(string s);
	void display();
};

class graphical_inputbox : public graphics_abstract
{
	int x, y, w, h, offset = 1;
	graphical_box box;
public:
	graphical_inputbox(int posx, int posy, int width, int height);
	template <class T>
	void input(string content, T &var);
	void inputhidden(string content, string& var);
};

class graphical_loader :public graphics_abstract
{
private:
	int x, y, w;
	string content;
public:
	graphical_loader(int posx, int posy, int width, string s) :
		x(posx), y(posy), w(width), content(s) { srand((unsigned)time(0)); }
	void load(int time);
	void reset(int posx, int posy, int width);
};

extern graphical_textbox outputbox;
extern graphical_menu mainmenu;

#endif

template<class T>
inline void graphical_inputbox::input(string content, T &var)
{
	warp(x+1, y+offset++);
	charColorate(SEMI); cout << content;
	charColorate(WHITE); cin >> var;
}
