#include "RubiksCube.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

/*Default Constructor*/
Cube::Cube() {
	front.resize(3, vector<CubeColor>(3));
	back.resize(3, vector<CubeColor>(3));
	left.resize(3, vector<CubeColor>(3));
	right.resize(3, vector<CubeColor>(3));
	top.resize(3, vector<CubeColor>(3));
	bottom.resize(3, vector<CubeColor>(3));
	cubeSize = 3;
	loadCube();

}//end default constructor

/*Explicit Constructor*/
Cube::Cube(int size) {
	if (size < 2) {
		size = 2;
		cout << "Size cannot be smaller than 2; Size set to 2." << endl;
	}
	
	front.resize(size, vector<CubeColor>(size));
	back.resize(size, vector<CubeColor>(size));
	left.resize(size, vector<CubeColor>(size));
	right.resize(size, vector<CubeColor>(size));
	top.resize(size, vector<CubeColor>(size));
	bottom.resize(size, vector<CubeColor>(size));
	cubeSize = size;
	loadCube();
}//end explicit constructor

void Cube::loadCube() {
	for (int i = 0; i < cubeSize; i++) {
		for (int j = 0; j < cubeSize; j++) {
			front[i][j] = WHITE;
		}
	}
	for (int i = 0; i < cubeSize; i++) {
		for (int j = 0; j < cubeSize; j++) {
			back[i][j] = BLUE;
		}
	}
	for (int i = 0; i < cubeSize; i++) {
		for (int j = 0; j < cubeSize; j++) {
			left[i][j] = GREEN;
		}
	}
	for (int i = 0; i < cubeSize; i++) {
		for (int j = 0; j < cubeSize; j++) {
			right[i][j] = ORANGE;
		}
	}
	for (int i = 0; i < cubeSize; i++) {
		for (int j = 0; j < cubeSize; j++) {
			top[i][j] = RED;
		}
	}
	for (int i = 0; i < cubeSize; i++) {
		for (int j = 0; j < cubeSize; j++) {
			bottom[i][j] = YELLOW;
		}
	}
}

void Cube::move(Direction direction, int piece, Side side) {
	if (piece > cubeSize * 2 - 1) {
		cout << "Piece too high" << endl;
		return;
	}

	int rowOrCol = piece % cubeSize;

	if (piece >= cubeSize) {//move will be horizontal
		if (piece == cubeSize) {//top will be turned
			cout << "top selected" << endl;
			switch (direction) {
			case COUNTER_CLOCKWISE:
				switch (side) {
				case FRONT:
				case LEFT:
				case RIGHT:
				case BACK:
					this->rotate(COUNTER_CLOCKWISE, TOP);
					break;
				case TOP:
					this->rotate(COUNTER_CLOCKWISE, BACK);
					break;
				case BOTTOM:
					this->rotate(COUNTER_CLOCKWISE, FRONT);
					break;
				default:
					break;
				}
				break;
			case CLOCKWISE:
				switch (side) {
				case FRONT:
				case LEFT:
				case RIGHT:
				case BACK:
					this->rotate(CLOCKWISE, TOP);
					break;
				case TOP:
					this->rotate(CLOCKWISE, BACK);
					break;
				case BOTTOM:
					this->rotate(CLOCKWISE, FRONT);
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
		else if (piece == cubeSize * 2 - 1) {//bottom will be turned
			cout << "Bottom selected" << endl;
			switch (direction) {
			case COUNTER_CLOCKWISE:
				switch (side) {
				case FRONT:
				case LEFT:
				case RIGHT:
				case BACK:
					this->rotate(COUNTER_CLOCKWISE, BOTTOM);
					break;
				case TOP:
					this->rotate(COUNTER_CLOCKWISE, FRONT);
					break;
				case BOTTOM:
					this->rotate(COUNTER_CLOCKWISE, BACK);
					break;
				default:
					break;
				}
				break;
			case CLOCKWISE:
				switch (side) {
				case FRONT:
				case LEFT:
				case RIGHT:
				case BACK:
					this->rotate(CLOCKWISE, BOTTOM);
					break;
				case TOP:
					this->rotate(CLOCKWISE, FRONT);
					break;
				case BOTTOM:
					this->rotate(CLOCKWISE, BACK);
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
			
		}
		else {

		}
		this->swapper(direction, 0, rowOrCol, side);
	}
	else {//move will be vertical
		if (piece == 0) {//left will be turned
			cout << "left selected" << endl;
			switch (direction) {
			case COUNTER_CLOCKWISE:
				switch (side) {
				case FRONT:
				case TOP:
				case BOTTOM:
					this->rotate(CLOCKWISE, LEFT);
					break;
				case BACK:
					this->rotate(CLOCKWISE, RIGHT);
					break;
				case LEFT:
					this->rotate(CLOCKWISE, BACK);
					break;
				case RIGHT:
					this->rotate(CLOCKWISE, FRONT);
					break;
				default:
					break;
				}
				break;
			case CLOCKWISE:
				switch (side) {
				case FRONT:
				case TOP:
				case BOTTOM:
					this->rotate(COUNTER_CLOCKWISE, LEFT);
					break;
				case BACK:
					this->rotate(COUNTER_CLOCKWISE, RIGHT);
					break;
				case LEFT:
					this->rotate(COUNTER_CLOCKWISE, BACK);
					break;
				case RIGHT:
					this->rotate(COUNTER_CLOCKWISE, FRONT);
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
		else if (piece == cubeSize - 1) {//right will be turned
			cout << "right selected" << endl;
			switch (direction) {
			case COUNTER_CLOCKWISE:
				switch (side) {
				case FRONT:
				case TOP:
				case BOTTOM:
					this->rotate(COUNTER_CLOCKWISE, RIGHT);
					break;
				case BACK:
					this->rotate(COUNTER_CLOCKWISE, LEFT);
					break;
				case LEFT:
					this->rotate(COUNTER_CLOCKWISE, FRONT);
					break;
				case RIGHT:
					this->rotate(COUNTER_CLOCKWISE, BACK);
					break;
				default:
					break;
				}
				break;
			case CLOCKWISE:
				switch (side) {
				case FRONT:
				case TOP:
				case BOTTOM:
					this->rotate(CLOCKWISE, RIGHT);
					break;
				case BACK:
					this->rotate(CLOCKWISE, LEFT);
					break;
				case LEFT:
					this->rotate(CLOCKWISE, FRONT);
					break;
				case RIGHT:
					this->rotate(CLOCKWISE, BACK);
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
		else {
		}
		this->swapper(direction, 1, rowOrCol, side);
	}
}

void Cube::rotate(Direction direction, Side side) {
	Cube tempCube(cubeSize);

	if (direction == CLOCKWISE){//right rotation
		switch (side) {
		case FRONT:
			for (int i = 0; i < cubeSize; i++) {
				for (int j = 0; j < cubeSize; j++) {
					tempCube.front[i][j] = front[cubeSize - j - 1][i];
				}
			}
			front = tempCube.front;
			break;
		case BACK:
			for (int i = 0; i < cubeSize; i++) {
				for (int j = 0; j < cubeSize; j++) {
					tempCube.back[i][j] = back[cubeSize - j - 1][i];
				}
			}
			back = tempCube.back;
			break;
		case LEFT:
			for (int i = 0; i < cubeSize; i++) {
				for (int j = 0; j < cubeSize; j++) {
					tempCube.left[i][j] = left[cubeSize - j - 1][i];
				}
			}
			left = tempCube.left;
			break;
		case RIGHT:
			for (int i = 0; i < cubeSize; i++) {
				for (int j = 0; j < cubeSize; j++) {
					tempCube.right[i][j] = right[cubeSize - j - 1][i];
				}
			}
			right = tempCube.right;
			break;
		case TOP:
			for (int i = 0; i < cubeSize; i++) {
				for (int j = 0; j < cubeSize; j++) {
					tempCube.top[i][j] = top[cubeSize - j - 1][i];
				}
			}
			top = tempCube.top;
			break;
		case BOTTOM:
			for (int i = 0; i < cubeSize; i++) {
				for (int j = 0; j < cubeSize; j++) {
					tempCube.bottom[i][j] = bottom[cubeSize - j - 1][i];
				}
			}
			bottom = tempCube.bottom;
			break;
		default:
			break;
		}
	}
	else {//left rotation
		switch (side) {
		case FRONT:
			for (int i = 0; i < cubeSize; i++) {
				for (int j = 0; j < cubeSize; j++) {
					tempCube.front[cubeSize - j - 1][i] = front[i][j];
				}
			}
			front = tempCube.front;
			break;
		case BACK:
			for (int i = 0; i < cubeSize; i++) {
				for (int j = 0; j < cubeSize; j++) {
					tempCube.back[i][j] = back[j][i];
				}
			}
			back = tempCube.back;
			break;
		case LEFT:
			for (int i = 0; i < cubeSize; i++) {
				for (int j = 0; j < cubeSize; j++) {
					tempCube.left[i][j] = left[j][i];
				}
			}
			left = tempCube.left;
			break;
		case RIGHT:
			for (int i = 0; i < cubeSize; i++) {
				for (int j = 0; j < cubeSize; j++) {
					tempCube.right[i][j] = right[j][i];
				}
			}
			right = tempCube.right;
			break;
		case TOP:
			for (int i = 0; i < cubeSize; i++) {
				for (int j = 0; j < cubeSize; j++) {
					tempCube.top[i][j] = top[j][i];
				}
			}
			top = tempCube.top;
			break;
		case BOTTOM:
			for (int i = 0; i < cubeSize; i++) {
				for (int j = 0; j < cubeSize; j++) {
					tempCube.bottom[i][j] = bottom[j][i];
				}
			}
			bottom = tempCube.bottom;
			break;
		default:
			break;
		}
	}
	
	
}

void Cube::swapper(Direction direction, bool isVertical, int rowOrCol, Side side) {
	vector<CubeColor> tempRow;
	tempRow.resize(cubeSize);

	//tempCube.cubeFaceTransfer(*this, side);
	if (isVertical) {//vertical moves
		if (direction) {//clockwise
			switch (side) {
			case FRONT:
				for (int i = 0; i < cubeSize; i++) {
					tempRow[i] = front[i][rowOrCol];
					front[i][rowOrCol] = bottom[i][rowOrCol];
					bottom[i][rowOrCol] = back[i][(cubeSize - 1) - rowOrCol];
					back[i][(cubeSize - 1) - rowOrCol] = top[i][rowOrCol];
					top[i][rowOrCol] = tempRow[i];
				}//end for
				break;//end FRONT
			case BACK:
				switch (direction) {//switch direction
				case CLOCKWISE:
					direction = COUNTER_CLOCKWISE;
					break;
				case COUNTER_CLOCKWISE:
					direction = CLOCKWISE;
					break;
				}//end switch
				
				//tempCube.cubeModifiedFaceTransfer(*this, side);
			
				this->swapper(direction, isVertical, (cubeSize - 1) - rowOrCol, FRONT);
				break;//end BACK
			case LEFT:
				for (int i = 0; i < cubeSize; i++) {
					tempRow[i] = left[i][rowOrCol];
					left[i][rowOrCol] = bottom[(cubeSize - 1) - rowOrCol][i];
					bottom[(cubeSize - 1) - rowOrCol][i] = right[i][(cubeSize - 1) - rowOrCol];
					right[i][(cubeSize - 1) - rowOrCol] = top[rowOrCol][i];
					top[rowOrCol][i] = tempRow[i];
				}//end for
				break;
			case RIGHT:
				switch (direction) {//switch direction
				case CLOCKWISE:
					direction = COUNTER_CLOCKWISE;
					break;
				case COUNTER_CLOCKWISE:
					direction = CLOCKWISE;
					break;
				}//end switch

				this->swapper(direction, isVertical, (cubeSize - 1) - rowOrCol, LEFT);
				break;//end RIGHT
			case TOP:
			case BOTTOM:
				this->swapper(direction, isVertical, rowOrCol, FRONT);
				break;
			}//end switch
			
		}//counter clockwise
		else {
			switch (side) {
			case FRONT:
				for (int i = 0; i < cubeSize; i++) {
					tempRow[i] = front[i][rowOrCol];
					front[i][rowOrCol] = top[i][rowOrCol];
					top[i][rowOrCol] = back[i][(cubeSize - 1) - rowOrCol];
					back[i][(cubeSize - 1) - rowOrCol] = bottom[i][rowOrCol];
					bottom[i][rowOrCol] = tempRow[i];
				}
				break;
			case LEFT:
				for (int i = 0; i < cubeSize; i++) {
					tempRow[i] = left[i][rowOrCol];
					left[i][rowOrCol] = top[rowOrCol][i];
					top[rowOrCol][i] = right[i][(cubeSize - 1) - rowOrCol];
					right[i][(cubeSize - 1) - rowOrCol] = bottom[(cubeSize - 1) - rowOrCol][i];
					bottom[(cubeSize - 1) - rowOrCol][i] = tempRow[i];
				}//end for
				break;
			case RIGHT:
				this->swapper(direction, isVertical, (cubeSize - 1) - rowOrCol, LEFT);
				break;
			case TOP:
			case BOTTOM:
				this->swapper(direction, isVertical, rowOrCol, FRONT);
				break;
			}
		}

	}
	else {//is horizontal
		if (direction) {//clockwise
			switch (side) {
			case TOP:
				this->swapper(CLOCKWISE, 1, rowOrCol, LEFT);
				break;
			case BOTTOM:
				this->swapper(CLOCKWISE, 1, (cubeSize - 1) - rowOrCol, LEFT);
				break;
			default:
				for (int i = 0; i < cubeSize; i++) {
					tempRow[i] = front[rowOrCol][i];
					front[rowOrCol][i] = right[rowOrCol][i];
					right[rowOrCol][i] = back[rowOrCol][i];
					back[rowOrCol][i] = left[rowOrCol][i];
					left[rowOrCol][i] = tempRow[i];
				}
				break;
			}
			
		}//counter clockwise
		else {
			switch (side) {
			case TOP:
				this->swapper(COUNTER_CLOCKWISE, 1, rowOrCol, LEFT);
				break;
			case BOTTOM:
				this->swapper(COUNTER_CLOCKWISE, 1, (cubeSize - 1) - rowOrCol, LEFT);
				break;
			default:
				for (int i = 0; i < cubeSize; i++) {
					tempRow[i] = front[rowOrCol][i];
					front[rowOrCol][i] = left[rowOrCol][i];
					left[rowOrCol][i] = back[rowOrCol][i];
					back[rowOrCol][i] = right[rowOrCol][i];
					right[rowOrCol][i] = tempRow[i];
				}
				break;
			}
			
		}
		
	}

	//this->cubeModifiedFaceTransfer(tempCube, side);
	//*this = tempCube;
}

/*Side Cube::getNeighbor(Side side, Neighbor direction) {
	switch (direction) {
	case UP:
		switch (side) {
		case FRONT:
			return TOP;
			break;
		case BACK:
			return TOP;
			break;
		case LEFT:
			return TOP;
			break;
		case RIGHT:
			return TOP;
			break;
		case TOP:
			return BACK;
			break;
		case BOTTOM:
			return FRONT;
			break;
		default:
			break;
		}
		break;
	case DOWN:
		switch (side) {
		case FRONT:
			return BOTTOM;
			break;
		case BACK:
			return BOTTOM;
			break;
		case LEFT:
			return BOTTOM;
			break;
		case RIGHT:
			return BOTTOM;
			break;
		case TOP:
			return FRONT;
			break;
		case BOTTOM:
			return BACK;
			break;
		default:
			break;
		}
		break;
	case LEFT:
		switch (side) {
		case FRONT:
			return Side::LEFT;
			break;
		case BACK:
			return Side::RIGHT;
			break;
		case LEFT:
			return Side::BACK;
			break;
		case RIGHT:
			return Side::FRONT;
			break;
		case TOP:
			return Side::LEFT;
			break;
		case BOTTOM:
			return Side::LEFT;
			break;
		default:
			break;
		}
		break;
	case RIGHT:
		switch (side) {
		case FRONT:
			return Side::RIGHT;
			break;
		case BACK:
			return Side::LEFT;
			break;
		case LEFT:
			return Side::FRONT;
			break;
		case RIGHT:
			return Side::BACK;
			break;
		case TOP:
			return Side::RIGHT;
			break;
		case BOTTOM:
			return Side::RIGHT;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}*/

void Cube::cubeFaceTransfer(Cube& donor, Side side) {
	switch (side) {
	case FRONT:
		*this = donor;
		break;
	case BACK:
		front = donor.getSide(BACK);
		back = donor.getSide(FRONT);
		left = donor.getSide(RIGHT);
		right = donor.getSide(LEFT);
		top = donor.getSide(TOP);
		bottom = donor.getSide(BOTTOM);
		break;
	case LEFT:
		front = donor.getSide(LEFT);
		back = donor.getSide(RIGHT);
		left = donor.getSide(BACK);
		right = donor.getSide(FRONT);
		top = donor.getSide(TOP);
		bottom = donor.getSide(BOTTOM);
		break;
	case RIGHT:
		front = donor.getSide(RIGHT);
		back = donor.getSide(LEFT);
		left = donor.getSide(FRONT);
		right = donor.getSide(BACK);
		top = donor.getSide(TOP);
		bottom = donor.getSide(BOTTOM);
		break;
	case TOP:
		front = donor.getSide(TOP);
		back = donor.getSide(BOTTOM);
		left = donor.getSide(LEFT);
		right = donor.getSide(RIGHT);
		top = donor.getSide(BACK);
		bottom = donor.getSide(FRONT);
		break;
	case BOTTOM:
		front = donor.getSide(BOTTOM);
		back = donor.getSide(TOP);
		left = donor.getSide(LEFT);
		right = donor.getSide(RIGHT);
		top = donor.getSide(FRONT);
		bottom = donor.getSide(BACK);
		break;
	}
}

void Cube::cubeModifiedFaceTransfer(Cube& modified, Side side) {
	switch (side) {
	case FRONT:
		*this = modified;
		break;
	case BACK:
		back = modified.getSide(FRONT);
		front = modified.getSide(BACK);
		right = modified.getSide(LEFT);
		left = modified.getSide(RIGHT);
		top = modified.getSide(TOP);
		bottom = modified.getSide(BOTTOM);
		break;
	case LEFT:
		left = modified.getSide(FRONT);
		right = modified.getSide(BACK);
		back = modified.getSide(LEFT);
		front = modified.getSide(RIGHT);
		top = modified.getSide(TOP);
		bottom = modified.getSide(BOTTOM);
		break;
	case RIGHT:
		right = modified.getSide(FRONT);
		left = modified.getSide(BACK);
		front = modified.getSide(LEFT);
		back = modified.getSide(RIGHT);
		top = modified.getSide(TOP);
		bottom = modified.getSide(BOTTOM);
		break;
	case TOP:
		top = modified.getSide(FRONT);
		bottom = modified.getSide(BACK);
		left = modified.getSide(LEFT);
		right = modified.getSide(RIGHT);
		back = modified.getSide(TOP);
		front = modified.getSide(BOTTOM);
		break;
	case BOTTOM:
		bottom = modified.getSide(FRONT);
		top = modified.getSide(BACK);
		left = modified.getSide(LEFT);
		right = modified.getSide(RIGHT);
		front = modified.getSide(TOP);
		back = modified.getSide(BOTTOM);
		break;
		break;
	}
}

vector<vector<CubeColor>> Cube::getSide(Side side) {
	switch (side) {
	case FRONT:
		return front;
		break;
	case BACK:
		return back;
		break;
	case LEFT:
		return left;
		break;
	case RIGHT:
		return right;
		break;
	case TOP:
		return top;
		break;
	case BOTTOM:
		return bottom;
		break;
	default:
		break;
	}
}

void Cube::resetCube() {
	loadCube();
}

void Cube::display(Side side) {
	switch (side) {
	case FRONT:
		for (int i = 0; i < cubeSize; i++) {
			for (int j = 0; j < cubeSize; j++) {
				cout << front[i][j] << " ";
			}
			cout << endl;
		}
		break;
	case BACK:
		for (int i = 0; i < cubeSize; i++) {
			for (int j = 0; j < cubeSize; j++) {
				cout << back[i][j] << " ";
			}
			cout << endl;
		}
		break;
	case LEFT:
		for (int i = 0; i < cubeSize; i++) {
			for (int j = 0; j < cubeSize; j++) {
				cout << left[i][j] << " ";
			}
			cout << endl;
		}
		break;
	case RIGHT:
		for (int i = 0; i < cubeSize; i++) {
			for (int j = 0; j < cubeSize; j++) {
				cout << right[i][j] << " ";
			}
			cout << endl;
		}
		break;
	case TOP:
		for (int i = 0; i < cubeSize; i++) {
			for (int j = 0; j < cubeSize; j++) {
				cout << top[i][j] << " ";
			}
			cout << endl;
		}
		break;
	case BOTTOM:
		for (int i = 0; i < cubeSize; i++) {
			for (int j = 0; j < cubeSize; j++) {
				cout << bottom[i][j] << " ";
			}
			cout << endl;
		}
		break;
	case ALL:
		
		this->display(FRONT);

		cout << "FRONT" << endl;
		cout << endl;

		this->display(BACK);
		
		cout << "BACK" << endl;
		cout << endl;

		this->display(LEFT);

		cout << "LEFT" << endl;
		cout << endl;

		this->display(RIGHT);

		cout << "RIGHT" << endl;
		cout << endl;

		this->display(TOP);

		cout << "TOP" << endl;
		cout << endl;

		this->display(BOTTOM);

		cout << "BOTTOM" << endl;
		cout << endl;
		break;
	default:
		break;
	}
}//end display

int Cube::getSize() {	
	return cubeSize;
}

void Cube::operator=(Cube cube2) {
	front = cube2.front;
	back = cube2.back;
	left = cube2.left;
	right = cube2.right;
	top = cube2.top;
	bottom = cube2.bottom;
	cubeSize = cube2.getSize();
}