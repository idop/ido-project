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

public:
	SolutionPosabilty(const Point& p, const unsigned int& num) : ScreenObject(p, NumDigits(num)), data(num)
	{
	};

	virtual void Draw()const override;//inherited  from the Screenobject class draws solution posabillity
	virtual void Clear()const override; //inherited  from the Screenobject class, removes the solution posabillity form the screen
	virtual unsigned int GetData()const override; //inherited  from the Screenobject class . returns the date of the solution posabillity

};
#endif
