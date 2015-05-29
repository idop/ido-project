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

class Bullet : 	public MovingScreenObject
{
	char bullet = '*';
	bool isLive;

public:
	Bullet(const Point & p, const Direction::value & d) : MovingScreenObject(p, d), isLive(true) {};
	~Bullet(){};

	virtual void Draw()const override; //inherited  from the Screenobject class draws the player
	virtual void Collesion() override{ isLive = false; };

	virtual void Move(const Point & p) override;
};

#endif