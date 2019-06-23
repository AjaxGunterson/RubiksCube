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
	for (double i = 1; i > -1; i -= (1.0f / dimension) * 2) {
		for (double j = -1; j < 1; j += (1.0f / dimension) * 2) {
			/*bottom left*/
			points.push_back(float(j));//current tile's left x
			points.push_back(float(i) - (1.0f / dimension) * 2);//current tile's lower y
			/*top left*/
			points.push_back(float(j));//current tile's left x
			points.push_back(float(i));//current tile's upper y
			/*top right*/
			points.push_back(float(j) + (1.0f / dimension) * 2);//current tile's right x
			points.push_back(float(i));//current tile's upper y
			/*bottom right*/
			points.push_back(float(j) + (1.0f / dimension) * 2);//current tile's right x
			points.push_back(float(i) - (1.0f / dimension) * 2);//current tile's lower y
			cout << "Inner; " << "j = " << j << endl;
		}
		//cout << "Outer; " << "i = " << i << endl;
	}
}

vector<float> Point::getPoints() {
	return points;
}