#include "SolutionPosabilty.h"
#include "io_utils.h"
#include <iostream>
using namespace std;

//global function to get the number of digits of a number
unsigned int NumDigits(unsigned int num)
{
	if (num < 10)
		return 1;
	else
		return 2;
}


void SolutionPosabilty::Draw()const
{
	gotoxy(GetPosition().getX(), GetPosition().getY());
	cout << data;
}

void SolutionPosabilty::Clear()const
{
	unsigned int length = GetLength();
	gotoxy(GetPosition().getX(), GetPosition().getY());
	for (unsigned int i = 0; i < length; ++i)
		cout << ' ';
}
