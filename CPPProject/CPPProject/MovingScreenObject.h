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

class MovingScreenObject : public ScreenObject
{
	Direction::value direction;

public:

	MovingScreenObject(const Point& p, const Direction::value& d) : ScreenObject(p), direction(d)
	{
	};

	virtual void Move(const Point& p) = 0;
	virtual void Draw()const override = 0; // draw funciton for the screenobject the classes who will inheret this class will implement this class
	virtual void Collesion() override = 0; // each object will implement its own collesion handeling

	virtual unsigned int GetData()const override
	{
		return 0;
	}; // get the numral value of the current screenobject( needed only for the solution posabilities) the classes who will inheret this class will implement this class

	virtual unsigned int GetLength()const override
	{
		return 1;
	} // inherited  from the Screenobject class, returns the length of the player symobl

	void SetDirection(const Direction::value& d)
	{
		direction = d;
	}

	Direction::value GetDirection()const
	{
		return direction;
	}

	virtual Point getPointToMove(){ return this->GetPosition().GetPointToMoveFromDirection(direction); };

};

#endif
