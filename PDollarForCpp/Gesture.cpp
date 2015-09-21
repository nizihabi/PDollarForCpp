#include "Headers\Gesture.h"
#include "Headers\Geometry.h"
#include <math.h>
#include "stdafx.h"
using namespace std;

Gesture::Gesture(vector<Point *> point, string gestureName)
{
	m_Name = gestureName;

	m_Points = scale(point);
	m_Points = translateTo(m_Points, getCentroid(point));
	m_Points = resamplePoints(m_Points,MAX_SAMPLING_RESOLUTION);
}

Gesture::~Gesture()
{
	if (!m_Points.empty())
	{
		m_Points.clear();
	}
}

//Performs scale normalization with shape preservation into [0..1]x[0..1]
//
vector<Point *> Gesture::scale(vector<Point *> point)
{
	double minX = DBL_MAX;
	double minY = DBL_MAX;
	double maxX = DBL_MIN;
	double maxY = DBL_MIN;
	double scaleX, scaleY, scale;
	for (int i = 0; i < point.size(); i++)
	{
		if (minX > point[i]->getX())
			minX = point[i]->getX();
		if (minY > point[i]->getY())
			minY = point[i]->getY();
		if (maxX < point[i]->getX())
			maxX = point[i]->getX();
		if (maxY < point[i]->getY())
			maxY = point[i]->getY();
	}
	scaleX = maxX - minX;
	scaleY = maxY - minY;

	vector<Point *> newPoint;
	
	if (scaleX > scaleY)
		scale = scaleX;
	else
		scale = scaleY;

	for (int i = 0; i < point.size(); i++)
	{
		newPoint.push_back(new Point((point[i]->getX() - minX) / scale, (point[i]->getY() - minY) / scale, point[i]->getStrokeID()));
	}
	return newPoint;

}

vector<Point *> Gesture::translateTo(vector<Point *> point, Point *centroid)
{
	vector<Point *> newPoint;

	for (int i = 0; i < point.size(); i++)
	{
		newPoint.push_back(new Point(point[i]->getX() - centroid->getX(), point[i]->getY() - centroid->getY(), point[i]->getStrokeID()));
	}
	return newPoint;
}

Point *Gesture::getCentroid(vector<Point *> point)
{
	double cx = 0, cy = 0;
	for (int i = 0; i < point.size(); i++)
	{
		cx += point[i]->getX();
		cy += point[i]->getY();
	}
	return new Point(cx / point.size(), cy / point.size(), 0);
}

double Gesture::pathLength(vector<Point *>point)
{
	double length = 0;
	for (int i = 1; i < point.size(); i++)
	{
		if (point[i]->getStrokeID() == point[i - 1]->getStrokeID())
			length += Geometry::SqrEuclideanDistance(point[i], point[i - 1]);
	}
	return length;
}

vector<Point *> Gesture::resamplePoints(vector<Point *> point, int n)
{
	vector<Point *> newPoint;
	newPoint.push_back(new Point(point[0]->getX(),point[0]->getY(),point[0]->getStrokeID()));
	
	double I = pathLength(point) / n;
	double D = 0;
	int pointNums = 1;

	for (int i = 1; i < point.size(); i++)
	{
		if (point[i - 1]->getStrokeID() == point[i]->getStrokeID())
		{
			double d = Geometry::EuclideanDistance(point[i], point[i - 1]);
			if (D + d >= I)
			{
				Point *firstPoint = point[i - 1];
				while (D + d >= I)
				{
					double t = (I - D) / d;

					if (isnan(t))
						t = 0.5;
					else
					{
						if (t < 0)
							t = 0;
						else if (t > 1)
							t = 1;
					}		

					double newX = (1 - t) * firstPoint->getX() + t * point[i]->getX();
					double newY = (1 - t) * firstPoint->getY() + t * point[i]->getY();
					newPoint.push_back(new Point(newX, newY, point[i]->getStrokeID()));
					pointNums++;

					d = D + d - I;
					D = 0;
					firstPoint = newPoint[pointNums - 1];
				}
			}
			else
				D += d;
		}
	}

	if (pointNums == n - 1)
		newPoint.push_back(point[n - 1]);

	return newPoint;
}