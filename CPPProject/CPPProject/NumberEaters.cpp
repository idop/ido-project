#include "NumberEaters.h"
#include <math.h>
NumberEaters::~NumberEaters()
{
}



void NumberEaters::setDirectionToTargetPosition()
{
	int xDiffrence = this->GetPosition().getXDiffrence(targetPosition);
	int yDiffrence = this->GetPosition().getYDiffrence(targetPosition);

	if (xDiffrence != 0)
		if ((isPositive(xDiffrence) && needToCrossMoreThenHalfTheScreen(xDiffrence)) || (!isPositive(xDiffrence) && !needToCrossMoreThenHalfTheScreen(xDiffrence))) 
			this->SetDirection(Direction::value::RIGHT);  // change direction to right
		else
			this->SetDirection(Direction::value::LEFT); // change direction to left
	else //  only  ydiffrence is greater then 0
	{
		if ((isPositive(yDiffrence) && needToCrossMoreThenHalfTheScreen(yDiffrence)) || (!isPositive(yDiffrence) && !needToCrossMoreThenHalfTheScreen(yDiffrence)))
			this->SetDirection(Direction::value::DOWN); 

			this->SetDirection(Direction::value::UP); 
	}

}

Point NumberEaters::getPointToMove()
{
	targetPosition = CurrentScreen->findClosesetTarget(this->GetPosition(),targetPosition);
	setDirectionToTargetPosition();
	return MovingScreenObject::getPointToMove();
}