//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ColumnFlyers.h
// -------------
// 
// 
//
// Author: Ido Perry and Alex Odesser
// First version: 2015-05-29
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#pragma once
#ifndef _COLUMNFLYERS_H_
#define _COLUMNFLYERS_H_

#include "Creature.h"
class ColumnFlyers :
	public Creature
{
	const char sign = '$';

public:
	ColumnFlyers(const Point & p, const Direction::value & d) : Creature(p, d){};
	virtual ~ColumnFlyers();

	virtual void Draw()const override; //inherited  from the Screenobject class draws the player
	virtual void Collesion() override{ };
	virtual void Move(const Point & p) override;


};

#endif
