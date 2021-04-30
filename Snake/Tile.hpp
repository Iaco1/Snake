#include <iostream>

using namespace std;

enum class Tile_type {
	SNAKE_HEAD, SNAKE_TAIL, FRUIT, EMPTY
};

class Tile {
protected:
	pair <int, int> position;
	Tile_type type;
public:
	Tile();
	//generates a tile in a random position on the board 
	//could possibly cause an issue because it has been declared before the fully parametrized constructor 
	//but uses the f.p. constructor in its definition
	Tile(Tile_type type);
	Tile(int x, int y, Tile_type type);
	pair<int, int> getPosition();
	Tile_type getType();
};