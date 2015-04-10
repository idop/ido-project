//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Point.h
// -------------
// simple class to store screen points
//
// Author: Ido Perry
// First version: 2015-03-29
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef _POINT_H_
#define _POINT_H_


class Point
{
	int x, y;
public:
	Point(){}
	Point(const Point & p):x(p.getX()),y(p.getY()){};
	Point(int x1, int y1) :x(x1), y(y1){}
	int getX()const{ return x;}
	int getY()const{ return y;}
	void setX(int x1){ x = x1; }
	void setY(int y1){ y = y1; }
};
#endif
