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