#include "Game.hpp"
void Game::createapple(){
	int y, x;
	square.getcoordinates(y, x);
	apple = new Apple(y, x);
	square.add(*apple);

}

void Game::createnextpiece(SnakePiece next){
	if(apple != NULL) {
		switch(square.getchar(next.gety(), next.getx())) {
			case '@':
				destroyapple();
				break;
			case ' ': {
				int emptyrow = snake.tail().gety();
				int emptycol = snake.tail().getx();
				square.add(Empty(emptyrow, emptycol));
				snake.removepiece();
				break;
			}
			default:            //kazdy inny przypadek to kolizja
				gameover = true;
				break;
		}
	}
	square.add(next);
	snake.addpiece(next);
}

void Game::destroyapple(){
	delete apple;
	apple = NULL;
	score += 1;
	if ((square.gettimeout() > 50))
		square.changetimeout(square.gettimeout() - 10);
	scoreboard.updatescore(score);
}

Game::Game(int height, int width, int hs, bool p, bool v) :highscore(hs){
	square = Square(height, width, 300);
	int sbrow = square.getstartrow() + height;
	int sbcol = square.getstartcol();
	scoreboard = Scoreboard(width, sbrow, sbcol);
	initialize(p, v);
}

void Game::initialize(bool plus, bool vase){
	apple = NULL;
	square.drawsquare();
	scoreboard.initialize(score, highscore);

	gameover = false;
	exit = false;
	//pozwala na uzycie rand
	srand(time(NULL));

	snake.setdirection(down);

	createnextpiece(SnakePiece(2, 5));
	for(int i=0; i<3; i++)
		createnextpiece(snake.nexthead());
	//levele
	if(plus){
		for(int i = 1; i!=8; i++)
			square.addsign(7, 11 + i, '%');
		for(int i = 1; i!=6; i++)
			square.addsign(4 + i, 15, '%');
	}
	if(vase){
		for(int i = 1; i!=7; i++)
			square.addsign(3 + i, 7 + i, '%');
		for(int i = 1; i!=7; i++)
			square.addsign(3 + i, 25, '%');
		for(int i = 1; i!=13; i++)
			square.addsign(12, 13 + i, '%');
	}
	if (apple == NULL){
		createapple();
	}

}

void Game::useinput(){
	chtype input = square.getinput();

	int old_timeout = square.gettimeout();

	switch(input){
		case KEY_UP:
		case 'w':
			snake.setdirection(up);
			break;

		case KEY_DOWN:
		case 's':
			snake.setdirection(down);
			break;

		case KEY_RIGHT:
		case 'd':
			snake.setdirection(right);
			break;

		case KEY_LEFT:
		case 'a':
			snake.setdirection(left);
			break;

		case 'p':
			square.settimeout(-1);
			while(square.getinput() != 'p')
				;
			square.settimeout(old_timeout);
			break;

		case 'x':
			exit = true;
			gameover = true;
			break;

		default:
			break;
	}
}

void Game::update(){
	createnextpiece(snake.nexthead());

	if (apple == NULL){
		createapple();
	}
}

void Game::redraw(){
	square.refresh();
	scoreboard.refresh();
}

bool Game::isover(){
	return gameover;
}

bool Game::isexit(){return exit;}

int Game::getscore(){return score;}