#include <iostream>
#include <vector>

const int  BOARD_WIDTH = 40;
const int BOARD_HEIGHT = 20;

using namespace std;

enum class Direction { STOP, LEFT, RIGHT, UP, DOWN };

class Snake {
protected:
	Tile head;
	Direction direction;
	vector<Tile> tail;
public:
	Snake();
	Tile getHead();
	vector<Tile> getTail();
	void setTail(vector<Tile> tail);
	void incrementTail(int x, int y, int& score);
	Direction getDirection();
	void setDirection(Direction direction);
	bool isOpposite(Direction d1, Direction d2);
	bool isInTail(int x, int y);
	void getNextPosition(int& x, int& y);
	void getPreviousPosition(int& x, int& y);
	bool isValidPosition(int x, int y);
	void setHeadPosition(int x, int y);
	void setTailAt(int i, Tile tile);

	void getCurrentTailPosition(int& x, int& y);