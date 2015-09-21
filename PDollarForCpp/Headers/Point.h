#ifndef _POINT_H_
#define _POINT_H_

class Point
{
public:
	Point();
	Point(double x, double y, int strokeid) :m_X(x), m_Y(y), m_StrokeID(strokeid)
	{
	}

	double getX() const
	{
		return m_X;
	}

	double getY() const
	{
		return m_Y;
	}

	int getStrokeID() const
	{
		return m_StrokeID;
	}

	~Point();

private:
	double m_X = 0;
	double m_Y = 0;
	int m_StrokeID = 0;
};

#endif