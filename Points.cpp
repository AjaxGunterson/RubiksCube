#include "Points.h"
using namespace std;

/*Default Constructor*/
Point::Point() {
	/*Default rubik's cube dimensions*/
	this->load(points, 3);
}

/*Explicit Constructor*/
Point::Point(int dimension) {
	this->load(points, dimension);
}

void Point::load(vector<float> &points, int dimension) {
	

	/*hacked a solution to probably get rid of the black 
	* hell holes forever since loop now uses ints
	*/

	//arbritary names, sorry :(
	float k = 1,
		p = -1;
	
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			/*bottom left*/
			points.push_back(p);
			points.push_back(k - (1.0f / dimension) * 2);
			/*top left*/
			points.push_back(p);
			points.push_back(k);
			/*top right*/
			points.push_back(p + (1.0f / dimension) * 2);
			points.push_back(k);
			/*bottom right*/
			points.push_back(p + (1.0f / dimension) * 2);
			points.push_back(k - (1.0f / dimension) * 2);
	
			p += (1.0f / dimension) * 2;
		}

		p = -1;
		k -= (1.0f / dimension) * 2;
	}

}

vector<float> Point::getPoints() {
	return points;
}