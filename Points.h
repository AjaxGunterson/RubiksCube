/*---RubiksCube.h----------------------------------------------------------------
A header file for enumerated data type RubiksCube

Written by:	Nolan Ripplinger
Written For:
---------------------------------------------------------------------------*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#ifndef POINTS
#define POINTS

class Point {
public:
	Point();
	Point(int dimension);
	vector<float> getPoints();
	vector<float> getDemarcations();
private:
	void load(vector<float> &points, vector<float> &demarcations, int dimension);
	vector<float> points;
	vector<float> demarcations;
};

//Prototypes

#endif