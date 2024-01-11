#pragma once // program znajdzię się tylko w jednej kompilacji
#include <ncursesw/curses.h>
#include "Draw.hpp"

class Square{
	WINDOW *win;
	int m_height, m_width, m_startrow, m_startcol, m_xres, m_yres, m_timeout = 300;
	bool plus = false, vase = false, decision = false, enddecision = false, reset = false;
public:
	Square() {}
	Square(int h, int w) : m_height(h), m_width(w){
		initialize();
		mainmenu();
	}
	void initialize(){
		initscr();
		noecho();
		curs_set(0);
		getmaxyx(stdscr, m_yres, m_xres);	
		m_startrow = (m_yres / 2) - (m_height / 2);
		m_startcol = (m_xres / 2) - (m_width / 2);
		win = newwin(m_height, m_width, m_startrow, m_startcol);
		settimeout(m_timeout);
		keypad(win, true);
		addbox();
	}
	void mainmenu(){
		mvwaddstr(win, 1, 2, "SNAKE");
		mvwaddstr(win, 3, 2, "select gamemode:");
		mvwaddstr(win, 4, 2, "press 1 for plain mode");
		mvwaddstr(win, 5, 2, "press 2 for vase mode");
		mvwaddstr(win, 6, 2, "press 3 for plus mode");
		while(!decision){
			chtype input = getinput();
			switch(input){
				case '1':
					decision = true;
					break;
				case '2':
					vase = true;
					decision = true;
					break;
				case '3':
					plus = true;
					decision = true;
					break;
				default:
					break;
			}
		}
		werase(win);
		addbox();
	}
	void add(Draw draw){
		addsign(draw.gety(), draw.getx(), draw.getsign());
	}
	void addsign(int y, int x, chtype ch){
		mvwaddch(win, y, x, ch);
	}
	void getcoordinates(int &y, int &x){
		while((mvwinch(win, y = rand() % m_height, x = rand() % m_width)) != ' '); //losowe puste miejsce dla jabłka
	}
	bool isreset()                  {return reset;}
	bool isplus()                   {return plus;}
	bool isvase()                   {return vase;}
	chtype getinput()               {return wgetch(win);}
	void addbox()                   {box(win, 0, 0);}
	chtype getchar(int y, int x)    {return mvwinch(win, y, x);}
	void refresh()                  {wrefresh(win);}
	void settimeout(int speed)      {wtimeout(win, speed);}
	int getstartrow()	            {return m_startrow;}
	int getstartcol()	            {return m_startcol;}
	int gettimeout()	            {return m_timeout;}
	void changetimeout(int speed)	{m_timeout = speed;}
};