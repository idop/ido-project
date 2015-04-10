//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Equation.cpp
// -------------
// This class  will manage equation generator
// randomize the sign and numbers, and decides on the missing number
//
// Author: Ido Perry and Alex Odesser
// First version: 2015-04-04
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#include "Equation.h"
#include <stdlib.h>
#include "io_utils.h"
// this function will return a random sign for the equation
char Equation::RandomSign()
{

	char res = NULL;
	int randomValue = rand() % 4;

	switch (randomValue)
	{
	case 0:
		res = '+';
		break;
	case 1:
		res = '-';
		break;
	case 2:
		res = '*';
		break;
	case 3:
		res = '/';
		break;
	default:
		break;
	}
	return res;
}

//this function will get the sign populated for the eqation and return the eqation part we will hide from the player
char Equation::RandomPartToHide(const char & sign)
{
	if (sign == '+' || sign == '*')
	{
		if (rand() % 2 == 0)
			return 'l';
		else
			return 'r';
	}
	else
	{
		if (rand() % 2 == 0)
			return 's';
		else
			return 'r';
	}
}

//this function will generte a new random equation according to the game definitions
void Equation::Init(const unsigned int & gameLevel) 
{
	sign = RandomSign();

	switch (sign)
	{
	case '+':
		leftNumber = rand() % (gameLevel + 10) + 1;
		rightNumber = rand() % (gameLevel + 10) + 1;
		solution = leftNumber + rightNumber;
		partToHide = RandomPartToHide('+');
		break;
	case '-':
		rightNumber = rand() % (gameLevel + 10) + 1;
		solution = rand() % (gameLevel + 10) + 1;
		leftNumber = solution + rightNumber;
		partToHide = RandomPartToHide('-');
		break;
	case '*':
		leftNumber = rand() % (gameLevel + 10) + 1;
		rightNumber = rand() % (gameLevel + 10) + 1;
		solution = leftNumber * rightNumber;
		partToHide = RandomPartToHide('*');
		break;
	case '/':
		rightNumber = rand() % (gameLevel + 10) + 1;
		solution = rand() % (gameLevel + 10) + 1;
		leftNumber = solution * rightNumber;
		partToHide = RandomPartToHide('/');
		break;
	default:  // we should not get here
		break;
	}
}


// this funciton will draw the equation in the relevant position and with the relvant hidden part
void Equation::Draw()const
{
	gotoxy(position.getX(), position.getY());
	switch (partToHide)
	{
	case 'l':
		cout << "??"<< sign << rightNumber << '=' << solution;
		break;
	case 'r':
		cout << leftNumber << sign << "??" << '=' << solution;
		break;
	case 's':
		cout << leftNumber << sign << rightNumber << '=' << "??";
		break;
	default:  // we should not get here
		break;
	}
}
	
bool Equation::IsSolution(const unsigned int & num)
{
	switch (partToHide)
	{
	case 'l':
		return (num == leftNumber);
		break;
	case 'r':
		return (num == rightNumber);
		break;
	case 's':
		return (num == solution);
		break;
	default:  // we should not get here
		break;

	}
}