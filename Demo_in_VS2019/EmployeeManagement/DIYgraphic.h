#ifndef GRAPHICS_HEADER
#define GRAPHICS_HEADER
#include<Windows.h>
#include<conio.h>
#define TONE1 1
#define TONE2 9
#define GOOD A
#define BAD C
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

class graphical_menu : public graphics_abstract
{
private:
	string content, title;
	int x, y, w, h, border, select = 0;
public:
	graphical_menu();
	graphical_menu(int posx, int posy, int width, int height, int bor) :
		x(posx), y(posy), w(width), h(height), border(bor) {}
	void init(int posx, int posy, int width, int height);
	void set(string t, string s);
	void resize(int width, int height);
	void display() { display(title, content); }
	void display(string title, string content);
	void formoutline(int color);
	int operate();
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
extern int scrw, scrh;
void getscrsize(int& width, int& height);
#endif