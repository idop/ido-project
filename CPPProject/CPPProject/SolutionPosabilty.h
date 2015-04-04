//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//SolutionPosabilty.h
// -------------
// This class  will store all the dynemic objects in the screen
// the calss will also check for collisions , rederaw the dyemic part of the screen after continuing the game form the sub manu , etc..
//
// Author: Ido Perry
// First version: 2015-04-04
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#ifndef _SOLUTION_POSABILITY_H_
#define __SOLUTION_POSABILITY_H_

#include "ScreenObject.h"





class SolutionPosabilty :public ScreenObject
{
	const unsigned int data;
	const Point position;
public:
	SolutionPosabilty(const unsigned int & num, const Point & p) :data(num), position(p){}
	virtual char Type()const{ return 'n'; } // we will have 2 types for the first EX 'p' for player and  n - number for possible solution
	virtual void Draw()const ;
	virtual void Clear()const ;
	virtual Point GetPosition()const { return position; }
	virtual unsigned int GetData()const { return data;}
	friend unsigned int NumDigits(unsigned int num);//global function to get the number of digits of a number
};
#endif
