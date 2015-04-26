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
	if (sign == '+' || sign == '*') // sign is +  or * so we want to hide  the left or the right number
	{
		if (rand() % 2 == 0)
			return 'l';
		else
			return 'r';
	}
	else
	{
		if (rand() % 2 == 0) // sign is -  or / so we want to hide  the solution or the right number
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
	case '+': // sign is + therfore we will generate 2 radnnom numbers  for the left and right numbers and calculate the solution
		leftNumber = rand() % (gameLevel + 10) + 1;
		rightNumber = rand() % (gameLevel + 10) + 1;
		solution = leftNumber + rightNumber;
		partToHide = RandomPartToHide('+'); // sign is + so we want to hide  the left or the right number
		break;
	case '-':// sign is - therfore we will generate 2 radnnom numbers  for the right and and solution numbers and calculate the left number
		rightNumber = rand() % (gameLevel + 10) + 1;
		solution = rand() % (gameLevel + 10) + 1;
		leftNumber = solution + rightNumber;
		partToHide = RandomPartToHide('-'); // sign is - so we want to hide  the solution or the right number
		break;
	case '*': // sign is * therfore we will generate 2 randnom numbers  for the left and right numbers and calculate the solution
		leftNumber = rand() % (gameLevel + 10) + 1;
		rightNumber = rand() % (gameLevel + 10) + 1;
		solution = leftNumber * rightNumber;
		partToHide = RandomPartToHide('*');// sign is * so we want to hide  the left or the right number
		break;
	case '/':// sign is / therfore we will generate 2 radnnom numbers  for the right and and solution numbers and calculate the left number
		rightNumber = rand() % (gameLevel + 10) + 1;
		solution = rand() % (gameLevel + 10) + 1;
		leftNumber = solution * rightNumber;
		partToHide = RandomPartToHide('/');// sign is - so we want to hide  the solution or the right number
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

//this fucntion get a number and check if it solves the equations
bool Equation::IsSolution(const unsigned int & num)
{
	switch (partToHide)
	{
	case 'l': // left part is hidden so check the left number
		return (num == leftNumber);
		break;
	case 'r':// right part is hidden so check the right number
		return (num == rightNumber);
		break;
	case 's':// solution part is hidden so check the solution number
		return (num == solution);
		break;
	default:  // we should not get here
		break;

	}
}