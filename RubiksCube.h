/*---RubiksCube.h----------------------------------------------------------------
A header file for enumerated data type RubiksCube

Written by:	Nolan Ripplinger
Written For: 
---------------------------------------------------------------------------*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#ifndef RUBIKSCUBE
#define RUBIKSCUBE

enum CubeColor {
	WHITE, BLUE, GREEN, ORANGE, RED, YELLOW
};
enum Side {
	FRONT, BACK, LEFT, RIGHT, TOP, BOTTOM, ALL
};
enum Direction {
	COUNTER_CLOCKWISE, CLOCKWISE
};
/*enum Neighbor {
	UP, DOWN, LEFT, RIGHT
};*/

class Cube{
public:	
	Cube();
	Cube(int dimension);
	void display(Side side);
	void resetCube();
	void move(Direction direction, int piece, Side);
	void swapper(Direction direction, bool isVertical, int rowOrCol, Side side);
	//Side getNeighbor(Side side, Neighbor direction);
	int getSize();
	vector<vector<CubeColor>> getSide(Side side);
	void operator=(Cube cube2);
	
private:
	int cubeSize;
	vector<vector<CubeColor>> front;
	vector<vector<CubeColor>> back;
	vector<vector<CubeColor>> left;
	vector<vector<CubeColor>> right;
	vector<vector<CubeColor>> top;
	vector<vector<CubeColor>> bottom;

	void loadCube();
	void rotate(Direction direction, Side side);
	void cubeFaceTransfer(Cube& donor, Side side);
	void cubeModifiedFaceTransfer(Cube& modified, Side side);
};

//Prototypes

#endif