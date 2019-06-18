#include <iostream>
#include "RubiksCube.h"

using namespace std;

//prototypes

//global variables
const int CUBE_SIZE = 5;

int main()
{
	Cube rubik(CUBE_SIZE),
		rubik2(CUBE_SIZE);

	rubik.move(CLOCKWISE, 3, LEFT);
	rubik.display(ALL);

	return 0;
}