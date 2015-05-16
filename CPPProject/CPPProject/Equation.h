//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Equation.h
// -------------
// This class creates the equtions the players will have to solve.
// This class will form the quation  , draw it to the screen , validate the validety of the player solution ettempts, etc.
//
// Author: Ido Perry and Alex Odesser
// First version: 2015-03-29
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef __EQUATION_H
#define __EQUATION_H

#include <iostream>
#include "Point.h"
#include "SolutionType.h"
using namespace std;


//const values decleration

const Point P1_EQUATION_POSITION(0, 1);
const Point P2_EQUATION_POSITION(55, 1);
const unsigned int MAX_RANDOM_NUMER_AFTER_LEVEL_20 = 21;
const unsigned int MAX_NUMBER_OF_OPERATORS = 2;
const unsigned int MAX_NUMBER_OF_OPERANDS = 4;


class Equation
{
	unsigned int currentLevel;
	unsigned int  num1, num2, num3, solution;
	unsigned int operandsArray[MAX_NUMBER_OF_OPERANDS]; // for display only
	Point position;
	char operator1;
	char  partToHide; // partTohide will store the part that the eqations will hide : 'l' - left , 'r' - right, 's' - solution
	char operatorsArray[MAX_NUMBER_OF_OPERATORS + 1]; // '=' is always the last operands and for display only

	//this function will return a random sign for the equation
	char RandomOperator();
	//this function will get the sign populated for the eqation and return the eqation part we will hide from the player
	char RandomPartToHide(const char & op);
	bool IsInteger(const int & dividend, const int & divisor)const{ return (dividend % divisor == 0); } // this function checks if a caluclated solution posability is an integer
	bool IsSolutionInRange(const int & num)const{ return (num > 0 && num <= (currentLevel + 10)); };
	void DrawUntilLevel20()const; // helper methood to draw. Draws the equation for levels 1-20
	void DrawAfterLevel20()const; // helper methood to draw. Draws the equation for levels  21+
	void CreateEquationUntilLevel20();  //helper methood to init, creates an equation for levels 1-20
	void CreateEquationAfterLevel20(); //helper methood to init, creates an equation for levels 21+
	void operandsArrayHideMinium(); // hides the 2 minimum numbers in the array
	void GenerteEquationNumbersFirstOperatorPlus(); //helper methood for the case when first operator is '+'
	void GenerteEquationNumbersFirstOperatorSubtruct();	//helper methood for the case when first operator is '-'
	void GenerteEquationNumbersFirstOperatorMultiply(); //helper methood for the case when first operator is '*'
	void GenerteEquationNumbersFirstOperatorDevide(); //helper methood for the case when first operator is '/'
	void GenerteRandomNumsOpPM(); //helper mehtood to genrate the equation after level 20 for the case when the first operator is + or * generates random numbers for 1 2 and 3
	void GenerteRandomNumsOpS(); //helper mehtood to genrate the equation after level 20 for the case when the first operator is - or /  generates random numbers 2, 3 and solution
	void GenerteRandomNumsOpD(); //helper mehtood to genrate the equation after level 20 for the case when the first operator is - or /  generates random numbers 2, 3 and solution
	SolutionType IsSolutionUntilLevel20(const unsigned int & num);
	SolutionType IsSolutionAfterLevel20(const unsigned int & num);
	SolutionType SolvePartialEquation(const int & secondHiddenNumber); // helper methood will solve a a simple 2 numbers and operator equation (num1 Op num2)
	SolutionType ExtractNum2PartialSolutionState();// helper methood to extract the partial state of the solution when num 2 is still hidden
	SolutionType ExtractNum3PartialSolutionState();// helper methood to extract the partial state of the solution when num 3 is still hidden
	SolutionType ExtractSolutionPartialSolutionState();// helper methood to extract the partial state of the solution when the solution is still hidden
public:
	Equation(const Point & p) :position(p){ operatorsArray[MAX_NUMBER_OF_OPERATORS] = '='; }; // constrator for equation with the defult position and  '=' is set to the last operandsArray position
	void Init(const unsigned int & gameLevel); // genrates a random equation for the game
	void Draw()const;  // draws the equation to the screen
	SolutionType IsSolution(const unsigned int & num); // checks the a number to see if it solves the equations

};

#endif