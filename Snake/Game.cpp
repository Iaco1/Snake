#include "Game.hpp"
#include <cassert>
#include <conio.h>
#include <thread>
#include <chrono>
#include <Windows.h>

Game::Game() {
	gameOver = false;
	fruit = Tile(Tile_type::FRUIT);
	snake.getHead() = Tile(Tile_type::SNAKE_HEAD);
	score = 0;
}
void Game::updateBoard() {
	//eliminating the previous head position
	int x = snake.getHead().getPosition().first, y = snake.getHead().getPosition().second;
	snake.getPreviousPosition(x, y);
	map[y][x] = Tile(x, y, Tile_type::EMPTY);

	//eliminating the previous tail tiles
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (map[i][j].getType() == Tile_type::SNAKE_TAIL) map[i][j] = Tile(j, i, Tile_type::EMPTY);
		}
	}

	//sets the position of the fruit, snake's head and tail in the map
	map[fruit.getPosition().second][fruit.getPosition().first] = Tile(fruit.getPosition().first, fruit.getPosition().second, Tile_type::FRUIT);
	map[snake.getHead().getPosition().second][snake.getHead().getPosition().first] = Tile(snake.getHead().getPosition().first, snake.getHead().getPosition().second, Tile_type::SNAKE_HEAD);
	for (unsigned int i = 0; i < snake.getTail().size(); i++) {
		x = snake.getTail()[i].getPosition().first, y = snake.getTail()[i].getPosition().second;
		map[y][x] = Tile(x, y, Tile_type::SNAKE_TAIL);
	}
}
/*
void Game::draw() {
	system("cls");
	cout << "Score: " << score<< " ";
	if (snake.getDirection() == Direction::STOP) cout << "PAUSE";
	cout << endl;
	for (int i = 0; i < BOARD_WIDTH+2; i++) { cout << "\xCD"; } cout << endl;

	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = -1; j < BOARD_WIDTH+1; j++) {
			switch (j) {
			case -1:
			case BOARD_WIDTH:
				cout << "\xBA";
				break;
			default:
				switch (map[i][j].getType()) {
				case Tile_type::EMPTY:
					cout << " ";
					break;
				case Tile_type::FRUIT:
					cout << "a";
					break;
				case Tile_type::SNAKE_HEAD:
					cout << "H";
					break;
				case Tile_type::SNAKE_TAIL:
					cout << "T";
					break;
				default:
					cout << "x";
					break;
				}
			}
			
		}
		cout << endl;
	}

	for (int i = 0; i < BOARD_WIDTH + 2; i++) { cout << "\xCD"; }
	if (gameOver) cout << endl << "GAME OVER";
}
*/
void Game::drawConsole() {
	setCursorPosition(0, 0);
	setCursorVisible(false);
	cout << "Score: " << score << " ";
	if (snake.getDirection() == Direction::STOP) cout << "PAUSE";
	cout << "     "<<endl;
	for (int i = 0; i < BOARD_WIDTH + 2; i++) { cout << "\xCD"; } cout << endl;

	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = -1; j < BOARD_WIDTH + 1; j++) {
			switch (j) {
			case -1:
			case BOARD_WIDTH:
				cout << "\xBA";
				break;
			default:
				switch (map[i][j].getType()) {
				case Tile_type::EMPTY:
					cout << " ";
					break;
				case Tile_type::FRUIT:
					cout << "a";
					break;
				case Tile_type::SNAKE_HEAD:
					cout << "H";
					break;
				case Tile_type::SNAKE_TAIL:
					cout << "T";
					break;
				default:
					cout << "x";
					break;
				}
			}

		}
		cout << endl;
	}

	for (int i = 0; i < BOARD_WIDTH + 2; i++) { cout << "\xCD"; }
	if (gameOver) cout << endl << "GAME OVER";

	this_thread::sleep_for(chrono::milliseconds(50));
	setCursorVisible(true);
}

char Game::input() {
	char action = ' ';
	if (_kbhit()) {
		char action = _getch();
		Direction previousDirection = snake.getDirection();
		switch (action) {
		case 'w':
			snake.setDirection(Direction::UP);
			break;
		case 'a':
			snake.setDirection(Direction::LEFT);
			break;
		case 's':
			snake.setDirection(Direction::DOWN);
			break;
		case 'd':
			snake.setDirection(Direction::RIGHT);
			break;
		case 'x':
			gameOver = true;
			break;
		case 'p':
			snake.setDirection(Direction::STOP);
			break;
		//default:
			//means the action char is not wasd or x for exit
			//snake.setDirection(Direction::STOP);
		}
		//this way we make it impossible for the player to turn the head onto its own tail and cause a gameover
		if (snake.isOpposite(snake.getDirection(), previousDirection)) snake.setDirection(previousDirection);
	}
	return action;
}
void Game::logic() {
	//case in which the fruit and snake head spawn in the same place
	while (fruit.getPosition().first == snake.getHead().getPosition().first
		&& fruit.getPosition().second == snake.getHead().getPosition().second) {
		fruit = Tile(Tile_type::FRUIT);
	}
	
	//case in which the fruit spawns in the snake's tail
	if (snake.getTail().size() > 0) {
		while (snake.isInTail(fruit.getPosition().first, fruit.getPosition().second)) {
			fruit = Tile(Tile_type::FRUIT);
		}
	}
	
	//this has the head follow the tail
	if (snake.getDirection() != Direction::STOP) {
		//having the tail follow the head
		vector<Tile> tailcopy = snake.getTail();
		tailcopy.insert(tailcopy.begin(), snake.getHead());
		
		for (unsigned int i = 0; i < snake.getTail().size(); i++) {
			int x = tailcopy[i].getPosition().first, y = tailcopy[i].getPosition().second;
			snake.setTailAt(i, Tile(x, y, Tile_type::SNAKE_TAIL));
		}
	}
	
	int x, y;
	//gameOver if the head bumps into a wall or into its own tail
	x = snake.getHead().getPosition().first, y = snake.getHead().getPosition().second;
	snake.getNextPosition(x, y);
	if (snake.isValidPosition(x,y)) snake.setHeadPosition(x, y);
	else gameOver = true;

	//case in which the snake eats the fruit
	if (fruit.getPosition().first == x && fruit.getPosition().second == y) {
		snake.getCurrentTailPosition(x, y);
		snake.incrementTail(x, y, score);
	}
}
void Game::mainLoop() {
	char action = ' ';

	while (action != 'x' && !getGameOver()) {
		updateBoard();
		drawConsole();
		action = input();
		logic();
	}
	drawConsole();
	gameOver = false;
}
bool Game::getGameOver() { 
	return gameOver; 
}

