#pragma once // program znajdzię się tylko w jednej kompilacji
#include <ncursesw/curses.h>
#include "Draw.hpp"

class Square{
	WINDOW *win;
	int m_height, m_width, m_startrow, m_startcol, m_xres, m_yres, m_timeout = 300;
public:
	Square() {}
	Square(int h, int w) : m_height(h), m_width(w){
		initialize();
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
		// strzałki są wyłączone by default
		keypad(win, true);
	}
	void drawsquare(){
		clear();
		refresh();    //automatyzacja goes brrrr
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
		void clear(){
		wclear(win);
		addbox();
	}
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