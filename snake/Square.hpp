#pragma once // program znajdzię się tylko w jednej kompilacji
#include <ncursesw/curses.h>
#include "Draw.hpp"

class Square{
	WINDOW *win;
	int height, width, startrow, startcol;
	int timeout;
public:
	Square(){initialize(0, 0, 300);}  //default
	
	Square(int height, int width, int speed){
		initialize(height, width, speed);
	}
	
	void initialize(int height, int width, int speed){
		initscr();
		noecho();
		curs_set(0);
		int xres, yres;
		getmaxyx(stdscr, yres, xres);
		this->height = height;  
		this->width = width;
		
		startrow = (yres / 2) - (height / 2);
		startcol = (xres / 2) - (width / 2);
		
		win = newwin(height, width, startrow, startcol);
		
		timeout = speed;
		settimeout(speed);
		// strzałki są wyłączone by default
		keypad(win, true);
	}

	void drawsquare(){
		clear();
		refresh();    //automatyzacja goes brrrr
	}

	void addbox(){
		box(win, 0, 0);
	}
	
	void add(Draw draw){
		addsign(draw.gety(), draw.getx(), draw.getsign());
	}
	
	void addsign(int y, int x, chtype ch){
		mvwaddch(win, y, x, ch);
	}
	
	chtype getinput(){			
		return wgetch(win);
	}
	
	void getcoordinates(int &y, int &x){
		while((mvwinch(win, y = rand() % height, x = rand() % width)) != ' '); //losowe puste miejsce dla jabłka
	}
	
	chtype getchar(int y, int x){
		return mvwinch(win, y, x);
	}
	void clear(){
		wclear(win);
		addbox();
	}
	
	void refresh(){
	wrefresh(win);
	}
	
	void settimeout(int speed){
		wtimeout(win, speed);   // automatyczne odświeżanie się ekranu / prędkość gry
	}
	
	int getstartrow(){
		return startrow;
	}
	
	int getstartcol(){
		return startcol;
	}
	
	int gettimeout(){
		return timeout;
	}
	
	void changetimeout(int speed){
		timeout = speed;
	}
};