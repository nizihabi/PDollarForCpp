// PDollarForCpp.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Headers\PDollarForCpp.h"
#include "Headers\Geometry.h"

Gesture *createGesture(vector<Point *> point, string gestureName)
{
	return new Gesture(point, gestureName);
}

string classify(Gesture *gesture, vector<Gesture *> gestureSet)
{
	double minDistance = DBL_MAX;
	string gestureClass = "";
	for (int i = 0; i < gestureSet.size(); i++)
	{
		double dist = cloudMatch(gesture->m_Points, gestureSet[i]->m_Points);
		if (minDistance > dist)
		{
			minDistance = dist;
			gestureClass = gestureSet[i]->m_Name;
		}
	}
	return gestureClass;
}

double cloudMatch(vector<Point *> points1, vector<Point *> points2)
{
	int n = points1.size();  //此时points1 和 points2 有着一样的点数
	double eps = 0.5f;
	int step = (int)(floor(pow(n, 1 - eps)));
	double minDistance = DBL_MAX;
	for (int i = 0; i < n; i+= step)
	{
		double dist1 = cloudDistance(points1, points2,i);
		double dist2 = cloudDistance(points2, points1,i);
		minDistance = min(minDistance, min(dist1, dist2));
	}
	return minDistance;
}

double cloudDistance(vector<Point *> points1, vector<Point *> points2, int startIndex)
{
	int n = points1.size();       
	vector<bool> match(n); 
	match.clear();

	double sum = 0;  // computes the sum of distances between matched points (i.e., the distance between the two clouds)
	int i = startIndex;
	do
	{
		int index = -1;
		double minDistance = DBL_MAX;
		for (int j = 0; j < n; j++)
		if (!match[j])
		{
			float dist = Geometry::SqrEuclideanDistance(points1[i], points2[j]);  // use squared Euclidean distance to save some processing time
			if (dist < minDistance)
			{
				minDistance = dist;
				index = j;
			}
		}
		match[index] = true; // point index from the 2nd cloud is matched to point i from the 1st cloud
		double weight = 1 - ((i - startIndex + n) % n) / (1 * n);
		sum += weight * minDistance; // weight each distance with a confidence coefficient that decreases from 1 to 0
		i = (i + 1) % n;
	} while (i != startIndex);

	return sum;
}
