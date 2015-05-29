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

#ifndef _ROWFLYERS_H_
#define _ROWFLYERS_H_
#pragma once
#include "Creature.h"
class RowFlyers :
	public Creature
{

	char sign = '!';
public:

	RowFlyers(const Point & p, const Direction::value & d) : Creature(p, d){};
	virtual ~RowFlyers();

	virtual void Draw()const override; //inherited  from the Screenobject class draws the player
	virtual void Collesion() override{ };
	virtual void Move(const Point & p) override;


};

inline RowFlyers::~RowFlyers()
{
}

inline void RowFlyers::Draw() const
{
}

inline void RowFlyers::Move(const Point& p)
{
}

#endif