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
	virtual char Type()const = 0; // we will have 2 types for EX 1 the 'p' for player and  n - number for possible solution
	virtual void Draw()const = 0;  // draw funciton for the screenobject the classes who will inheret this class will implement this class
	virtual void Clear()const = 0;// clear the screan from the current screenobject classes who will inheret this class will implement this class
	virtual Point GetPosition()const = 0; // get the screen object current position classes who will inheret this class will implement this class
	virtual unsigned int GetData()const = 0;// get the numral value of the current screenobject( needed only for the solution posabilities) the classes who will inheret this class will implement this class
	virtual unsigned int GetLength()const = 0;// get char length of the current screenobject, the classes who will inheret this class will implement this class
};

#endif