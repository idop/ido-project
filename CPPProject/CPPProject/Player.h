//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Player.h
// -------------
// This class creates and handles the players of the game
// This class will  create the player , draw the player , move the player , etc..
//
// Author: Ido Perry and Alex Odesser
// First version: 2015-04-03
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include "Direction.h"
#include "MovingScreenObject.h"
using namespace std;

const int				NUM_OF_LIVES = 3;
const int				NUM_OF_BULLETS = 5;
const char				P1_DEFULT_CHAR = '@';
const char				P2_DEFULT_CHAR = '#';
const string			P1_KEYBOARD_KEYS = "awdxz";
const string			P2_KEYBOARD_KEYS = "jilmn";
const Point				P1_DEFULT_POSITION ( 10 , 9 );
const Point				P2_DEFULT_POSITION ( 70 , 9 );
const Direction::value  P1_DEFULT_DIRECTION = Direction::RIGHT;
const Direction::value  P2_DEFULT_DIRECTION = Direction::LEFT;

class Player : public MovingScreenObject {
	const char	 playerChar;
	const string keyboardKeys;
	int			 numberOfLives;
	int			 score;
	bool		 playerSolved;
	int			 bullets;

public:
	Player ( const char & ch , const string & str , const Point & p , const Direction::value & d ) : MovingScreenObject ( p , d , playerChar), playerChar ( ch ), keyboardKeys ( str ), score ( 0 ), playerSolved ( false ), bullets ( NUM_OF_BULLETS ) {
	}; // constract the play with the defult attributes (player char , keyboard commands and starting score

	~Player () {
	};

	void SetNumberOfLives ( const int & num ) {
		numberOfLives = num;
	};// set the number of lives of the player
	char GetPlayerChar ()const {
		return playerChar;
	} // get the player symbol
	int GetNumberOfLives ()const {
		return numberOfLives;
	}; // get the number of lives
	int GetScore ()const {
		return score;
	} /// get the player current score
	string GetKeyboardKeys ()const {
		return keyboardKeys;
	} // returns the player valid keyboards keys
	void FoundTheSolution () {
		playerSolved = true;
		++score;
	} // set the player equation status to solved and add a point to the player
	void WrongSolution () {
		numberOfLives--;
	} // removes 1a live from the player 
	bool IsSolutionFound ()const {
		return playerSolved;
	} // checks if the player solved the his equation. used to end the level
	int GetNumberOfBullets ()const {
		return bullets;
	}

	void RemoveBullet () {
		--bullets;
	}

	void AddBullet () {
		++bullets;
	}

	void ResetNumberOfBullets () {
		bullets = NUM_OF_BULLETS;
	}

	virtual void Move(const Point & p) override;

	//CPP:
	virtual void Draw ()const override; //inherited  from the Screenobject class draws the player
	void SetToStart ( const Point & p , const Direction::value & d ); // retrun the player to deuflt start level settings
	virtual void Collesion () override;

};


#endif