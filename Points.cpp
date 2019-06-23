#include "Points.h"
using namespace std;

const int POINTS_PER_CUBE = 3;

/*Default Constructor*/
Point::Point() {
	/*Default rubik's cube dimensions*/
	//points.resize(3 * 3 * POINTS_PER_CUBE);
	this->load(points, 3);
}

/*Explicit Constructor*/
Point::Point(int dimension) {
	//points.resize(POINTS_PER_CUBE * dimension * dimension);
	this->load(points, dimension);
}

void Point::load(vector<float> &points, int dimension) {
	for (float i = 1; i > -1; i -= (float(1) / dimension) * 2) {
		for (float j = -1; j < 1; j += (float(1) / dimension) * 2) {
			/*bottom left*/
			points.push_back(float(j));
			points.push_back(float(i) - (float(1) / dimension) * 2);
			/*top left*/
			points.push_back(float(j));
			points.push_back(float(i));
			/*top right*/
			points.push_back(float(j) + (float(1) / dimension) * 2);
			points.push_back(float(i));
			/*bottom right*/
			points.push_back(float(j) + (float(1) / dimension) * 2);
			points.push_back(float(i) - (float(1) / dimension) * 2);
			
		}
	}
}

vector<float> Point::getPoints() {
	return points;
}