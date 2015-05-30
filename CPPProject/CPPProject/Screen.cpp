//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Screen.cpp
// -------------
// This class  will store all the dynemic objects in the screen
// the calss will also check for collisions , rederaw the dyemic part of the screen after continuing the game form the sub manu , etc..
//
// Author: Ido Perry and Alex Odesser
// First version: 2015-04-04
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Screen.h"
#include "SolutionPossibility.h"
#include "io_utils.h"
#include <iostream>
using namespace std;

Screen::Screen() // constarctor for the screen. points all the pointers of the matrix to NULL
{
	for (int i = 0; i < SCREEN_WIDTH; ++i) 
		for (int j = 0; j < SCREEN_HIGHT; ++j) 
			screen[i][j] = nullptr;
}

//this function will sets all the pointers in the matrix to null and free the moemory of all dynamic alolocated objects 
void Screen::CleanScreen() 
{
	int currLength;
	for (int i = X_OFFSET; i < SCREEN_WIDTH; ++i)// we only run on the dymeic parts of the screen
		for (int j = Y_OFFSET; j < SCREEN_HIGHT; ++j)// we only run on the dymeic parts of the screen
		{
			if (screen[i][j] != nullptr)
			{
				if (screen[i][j]->IsSolutionPossibility()) // if the current object is a solution Posability object we need to the memory
				{
					currLength = screen[i][j]->GetLength();
					delete screen[i][j]; // delete the current object
					for (int k = 0; k < currLength && k < SCREEN_HIGHT; ++k) // we want to set all the pointers to the object to null
					{
						screen[i + k][j] = nullptr;
					}
				}
				
			}
		}
}
// this function will draw the entire dynamic part of the screen
void Screen::DrawScrean()const
{
	for (int i = X_OFFSET; i < SCREEN_WIDTH; ++i) // we only run on the dymeic parts of the screen
		for (int j = Y_OFFSET; j < SCREEN_HIGHT; ++j) // we only run on the dymeic parts of the screen
		{
			if (screen[i][j] != nullptr)
			{
				if (screen[i][j]->GetPosition().GetX() == i && screen[i][j]->GetPosition().GetY() == j) // check the object to see if we are in the first position of the object so we will only draw it once
				{ 
					gotoxy(i, j);
					screen[i][j]->Draw(); // draw the object
				}
			}
		}
		
}

// this funciton will set a screenobject to his position in the screen
void Screen::SetPositionForScreenObject(ScreenObject *object)
{

	for (unsigned int i = 0; i < object->GetLength(); ++i) // if the object length is greater then 1 we want to set all the relevant pointers to the object
	{
		screen[object->GetPosition().GetX() + i][object->GetPosition().GetY()] = object;
	}
}

// this funciton will remove an object from the screen
void Screen::ClearScreenObject(ScreenObject *object)
{
	for (unsigned int i = 0; i < object->GetLength(); ++i) // if the object length is greater then 1 we want to remove all the relevant pointers to the object
	{
		screen[object->GetPosition().GetX() + i][object->GetPosition().GetY()] = nullptr;
	}
	object->Clear();
	if (object->IsSolutionPossibility()) // if the current object is a solution Posability object we need to free the memory
		delete object;
}

//this funciton will create a new solution object
void Screen::CreateNewSolutionPosability(const unsigned int & currentLevel)
{
	bool foundPosition = false;
	int x, y;
	unsigned int data = rand() % (currentLevel + 10) + 1; //generate the number for the solution posability
	int length = NumDigits(data);

	for (int i = 0; i < 10 && !foundPosition; ++i) // try 10 times to find a position for the number
	{
		bool xPositionOk, yPositionOk;
		xPositionOk = yPositionOk = true; // we assume that we will find a good position and change it to false if dont

		x = rand() % (81 - length);
		y = rand() % (21) +3;

		for (int j = -1; j < length + 1 && xPositionOk && yPositionOk; ++j) // check all the x positions from -1 of the current position to +1 of the current position
		{
			if (screen[x + j][y] != nullptr) // if the position is taken then set xPositionOk to false
				xPositionOk = false;
			
			if (j > -1 && j < length) // check the y axis without the corrners of the squrae radius we are checking
			{
				if (screen[x + j][y + 1] != nullptr || screen[x + j][y - 1] != nullptr) // if the position is taken then set yPositionOk to false
					yPositionOk = false;
			}
		}

		if (xPositionOk && yPositionOk) // if x and y positions are ok set found position to ture
			foundPosition = true;
	}

	if (foundPosition)
	{
		latestSolutionPosabilityPosition = Point(x, y);
		SolutionPosabilty * newPosability = new SolutionPosabilty(latestSolutionPosabilityPosition, data); // if we have a valid position we will create a new pbject
		newPosability->Draw(); // we wont forget to draw the new solution posability
		
		for (int i = 0; i < length; ++i) // set the screen to point to the new object in all relvaln positions
		{
			screen[x+i][y] = newPosability; // set the screen

		}
	}
}

Point Screen::findClosestSolutionPossibility(const Point currentPosition) const
{
	Point res;
	int x = currentPosition.GetX(), y = currentPosition.GetY();
	bool found = false;

	while (!found)
	{
	

	}

	return res;
}

Point Screen::findClosestTarget(const Point& currentPosition, const Point& currentTargetPosition) const
{
	Point res;
		
	if (currentPosition == currentTargetPosition || currentTargetDied(currentTargetPosition))
		res = findClosestSolutionPossibility(currentPosition);
	else 
		res = currentPosition.getCloserPoint(currentTargetPosition,latestSolutionPosabilityPosition);


	return res;
}