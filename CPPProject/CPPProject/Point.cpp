#include "Point.h"


int Point::numberOfXStpes(const Point & p) const
{
	int res;
	int diff =abs(this->getXDiffrence(p));
	
	if (needToCrossMoreThenHalfTheScreen(diff, RIGHT_LIMIT + 1))
		res = diff;
	else
		res = RIGHT_LIMIT + 1 - diff;

	return res;
}

int Point::numberOfYSteps(const Point & p) const
{
	int res;
	int diff = abs(this->getYDiffrence(p));

	if (needToCrossMoreThenHalfTheScreen(diff, LOWER_LIMIT + 1))
		res = diff;
	else
		res = LOWER_LIMIT + 1 - diff;

	return res;
}

Point Point::GetPointToMoveFromDirection(const Direction::value& direction)
{
	Point res;
	switch (direction)
	{
	case Direction::LEFT:
		if (this->GetX() == LEFT_LIMIT) // check if the player is going to move outside of the screen limit
			res = Point(RIGHT_LIMIT, this->GetY());// direction is left so go to the right limit of the screen
		else
			res = Point(this->GetX() - 1, this->GetY()); // direction is left to reduce 1 from x
		break;
	case Direction::RIGHT:
		if (this->GetX() == RIGHT_LIMIT) // check if the player is going to move outside of the screen limit
			res = Point(LEFT_LIMIT, this->GetY());// direction is  right so go to the left limit of the screen
		else
			res = Point(this->GetX() + 1, this->GetY());// direction is right so add 1 to x
		break;
	case Direction::UP:
		if (this->GetY() == UPPER_LIMIT) // check if the player is going to move outside of the screen limit
			res = Point(this->GetX(), LOWER_LIMIT);// direction is up to go to the bottom of the screen
		else
			res = Point(this->GetX(), this->GetY() - 1); // direction is up so subtruct 1 from y
		break;
	case Direction::DOWN:
		if (this->GetY() == LOWER_LIMIT) // check if the player is going to move outside of the screen limit
			res = Point(this->GetX(), UPPER_LIMIT);// direction is down so go to the upper limit of the game screen
		else
			res = Point(this->GetX(), this->GetY() + 1); // direction is down so add 1 to y
		break;
	default:// we should not get here
		break;
	}

	return res;
}


