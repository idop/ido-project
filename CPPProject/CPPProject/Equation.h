//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Equation.h
// -------------
// This class creates the equtions the players will have to solve.
// This class will form the quation  , draw it to the screen , validate the validety of the player solution ettempts, etc.
//
// Author: Ido Perry
// First version: 2015-03-29
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef __EQUATION_H
#define __EQUATION_H

#include <iostream>
#include "Point.h"
using namespace std;


//const points for the equations

const Point P1_EQUATION_POSITION(0, 1);
const Point P2_EQUATION_POSITION(70, 1);

class Equation
{
	char sign;
	char  partToHide; // partTohide will sotr the part that the eqations will hide : 'l' - left , 'r' - right, 's' - solution
	unsigned int  leftNumber;
	unsigned int  rightNumber;
	unsigned int  solution;
	Point position;
	
	//this function will return a random sign for the equation
	char RandomSign();
	//this function will get the sign populated for the eqation and return the eqation part we will hide from the player
	char RandomPartToHide(const char & sign);

public:
	Equation(const Point & p) :position(p){}; // constrator for equation with the defult position
	void Init(const unsigned int & gameLevel); // genrates a random equation for the game
	 void Draw()const; 
	 bool IsSolution(const unsigned int & num) { return (num == solution); }
};

#endif