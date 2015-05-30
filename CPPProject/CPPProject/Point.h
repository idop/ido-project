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

const int UPPER_LIMIT = 3;
const int LOWER_LIMIT = 23;
const int LEFT_LIMIT = 0;
const int RIGHT_LIMIT = 79;

class Point
{
	int x, y;
public:
	Point(){}
	Point(const Point & p) :x(p.GetX()), y(p.GetY()){};
	Point(int x1, int y1) :x(x1), y(y1){}
	int GetX()const{ return x; }
	int GetY()const{ return y; }
	void SetX(int x1){ x = x1; }
	void SetY(int y1){ y = y1; }
	Point GetPointToMoveFromDirection(const Direction::value & direction);
	int getXDiffrence(const Point & targetPoint){ return (this->GetX() - targetPoint.GetX()); }; // returns the diffrence in x values of 2 points
	int getYDiffrence(const Point & targetPoint){ return (this->GetY() - targetPoint.GetY()); }; // returns the diffrence in Y values of 2 points

};


#endif
