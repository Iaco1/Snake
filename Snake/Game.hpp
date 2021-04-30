#include <iostream>
#include "Tile.hpp"
#include "Snake.hpp"

using namespace std;

class Game {
protected:
	bool gameOver;
	Tile map[BOARD_HEIGHT][BOARD_WIDTH];
	Snake snake;
	Tile fruit;
	int score;
public:
	Game();
	void updateBoard();
	//void draw();
	void drawConsole();
	char input();
	void logic();
	void mainLoop();

	bool getGameOver();
};