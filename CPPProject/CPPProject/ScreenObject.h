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

class ScreenObject {
	char type;
	Point position;

public:
	virtual ~ScreenObject () {
	}

	ScreenObject ( const char & t , const Point & p ) : type ( t ), position ( position ) {
	}

	virtual void Draw ()const = 0; // draw funciton for the screenobject the classes who will inheret this class will implement this class

	virtual unsigned int GetData ()const = 0; // get the numral value of the current screenobject( needed only for the solution posabilities) the classes who will inheret this class will implement this class
	virtual unsigned int GetLength ()const = 0; // get char length of the current screenobject, the classes who will inheret this class will implement this class
	virtual void Collesion () = 0; // each object will implement its own collesion handeling

	virtual void Clear()const
	{
		gotoxy(GetPosition().getX(), GetPosition().getY());
		cout << ' ';
	}

	Point GetPosition ()const {
		return position;
	} // get the screen object current position;

	char GetType ()const {
		return type;
	} // we will have 2 types for EX 1 the 'p' for player and  n - number for possible solution

	void SetPosition ( const Point & p ) {
		position = p;
	}

	void SetType ( const char & t ) {
		type = t;
	}
};

#endif