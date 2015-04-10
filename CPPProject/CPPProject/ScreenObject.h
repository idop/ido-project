//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ScreenObject.h
// -------------
// This is a base class for screen object 
// all the dynamic objects that are displeyed on the screen will inheret form this class (Players, SulotionOptions , etc..)
//
// Author: Ido Perry and Alex Odesser
// First version: 2015-04-04
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#ifndef _SCREEN_OBJECT_H_
#define _SCREEN_OBJECT_H_

#include "Point.h"
class ScreenObject
{

public:
	virtual char Type()const = 0; // we will have 2 types for the first EX 'p' for player and  n - number for possible solution
	virtual void Draw()const = 0; 
	virtual void Clear()const = 0;
	virtual Point GetPosition()const = 0;
	virtual unsigned int GetData()const = 0;
	virtual unsigned int GetLength()const = 0;
};

#endif