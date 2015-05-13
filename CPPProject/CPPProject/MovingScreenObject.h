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

class MovingScreenObject : public ScreenObject{

	Direction::value direction;

public:
	virtual void Move(const Point & p) = 0;
	virtual Direction::value getDirection() const = 0;
};

#endif