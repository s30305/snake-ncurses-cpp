#include <iostream>
#include <ncursesw/curses.h>
#include "Game.hpp"
#include "Square.hpp"
#include <stdlib.h>
#include <fstream>
#include <string>

#define height 16
#define width height*2
//boję się wkładać polskie znaczki w kod, a polski bez znaczków to herezja thus wszystko po angielsku
int loadhs();
void updatehs(int newhs);

int main(int argc, char **argv){
	reset_programu:;
	int score;
	int hs = loadhs();
	
	Game game(height, width, hs);
	while(!game.isover()){
		game.useinput();
		game.update();
		game.redraw();		
	}
	score = game.getscore();
	if(hs < game.getscore())
		updatehs(game.getscore());
		
	if (!game.isexit())
		goto reset_programu;
	
	getch();
	endwin();
	refresh();
	return 0;
}

int loadhs(){
	std::ifstream fin("highscore.txt");
	int score;
	fin >> score;
	fin.close();
	return score;
}

void updatehs(int newhs){
	std::ofstream fin("highscore.txt");
	fin << newhs;
	fin.close();
}