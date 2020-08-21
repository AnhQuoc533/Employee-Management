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
	int x, y, w, h, select, border;
public:
	void display();
	void formoutline(int color);
	int operate();
};