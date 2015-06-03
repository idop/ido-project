//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// RowFlyers.h
// -------------
// 
// This is the Row Flyers creature, he flies to the left or to the right, and his sing is !
//
// Author: Ido Perry and Alex Odesser
// First version: 2015-05-29
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef _ROWFLYERS_H_
#define _ROWFLYERS_H_
#pragma once
#include "Creature.h"

const char ROWFLYERS_SIGN = '!';

class RowFlyers :
	public Creature
{

public:

	RowFlyers(const Point & p, const Direction::value & d) : Creature(p, d, ROWFLYERS_SIGN){};

};


#endif