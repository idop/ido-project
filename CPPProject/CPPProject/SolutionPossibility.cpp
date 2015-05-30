//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SolutionPossibility.cpp
// -------------
// This class  will manage the game, all iterations and start / end / restart of levels
// it will also manage the movment of the players around the screen
//
// Author: Ido Perry and Alex Odesser
// First version: 2015-04-04
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "SolutionPossibility.h"
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

unsigned SolutionPosabilty::GetData() const
{
	return data;
}

void SolutionPosabilty::Draw()const
{
	gotoxy(GetPosition().GetX(), GetPosition().GetY());
	cout << data;
}

void SolutionPosabilty::Clear()const
{
	unsigned int length = GetLength();
	gotoxy(GetPosition().GetX(), GetPosition().GetY());
	for (unsigned int i = 0; i < length; ++i)
		cout << ' ';
}
