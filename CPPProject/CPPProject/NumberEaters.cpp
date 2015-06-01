#include "NumberEaters.h"

void NumberEaters::setDirectionToTargetPosition()
{
	int xDiffrence = this->GetPosition().getXDiffrence(targetPosition);
	int yDiffrence = this->GetPosition().getYDiffrence(targetPosition);

	if (xDiffrence != 0)
		if ((isPositive(xDiffrence) && needToCrossMoreThenHalfTheScreen(xDiffrence, SCREEN_WIDTH)) || (!isPositive(xDiffrence) && !needToCrossMoreThenHalfTheScreen(xDiffrence,SCREEN_WIDTH)))
			this->SetDirection(Direction::value::RIGHT);  // change direction to right
		else
			this->SetDirection(Direction::value::LEFT); // change direction to left
	else //  only  ydiffrence is greater then 0
	{
		if ((isPositive(yDiffrence) && needToCrossMoreThenHalfTheScreen(yDiffrence, SCREEN_HIGHT)) || (!isPositive(yDiffrence) && !needToCrossMoreThenHalfTheScreen(yDiffrence, SCREEN_HIGHT)))
			this->SetDirection(Direction::value::DOWN); 

			this->SetDirection(Direction::value::UP); 
	}

}

Point NumberEaters::getPointToMove()
{
	targetPosition = CurrentScreen->findClosestTarget(this->GetPosition(),targetPosition);
	setDirectionToTargetPosition();
	return MovingScreenObject::getPointToMove();
}