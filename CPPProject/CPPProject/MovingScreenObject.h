//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// MovingScreenObject.h
// -------------
// This class inherits from screenObject, and is the father class for all moving objects.
// All Objects that should have the ability to move in the game will inherit this calss
//
// Author: Ido Perry and Alex Odesser
// First version: 2015-05-03
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef _MOVINGSCREENOBJECT_T_
#define _MOVINGSCREENOBJECT_T_

#include "ScreenObject.h"
#include "Point.h"
#include "Direction.h"

using namespace std;

const unsigned int MOVINGOBJECT_LENGTH = 1;

class MovingScreenObject : public ScreenObject
{
	Direction::value direction;
	const char sign;

public:

	MovingScreenObject(const Point& p, const Direction::value& d, const char & sign) : ScreenObject(p, MOVINGOBJECT_LENGTH), direction(d), sign(sign)
	{
	};

	virtual void Move(const Point& p);
	void Draw()const override; // draw funciton for the screenobject the classes who will inheret this class will implement this class

	virtual unsigned int GetData()const override
	{
		return 0;
	}; // get the numral value of the current screenobject( needed only for the solution posabilities) the classes who will inheret this class will implement this class


	void SetDirection(const Direction::value& d)
	{
		direction = d;
	}

	Direction::value GetDirection()const
	{
		return direction;
	}

	virtual Point getPointToMove()
	{
		Point a = GetPosition().GetPointToMoveFromDirection(direction);
		return a;
	};

};


#endif
