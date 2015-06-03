//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// NumberEaters.ccp
// -------------
// 
// This Class reporesents the number eaters creatures, they are identified with the sign %
//
// Author: Ido Perry and Alex Odesser
// First version: 2015-05-29
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "NumberEaters.h"

//set the direction to the current target
void NumberEaters::setDirectionToTargetPosition()
{
	int xDiffrence = this->GetPosition().getXDiffrence(targetPosition);
	int yDiffrence = this->GetPosition().getYDiffrence(targetPosition);

	if (xDiffrence != 0)
		if ((isPositive(xDiffrence) && needToCrossMoreThenHalfTheScreen(xDiffrence, SCREEN_WIDTH-X_OFFSET)) || 
		    (!isPositive(xDiffrence) && !needToCrossMoreThenHalfTheScreen(xDiffrence,SCREEN_WIDTH-X_OFFSET)))
			this->SetDirection(Direction::value::RIGHT);  // change direction to right
		else
			this->SetDirection(Direction::value::LEFT); // change direction to left
	else //  only  ydiffrence is greater then 0
	{
		if ((isPositive(yDiffrence) && needToCrossMoreThenHalfTheScreen(yDiffrence, SCREEN_HIGHT-Y_OFFSET)) || 
			(!isPositive(yDiffrence) && !needToCrossMoreThenHalfTheScreen(yDiffrence, SCREEN_HIGHT-Y_OFFSET)))
			this->SetDirection(Direction::value::DOWN); 
		else
			this->SetDirection(Direction::value::UP); 
	}

}

//find the n ext point to move
Point NumberEaters::getPointToMove()
{
	targetPosition = CurrentScreen->findClosestTarget(this->GetPosition(), targetPosition); // get a aterget from the screen (current target or a new one)
	setDirectionToTargetPosition(); // set thje direction for that target
	return MovingScreenObject::getPointToMove(); // use the base class funciton to get the next point 
}