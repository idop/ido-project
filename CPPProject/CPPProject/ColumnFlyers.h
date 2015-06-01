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

const char COLUMNFLYERS_SIGN = '$';

class ColumnFlyers :
	public Creature
{

public:
	ColumnFlyers(const Point & p, const Direction::value & d) : Creature(p, d, COLUMNFLYERS_SIGN){};
	virtual ~ColumnFlyers(){};
};

#endif
