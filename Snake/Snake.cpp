// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Game.hpp"
#include <cassert>
#include <Windows.h>

using namespace std;

Snake::Snake() {
	head = Tile(Tile_type::SNAKE_HEAD);
	direction = Direction::STOP;
}
Tile Snake::getHead() { return head; }
vector<Tile> Snake::getTail() { return tail; }
void Snake::setTail(vector<Tile> tail) { this->tail = tail; }
Direction Snake::getDirection() { return direction; }
bool Snake::isInTail(int x, int y) {
	for (unsigned int i = 0; i < tail.size(); i++) {
		if (tail[i].getPosition().first == x && tail[i].getPosition().second == y) return true;
	}
	return false;
}
void Snake::incrementTail(int x, int y, int& score) {
	Tile tailTile;
	tailTile = Tile(x, y, Tile_type::SNAKE_TAIL);
	tail.push_back(tailTile);
	score++;
}
void Snake::setDirection(Direction direction) {
	this->direction = direction;
}
void Snake::getNextPosition(int& x, int& y) {
	switch (direction) {
	case Direction::DOWN:
		y++;
		break;
	case Direction::LEFT:
		x--;
		break;
	case Direction::RIGHT:
		x++;
		break;
	case Direction::UP:
		y--;
		break;
	}
}
void Snake::getPreviousPosition(int& x, int& y) {
	switch (direction) {
	case Direction::DOWN:
		y--;
		break;
	case Direction::LEFT:
		x++;
		break;
	case Direction::RIGHT:
		x--;
		break;
	case Direction::UP:
		y++;
		break;
	default:
		return;
	}
}
bool Snake::isValidPosition(int x, int y) {
	if (not(x >= 0 && x < BOARD_WIDTH)) return false;
	if (not(y >= 0 && y < BOARD_HEIGHT)) return false;

	for (unsigned int i = 0; i < tail.size(); i++) {
		if (tail[i].getPosition().first == x && tail[i].getPosition().second == y) return false;
	}
	//if(direction)
	return true;
}
//sets x, y to be the current last position of the last tile of the tail 
//if the snake has yet no tail, then it's the snake's head
void Snake::getCurrentTailPosition(int& x, int& y) {
	//case where tail is of size 0 or of size n
	if (tail.size() > 0) {
		x = tail[tail.size() - 1].getPosition().first;
		y = tail[tail.size() - 1].getPosition().second;
	}
	else {
		x = head.getPosition().first;
		y = head.getPosition().second;
	}
}
void Snake::setHeadPosition(int x, int y) {
	head = Tile(x, y, Tile_type::SNAKE_HEAD);
}
void Snake::setTailAt(int i, Tile tile) {
	assert(i >= 0 && i < tail.size());
	tail[i] = tile;
}
bool Snake::isOpposite(Direction d1, Direction d2) {
	switch (d1) {
	case Direction::DOWN:
		return d2 == Direction::UP;
		break;
	case Direction::UP:
		return d2 == Direction::DOWN;
		break;
	case Direction::LEFT:
		return d2 == Direction::RIGHT;
		break;
	case Direction::RIGHT:
		return d2 == Direction::LEFT;
		break;
	default:
		return false;
	}
}

void drawMenu() {
	Game::clearScreen(' ');
	Game::setCursorPosition(0, 0);
	cout << "Snake\n";
	cout << "1. PLAY\n";
	cout << "0. QUIT\n";
}

int main(){
	srand(time(NULL));

	char action;
	do {
		drawMenu();
		cin >> action;

		if (action == '1') {
			Game game;
			game.mainLoop();
		}
	} while (action != '0');
}