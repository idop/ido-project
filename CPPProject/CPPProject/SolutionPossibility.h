//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//SolutionPosabilty.h
// -------------
// This class  will store all the dynemic objects in the screen
// the calss will also check for collisions , rederaw the dyemic part of the screen after continuing the game form the sub manu , etc..
//
// Author: Ido Perry and Alex Odesser
// First version: 2015-04-04
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#ifndef _SOLUTION_POSABILITY_H_
#define __SOLUTION_POSABILITY_H_

#include "ScreenObject.h"



unsigned int NumDigits(unsigned int num);//global function to get the number of digits of a number

class SolutionPosabilty :public ScreenObject
{
	const unsigned int data;
	const Point position;
public:
	SolutionPosabilty(const unsigned int & num, const Point & p) :data(num), position(p){}
	virtual char Type()const{ return 'n'; } // inherited  from the Screenobject class , returns the type of the screen object in this case n for  the number of the solution posabillity
	virtual void Draw()const ;//inherited  from the Screenobject class draws solution posabillity
	virtual void Clear()const ; //inherited  from the Screenobject class, removes the solution posabillity form the screen
	virtual Point GetPosition()const { return position; } //inherited  from the Screenobject class, returns the current position of the first number of solution posabillity
	virtual unsigned int GetData()const { return data;} //inherited  from the Screenobject class . returns the date of the solution posabillity
	virtual unsigned int GetLength()const{ return NumDigits(data); } // inherited  from the Screenobject class, returns the length(number of digits) of the solution posabillity symobl
	virtual void GotHit(){  }
};
#endif
