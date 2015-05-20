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
void Player::SetToStart ( const Point & p , const Direction::value & d ) {
	numberOfLives = NUM_OF_LIVES;
	SetPosition ( p );
	SetDirection ( d );
	playerSolved = false;
}

void Player::Move(const Point & p){
	Clear();
	SetPosition(p);
	Draw();
} // moves the player to a new position p according to this direction

//this functions draws the player
void Player::Draw ()const {
	gotoxy ( GetPosition().getX() , GetPosition().getY() );
	cout << playerChar;
}


void Player::Collesion () {

	WrongSolution();

	switch (GetPlayerChar())
	{
	case P1_DEFULT_CHAR:
		SetDirection ( P1_DEFULT_DIRECTION );
		Move ( P1_DEFULT_POSITION );
		break;
	case P2_DEFULT_CHAR:
		SetDirection ( P2_DEFULT_DIRECTION );
		Move ( P2_DEFULT_POSITION );
		break;
	default: // we should not get here
		break;
	}
}