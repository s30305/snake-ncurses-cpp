#include <iostream>
#include <ncursesw/curses.h>
#include "Game.hpp"
#include <stdlib.h>
#include <fstream>
#include <string>

#define height 16
#define width height*2
//boję się wkładać polskie znaczki w kod, a polski bez znaczków to herezja thus wszystko po angielsku
int loadhs();
void updatehs(int newhs);
void pytanie1(bool & plus, bool & vase);
bool pytanie2(int score, int highscore);

int main(int argc, char **argv){
	reset_programu:;
	bool plus = false;
	bool vase = false;
	int score;
	int hs = loadhs();
	
	pytanie1(plus, vase);
	
	Game game(height, width, hs, plus, vase);
	while(!game.isover()){
		game.useinput();
		
		game.update();
		
		game.redraw();
		
	}
	
	score = game.getscore();
	if(hs < game.getscore())
		updatehs(game.getscore());
		
	if (!game.isexit())
		endwin();
		if (pytanie2(score, hs) == true)
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

void pytanie1(bool & plus, bool & vase){
	reset_pytania:;
	std::cout << "Press 1 to select plain gamemode" << std::endl << "Press 2 to select + gamemode" << std::endl << "Press 3 to select vase gamemode" << std::endl;
	int gamemode;
	std::cin >> gamemode; 
	switch(gamemode){
		case 1:
			break;
		case 2:
			plus = true;
			break;
		case 3:
			vase = true;
			break;
		default:
			std::cout << "Invalid input, retry" << std::endl;
			goto reset_pytania;
	}
}

bool pytanie2(int score, int highscore){
	reset_pytania2:;
	std::cout << "Game Over" << std::endl << "Score: " << score << std::endl << "HighScore: " << highscore << std::endl << "Do you want to continue playing? y/n" << std::endl;
	char pytanie;
	std::cin >> pytanie;
	if(pytanie == 'y')
		return true;
	else if(pytanie != 'y' && pytanie != 'n'){
		std::cout << "invalid input" << std::endl;
		goto reset_pytania2;
	}
	else 
		return false;
}