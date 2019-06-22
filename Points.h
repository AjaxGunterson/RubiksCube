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
private:
	void load(vector<float> &points, int dimension);
	vector<float> points;
};

//Prototypes

#endif