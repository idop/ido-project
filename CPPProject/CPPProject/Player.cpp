#include "Player.h"
#include "io_utils.h"
#include <string>
#include "Direction.h"
#include "Point.h"
using namespace std;

//this functino will return the player to his defult settings ( number of live, position , direction)
//when starting a new level or restarting the current level
void Player::SetToStart(const Point & p, const Direction::value & d)
{
	numberOfLives = 3;
	playerPosition = p;
	direction = d;
}

//this functions draws the player
void Player::Draw()const
{
	gotoxy(playerPosition.getX(), playerPosition.getY());
	cout << playerChar;
}

//this functions moves to player to the new position according to his direction
void Player::Move()
{

	switch (direction)
	{
	case Direction::LEFT:
		if (playerPosition.getX() == 0) // check if the player is going to move outside of the screen limit
			playerPosition.setX(79);
		else
			playerPosition.setX(playerPosition.getX() - 1);
		break;
	case Direction::RIGHT:
		if (playerPosition.getX() == 79) // check if the player is going to move outside of the screen limit
			playerPosition.setX(0);
		else
			playerPosition.setX(playerPosition.getX() + 1);
		break;
	case Direction::UP:
		if (playerPosition.getY() == 3) // check if the player is going to move outside of the screen limit
			playerPosition.setY(23);
		else
			playerPosition.setY(playerPosition.getY() - 1);
		break;
	case Direction::DOWN:
		if (playerPosition.getY() == 23) // check if the player is going to move outside of the screen limit
			playerPosition.setY(3);
		else
			playerPosition.setY(playerPosition.getY() + 1);
		break;
	default:// we should not get here
		break;
	}

}

//this function removes to  player from the screen
void Player::Clear()const
{
	gotoxy(playerPosition.getX(), playerPosition.getY());
	cout << ' ';
}