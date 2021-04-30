#include "Tile.hpp"
#include "Snake.hpp"
#include <iostream>
#include <cassert>

using namespace std;

Tile::Tile() {
	position.first = -1;
	position.second = -1;
	type = Tile_type::EMPTY;
}
Tile::Tile(int x, int y, Tile_type type) {
	assert(x >= 0 && x < BOARD_WIDTH);
	assert(y >= 0 && y < BOARD_HEIGHT);

	position.first = x;
	position.second = y;
	this->type = type;
}
Tile::Tile(Tile_type type) {
	//srand(time(NULL));
	int x = rand() % BOARD_WIDTH, y = rand() % BOARD_HEIGHT;
	
	position.first = x;
	position.second = y;
	this->type = type;
}
pair<int,int> Tile::getPosition() { return position; }
Tile_type Tile::getType() { return type; }