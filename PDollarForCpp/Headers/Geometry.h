#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "Point.h"
#include <math.h>


class Geometry
{
public:
	static double SqrEuclideanDistance(Point *a, Point *b)
	{
		return pow((a->getX() - b->getX()), 2) + pow((a->getY() - b->getY()), 2) ;
	}

	static double EuclideanDistance(Point *a, Point *b)
	{
		return sqrt(SqrEuclideanDistance(a, b));
	}
};

#endif