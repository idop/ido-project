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

public:
	virtual ~ScreenObject () {
	}

	ScreenObject (const Point & p ) :  position ( position ) {
	}

	virtual void Draw ()const = 0; // draw funciton for the screenobject the classes who will inheret this class will implement this class

	virtual unsigned int GetData ()const = 0; // get the numral value of the current screenobject( needed only for the solution posabilities) the classes who will inheret this class will implement this class
	virtual unsigned int GetLength ()const = 0; // get char length of the current screenobject, the classes who will inheret this class will implement this class
	virtual void Collesion () = 0; // each object will implement its own collesion handeling
	virtual bool IsSolutionPossibility(){ return false; }; // used only to know if the screenobject is a solutionPossivility object
	virtual void Clear()const
	{
		gotoxy(GetPosition().GetX(), GetPosition().GetY());
		cout << ' ';
	}

	Point GetPosition ()const {
		return position;
	} // get the screen object current position;


	void SetPosition ( const Point & p ) {
		position = p;
	}
	

};

#endif