#ifndef _BULLET_H
#define _BULLET_H

#include "ScreenObject.h"
#include "Direction.h"

class Bullet : 	public ScreenObject
{
	char bullet = '*';
	Point position;
	Direction::value direction;

public:
	Bullet(const Point & p, const Direction::value & d) : position(p), direction(d) {};
	void Move(const Point & p){ position = p; }
	
	virtual char Type()const{ return 'b'; } // inherited  from the Screenobject class , returns the type of the screen object in this case p for player
	virtual void Draw()const; //inherited  from the Screenobject class draws the player
	virtual void Clear()const;//inherited  from the Screenobject class, removes the player char form the screen
	virtual Point GetPosition()const{ return position; }//inherited  from the Screenobject class, returns the current position of the player
	virtual unsigned int GetData()const { return bullet; } //inherited  from the Screenobject class but not really needed in this class
	virtual unsigned int GetLength()const{ return 1; } // inherited  from the Screenobject class, returns the length of the player symobl
};

#endif