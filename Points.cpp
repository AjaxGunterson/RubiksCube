#include "Points.h"
using namespace std;

const int POINTS_PER_CUBE = 8;

/*Default Constructor*/
Point::Point() {
	/*Default rubik's cube dimensions*/
	points.resize(3 * 3 * POINTS_PER_CUBE);
	this->load(points, 3);
}

/*Explicit Constructor*/
Point::Point(int dimension) {
	points.resize(POINTS_PER_CUBE * dimension * dimension);
	this->load(points, dimension);
}

void Point::load(vector<float> &points, int dimension) {
	for (int i = 0; i < points.size(); i++) {

	}
}


/*void Point::triangle(float* &points) {
	
	// Points for triangle
	float points[8] = {

		// bottom Left
		-0.2f, -0.2f,

		// top left
		-0.2f, 0.2f,

		//top right
		0.2f, 0.2f,

		//bottom Right
		0.2f, -0.2f
	};
}*/