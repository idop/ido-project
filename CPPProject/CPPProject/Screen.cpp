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

bool Screen::currentTargetDied(const Point& currentTargetPosition) const
{
	ScreenObject * obj = screen[currentTargetPosition.GetX()][currentTargetPosition.GetY()];
	return (dynamic_cast<SolutionPosabilty*> (obj) == nullptr); // helper methood to find colsest solution posbility algorithem for numbereaters 
}

// // helper methood to find colsest solution posbility algorithem for numbereaters  this funciton will get an x value of the current rhombos scan and return a valid x point inside the screen
int Screen::getValidXValue(int x) const
{
	int res;
	
	if (x >= X_OFFSET && x < SCREEN_WIDTH)
		res = x;
	else if (x >= SCREEN_WIDTH)
		res = ((x - SCREEN_WIDTH + X_OFFSET) % SCREEN_WIDTH);
	else
		res = (SCREEN_WIDTH + (x % SCREEN_WIDTH)) % SCREEN_WIDTH;

	return res;
}

// // helper methood to find colsest solution posbility algorithem for numbereaters  this funciton will get an y value of the current rhombos scan and return a valid y point inside the screen
int Screen::getValidYValue(int y) const
{
	int res;

	if (y >= Y_OFFSET && y < SCREEN_HIGHT)
		res = y;
	else if (y >= SCREEN_HIGHT)
		res = ((y - SCREEN_HIGHT + Y_OFFSET) % SCREEN_HIGHT);
	else
		res = (SCREEN_HIGHT + (y % SCREEN_HIGHT)) % SCREEN_HIGHT;

	return res;
}

Screen::Screen() // constarctor for the screen. points all the pointers of the matrix to NULL
{
	numberOfSolutionPossibilities = 0;

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
		screen[object->GetPosition().GetX()+i][object->GetPosition().GetY()] = object;
}

// this funciton will remove an object from the screen
void Screen::ClearScreenObject(ScreenObject *object)
{
	for (unsigned int i = 0; i < object->GetLength(); ++i) // if the object length is greater then 1 we want to remove all the relevant pointers to the object
	{
		screen[object->GetPosition().GetX() + i][object->GetPosition().GetY()] = nullptr;
	}
	object->Clear();
	if (dynamic_cast<SolutionPosabilty*>(object) != nullptr){ // if the current object is a solution Posability object we need to free the memory
		delete object;
		--numberOfSolutionPossibilities;
	}
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
		++numberOfSolutionPossibilities;
		latestSolutionPosabilityPosition = Point(x, y);
		SolutionPosabilty * newPosability = new SolutionPosabilty(latestSolutionPosabilityPosition, data); // if we have a valid position we will create a new pbject
		newPosability->Draw(); // we wont forget to draw the new solution posability
		for (int i = 0; i < length; ++i) // set the screen to point to the new object in all relvaln positions
		{
			screen[x+i][y] = newPosability; // set the screen

		}
	}
}

Point Screen::findClosestSolutionPossibility(const Point currentPosition) const // we will scan Rhombus's to find the closest posability
{
	Point res;
	int x = currentPosition.GetX(), y = currentPosition.GetY();
	int xToCheck, yToCheck;
	bool found = false;
	ScreenObject * tmpObject;

	while (!found)
	{
		for (int i = 1; i < 50; ++i) // we need exaclty 50 diffrent Rhombus's (incresing in size by 1 every time) the scan the whole screen
		{				

			for (int t = 1; t > -2; t -= 2) // so we can scan both sides (x+t , x-t)
			{
				xToCheck = getValidXValue(x + t*i);
				yToCheck = getValidYValue(y);
				tmpObject = screen[xToCheck][yToCheck];
				if (tmpObject != nullptr)
				{
					if (dynamic_cast<SolutionPosabilty*>(tmpObject) != nullptr)
					{
						res = Point(xToCheck, yToCheck);
						found = true;
						break;
					}
				}
				for (int j = 1; j <= i; ++j)
				{
					xToCheck = getValidXValue(x + (t*(i - j)));
					yToCheck = getValidYValue(y + t*j);
					tmpObject = screen[xToCheck][yToCheck];
					if (tmpObject != nullptr && dynamic_cast<SolutionPosabilty*>(tmpObject) != nullptr)
					{
						res = Point(xToCheck, yToCheck);
						found = true;
						break;
					}
				}
			}
			}
	}
	return res;
}
// methood for the number eaters to find the closest solution posibility
Point Screen::findClosestTarget(const Point& currentPosition, const Point& currentTargetPosition) const
{
	Point res;
		
	if (numberOfSolutionPossibilities == 0) // if there are no solution posibility dont move
		res = currentPosition;
	else if (currentPosition == currentTargetPosition || currentTargetDied(currentTargetPosition))// if the current target is gone ( killed or eaten) 
		res = findClosestSolutionPossibility(currentPosition); // find the closest target
	else 
		res = currentPosition.getCloserPoint(currentTargetPosition,latestSolutionPosabilityPosition); // current target is in place so just check if the last alloceted number is closest


	return res;
}