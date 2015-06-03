//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// NumberEaters.h
// -------------
// 
// This Class reporesents the number eaters creatures, they are identified with the sign %
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
#include "Screen.h"

const char NUMBEREATERS_SIGN = '%';

class NumberEaters :
	public Creature
{
	char sign;
	Point targetPosition; // used to store the target position
	const Screen * CurrentScreen;
	void setDirectionToTargetPosition();
	bool isPositive(const int & num)const{ return (num > 0); }; // helper methood to set direcrtion 
	bool needToCrossMoreThenHalfTheScreen(const int & num , const int & size)const{ return (abs(num) > size/ 2); };
public:

	NumberEaters(const Point & p, const Direction::value & d, Screen * s) : Creature(p, d, NUMBEREATERS_SIGN),targetPosition(p), CurrentScreen(s){};
	virtual ~NumberEaters(){};
	virtual Point getPointToMove() override; // overide movingobject get the next point to move, this createre follwos a diffrent logic



};

#endif