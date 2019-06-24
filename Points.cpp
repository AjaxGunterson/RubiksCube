#include "Points.h"
using namespace std;

/*Default Constructor*/
Point::Point() {
	/*Default rubik's cube dimensions*/
	this->load(points, demarcations,  3);
}

/*Explicit Constructor*/
Point::Point(int dimension) {
	this->load(points, demarcations, dimension);
}

void Point::load(vector<float> &points, vector<float> &demarcations, int dimension) {
	

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

	k = 1;
	p = -1;

	demarcations.push_back(-1);
	demarcations.push_back(1);
	demarcations.push_back(-1);
	demarcations.push_back(-1);

	//vertical lines
	for (int i = 0; i < dimension - 1; i++) {
		p += (1.0f / dimension) * 2;
		demarcations.push_back(p);
		demarcations.push_back(1);
		demarcations.push_back(p);
		demarcations.push_back(-1);
	}

	demarcations.push_back(1);
	demarcations.push_back(1);
	demarcations.push_back(1);
	demarcations.push_back(-1);

	demarcations.push_back(-1);
	demarcations.push_back(1);
	demarcations.push_back(1);
	demarcations.push_back(1);

	//horizontal lines
	for (int i = 0; i < dimension - 1; i++) {
		k -= (1.0f / dimension) * 2;
		demarcations.push_back(-1);
		demarcations.push_back(k);
		demarcations.push_back(1);
		demarcations.push_back(k);
	}

	demarcations.push_back(-1);
	demarcations.push_back(-1);
	demarcations.push_back(1);
	demarcations.push_back(-1);
	

}

vector<float> Point::getDemarcations() {
	return demarcations;
}

vector<float> Point::getPoints() {
	return points;
}