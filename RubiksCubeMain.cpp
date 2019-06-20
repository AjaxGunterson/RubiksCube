#include <iostream>
#include "RubiksCube.h"

using namespace std;

//prototypes

//global variables
const int CUBE_SIZE = 3;

int main()
{
	Cube rubik(CUBE_SIZE),
		rubik2(CUBE_SIZE);

	//rubik.move(CLOCKWISE, 0, FRONT);
	rubik.move(CLOCKWISE, 5, FRONT);
	rubik.display(ALL);

	return 0;
}