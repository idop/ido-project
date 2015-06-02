//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Screen.h
// -------------
// This class  will store all the dynemic objects in the screen
// the calss will also check for collisions , rederaw the dyemic part of the screen after continuing the game form the sub manu , etc..
//
// Author: Ido Perry and Alex Odesser
// First version: 2015-04-04
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "ScreenObject.h"


const int SCREEN_WIDTH = 80; // screen max x position
const int SCREEN_HIGHT = 24; // screen max y position
const int X_OFFSET = 0; //  x offset position for the dynemic part of the screen
const int Y_OFFSET = 3; //  y offset position for the dynemic part of the screen

class Screen {
	int numberOfSolutionPossibilities;
	ScreenObject * screen[SCREEN_WIDTH][SCREEN_HIGHT];
	Point latestSolutionPosabilityPosition;

	bool currentTargetDied ( const Point & currentTargetPosition ) const {
		return (screen[currentTargetPosition.GetX()][currentTargetPosition.GetY()] == nullptr);
	};

	int getValidXValue ( int x ) const;
	int getValidYValue ( int y ) const;

public:
	~Screen () {
		CleanScreen();
	}

	Screen();

	ScreenObject* GetScreenObject ( const int & x , const int & y )const {
		return screen[x][y];
	} // returns a screen object in a spesific point (x,y)
	void CleanScreen (); // when level is done sets all the pointers to null and free the moemory of all dynamic alolocated objects
	void DrawScrean ()const; // draws the dyemic part of the screen from (0,3) to (79,23)
	void SetPositionForScreenObject ( ScreenObject * object ); // set the all the relevant positions in the matrix to point to a specific screenobject
	void ClearScreenObject ( ScreenObject * object ); // removes a spesific screenobject from the matrix (frees memoery when needed)
	void CreateNewSolutionPosability ( const unsigned int & currentLevel ); // dynamicly creates a new solution posability and places it on the screen


	Point findClosestSolutionPossibility ( const Point currentPosition ) const;
	Point findClosestTarget ( const Point & currentPosition , const Point & currentTargetPosition ) const;
};

#endif
