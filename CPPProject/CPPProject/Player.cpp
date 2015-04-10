//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Player.cpp
// -------------
// This class  will manage the player, as a screen object, initializing default parameters   
// delete and draw on screen.
//
// Author: Ido Perry and Alex Odesser
// First version: 2015-04-04
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

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
	numberOfLives = NUM_OF_LIVES;
	position = p;
	direction = d;
	playerSolved = false;
}

//this functions draws the player
void Player::Draw()const
{
	gotoxy(position.getX(), position.getY());
	cout << playerChar;
}

//this function removes to  player from the screen
void Player::Clear()const
{
	gotoxy(position.getX(), position.getY());
	cout << ' ';
}

