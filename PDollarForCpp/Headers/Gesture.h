#ifndef _GESTURE_H_
#define _GESTURE_H_

#include "Point.h"
#include <string>
#include <vector>
#define MAX_SAMPLING_RESOLUTION 32

using namespace std;

class Gesture
{
public:
	
	Gesture(vector<Point *> point, string gestureName = "");
	~Gesture();

	vector<Point *> m_Points;
	string m_Name;

	vector<Point *> resamplePoints(vector<Point *> point, int n);

private:
	vector<Point *> scale(vector<Point *>point);
	vector<Point *> translateTo(vector<Point *> point, Point* centroid);
	Point* getCentroid(vector<Point *> point);
	double pathLength(vector<Point *> point);

	
};

#endif