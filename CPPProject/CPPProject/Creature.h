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
	Creature(const Point & p, const Direction::value & d, const char &sign) : MovingScreenObject(p, d, sign) {};
	~Creature(){};
	virtual void Collesion() override = 0;

};

#endif