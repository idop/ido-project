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
using namespace std;

class Equation
{
	char sign;
	unsigned int  leftNumber;
	unsigned int  rightNumber;
	unsigned int  solution;
	// partTohide will sotr the part that the eqations will hide : 'l' - left , 'r' - right, 's' - solution
	char  partToHide;
	
	//this function will return a random sign for the equation
	char RandomSign();
	//this function will get the sign populated for the eqation and return the eqation part we will hide from the player
	char RandomPartToHide(const char & sign);

public:
	Equation(const unsigned int & gameLevel);
	
	 void Draw(); 
	 bool isSolution(const unsigned int & num) { return (num == solution) ? true : false; }

};

#endif