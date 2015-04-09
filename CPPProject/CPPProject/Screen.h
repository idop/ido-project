//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Screen.h
// -------------
// This class  will store all the dynemic objects in the screen
// the calss will also check for collisions , rederaw the dyemic part of the screen after continuing the game form the sub manu , etc..
//
// Author: Ido Perry
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

class Screen
{
	ScreenObject * screen[SCREEN_WIDTH][SCREEN_HIGHT];

public:
	Screen();
	ScreenObject * GetScreenObject(const int & x, const int & y)const{ return screen[x][y]; }
	void CleanScreen(); // when level is done
	void DrawScrean()const;
	void SetPositionForScreenObject(ScreenObject *object);
	void ClearScreenObject(ScreenObject *object);
	void CreateNewSolutionPosability(const unsigned int & currentLevel);
};

#endif