#pragma once
#include <ncursesw/curses.h>
#include <time.h>
#include <stdlib.h>
#include "Square.hpp"
#include "Draw.hpp"
#include "Apple.hpp"
#include "Empty.hpp"
#include "Snake.hpp"
#include "Scoreboard.hpp"

class Game{
	Square square;
	Apple *apple;
	Snake snake;
	Scoreboard scoreboard;
	bool m_gameover = false, m_exit = false;
	int m_score = 0, m_highscore; 
	void createapple();
	void createnextpiece(SnakePiece next);
	void destroyapple();
public:
	Game(int height, int width, int hs);
	void initialize();
	void useinput();
	void update();
	void redraw();
	bool isover();
	bool isexit();
	int getscore();
};