#include "Equation.h"
#include <stdlib.h>

// this function will return a random sign for the equation
char Equation::RandomSign()
{

	char res;
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
char Equation::PartToHide(char sign)
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

//C'tor we will use for the eqation. this C'tor gets the current level and creates a random equation for the game
Equation::Equation(unsigned int  gameLevel) :sign(RandomSign())
{
	switch (sign)
	{
	case '+':
		leftNumber = rand() % (gameLevel + 10) + 1;
		rightNumber = rand() % (gameLevel + 10) + 1;
		solution = leftNumber + rightNumber;
		partToHide = PartToHide('+');
		break;
	case '-':
		rightNumber = rand() % (gameLevel + 10) + 1;
		solution = rand() % (gameLevel + 10) + 1;
		leftNumber = solution + rightNumber;
		partToHide = PartToHide('-');
		break;
	case '*':
		leftNumber = rand() % (gameLevel + 10) + 1;
		rightNumber = rand() % (gameLevel + 10) + 1;
		solution = leftNumber * rightNumber;
		partToHide = PartToHide('*');
		break;
	case '/':
		rightNumber = rand() % (gameLevel + 10) + 1;
		solution = rand() % (gameLevel + 10) + 1;
		leftNumber = solution * rightNumber;
		partToHide = PartToHide('/');
		break;
	default:  // we should nbot get here
		break;
	}
}