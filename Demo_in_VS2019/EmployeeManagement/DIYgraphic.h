#ifndef GRAPHICS_HEADER
#define GRAPHICS_HEADER
#include<Windows.h>
#include<conio.h>
#define TONE1 1
#define TONE2 9
#define GOOD 0xA
#define BAD 0xC
#define WHITE 15
#define WIDTH 1360
#define HEIGHT 768
#define OFX 10
#define OFY 5
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
	string content, title;
	int x, y, w, h, border, select = 0, orix;
public:
	graphical_menu();
	graphical_menu(int posx, int posy, int bor) :
		x(posx), orix(posx), y(posy), w(0), h(0), border(bor) {}
	void init(int posx, int posy, int width, int height);
	void set(string t, string s);
	void resize(int width, int height);
	void display() { display(title, content); }
	void display(string title, string content);
	void formoutline(int color);
	int operate();
	int operate(string tit, string con);
};

class graphical_textbox : public graphics_abstract
{
private:
	string content;
	int x, y, w, h, border, select = 0;
public:
	graphical_textbox();
	graphical_textbox(int posx, int posy, int width, int height, int bor) :
		x(posx), y(posy), w(width), h(height), border(bor) {}
	void init(int posx, int posy, int width, int height);
	void set(string s) { content = s; }
	void wipe();
	void display(string s);
	void display();
};

extern graphical_textbox outputbox;
#endif