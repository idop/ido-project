//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Creature.h
// -------------
// 
// 
//
// Author: Ido Perry and Alex Odesser
// First version: 2015-05-29
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef _CREATURE_H
#define _CREATURE_H

#include "MovingScreenObject.h"

class Creature : public MovingScreenObject
{

public:
	Creature(const Point & p, const Direction::value & d) : MovingScreenObject(p, d) {};
	~Creature(){};

	virtual void Draw()const override = 0; //inherited  from the Screenobject class draws the player
	virtual void Collesion() override = 0;
	virtual void Move(const Point & p) override = 0;
};

#endif