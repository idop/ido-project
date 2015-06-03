//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ScreenObject.h
// -------------
// This is a base class for screen object 
// all the dynamic objects that are displeyed on the screen will inheret form this class (Players, SulotionOptions , etc..)
//
// Author: Ido Perry and Alex Odesser
// First version: 2015-04-04
// Second version: 2015-05-16
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#ifndef _SCREEN_OBJECT_H_
#define _SCREEN_OBJECT_H_

#include "Point.h"
#include "io_utils.h"
#include <iostream>

using namespace std;

class ScreenObject {
	Point position;
	int lenght;
	bool markForDestruction;

public:
	
	ScreenObject (const Point & p , const int & len) :  position (p), lenght(len), markForDestruction(false) {
	}

	virtual void Draw ()const = 0; // draw funciton for the screenobject the classes who will inheret this class will implement this class
	virtual unsigned int GetData ()const = 0; // get the numral value of the current screenobject( needed only for the solution posabilities) the classes who will inheret this class will implement this class	
	virtual bool IsSolutionPossibility(){ return false; }; // used only to know if the screenobject is a solutionPossivility object

	virtual void Clear()const //clears the object from the screen
	{
		gotoxy(GetPosition().GetX(), GetPosition().GetY());
		cout << ' ';
	}

	unsigned int GetLength()const{ return lenght; }; // get char length of the current screenobject, the classes who will inheret this class will implement this class

	Point GetPosition ()const {
		return position;
	} // get the screen object current position;

	// set a specific position for an item
	void SetPosition ( const Point & p ) {
		position = p;
	}

	//checks if the object is after collision
	bool isMarkForDestruction()
	{
		return markForDestruction;
	}
	//marks the object if he was involved in a collision with another object.
	virtual void destroy()
	{
		markForDestruction = true;
	}
	//restors the status if like the player object the object has several lifes.
	void revive()
	{
		markForDestruction = false;
	}
};

#endif