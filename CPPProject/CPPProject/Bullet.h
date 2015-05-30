//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Bullet.h
// -------------
// This class creates the the bullets that the players will be able to shoot while playing.
// This class will handle the oporation of the bullet
//
// Author: Ido Perry and Alex Odesser
// First version: 2015-05-03
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef _BULLET_H
#define _BULLET_H

#include "MovingScreenObject.h"
#include "Direction.h"

const char BULLET_SIGN = '*';

class Bullet : 	public MovingScreenObject
{



public:
	Bullet(const Point & p, const Direction::value & d) : MovingScreenObject(p, d, BULLET_SIGN){};
	~Bullet(){};

};

#endif
