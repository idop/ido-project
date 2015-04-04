//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Screen.cpp
// -------------
// This class  will store all the dynemic objects in the screen
// the calss will also check for collisions , rederaw the dyemic part of the screen after continuing the game form the sub manu , etc..
//
// Author: Ido Perry
// First version: 2015-04-04
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Screen.h"
#include <iostream>
using namespace std;

Screen::Screen()
{
	for (int i = 0; i < SCREEN_WIDTH; ++i)
		for (int j = 0; j < SCREEN_HIGHT; ++j)
			screen[i][j] = NULL;
}


void Screen::CleanScreen()
{

}
// this function will draw the
void Screen::DrawScrean()const
{
	/*
	unsigned int numSolution;
	for (int i = X_OFFSET; i < SCREEN_WIDTH; ++i)
		for (int j = Y_OFFSET; j < SCREEN_HIGHT; ++j)
		{
			if (screen[i][j] != NULL)
			{

			}
		}
		*/
}