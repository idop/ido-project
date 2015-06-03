//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Point.h
// -------------
// simple class to store screen points
//
// Author: Ido Perry and Alex Odesser
// First version: 2015-03-29
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef _POINT_H_
#define _POINT_H_

#pragma once

#include "Direction.h"
#include <math.h>
const int UPPER_LIMIT = 3;
const int LOWER_LIMIT = 23;
const int LEFT_LIMIT = 0;
const int RIGHT_LIMIT = 79;

class Point
{
	int x, y;
	int numberOfXStpes(const Point & p) const;
	int numberOfYSteps(const Point & p) const;
	int numberOfStepsTo(const Point & p) const{ return (this->numberOfXStpes(p) + this->numberOfYSteps(p)); };
	bool needToCrossMoreThenHalfTheScreen(const int & num, const int & size)const{ return (abs(num) > size / 2); };
public:
	Point(){}
	Point(const Point & p) :x(p.GetX()), y(p.GetY()){}
	Point(int x1, int y1) :x(x1), y(y1){}
	int GetX()const{ return x; }
	int GetY()const{ return y; }
	void SetX(int x1){ x = x1; }
	void SetY(int y1){ y = y1; }
	Point GetPointToMoveFromDirection(const Direction::value & direction);
	int getXDiffrence(const Point & targetPoint)const { return (this->GetX() - targetPoint.GetX()); }; // returns the diffrence in x values of 2 points
	int getYDiffrence(const Point & targetPoint)const { return (this->GetY() - targetPoint.GetY()); };// returns the diffrence in Y values of 2 points
	Point getCloserPoint(const Point &p1, const Point & p2) const
	{
		return (this->numberOfStepsTo(p1) < this->numberOfStepsTo(p2) ? p1 : p2);
	}; // returns the point that is closer to this (p1 or p2)

	bool operator==(const Point & p)const{ return ((this->GetX() == p.GetX()) && (this->GetY() == p.GetY())); };

};


#endif
