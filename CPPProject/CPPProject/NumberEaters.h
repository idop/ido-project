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

#ifndef _NUMBEREATERS_H_
#define _NUMBEREATERS_H_
#pragma once
#include "Creature.h"
#include "Point.h"

const char NUMBEREATERS_SIGN = '%';

class NumberEaters :
	public Creature
{
	char sign = '%';

public:

	NumberEaters(const Point & p, const Direction::value & d) : Creature(p, d, NUMBEREATERS_SIGN){};
	virtual ~NumberEaters();

	virtual void Draw()const override; //inherited  from the Screenobject class draws the player
	virtual void Collesion() override{ };
	virtual void Move(const Point & p) override;
	virtual Point getPointToMove() override { return this->GetPosition().GetPointToMoveFromDirection(direction); };

};

#endif