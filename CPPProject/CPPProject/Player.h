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

//const variables declration to store the players chars , players playing keys and dufult settings
const char  P1_DEFULT_CHAR='@';
const char  P2_DEFULT_CHAR='#';
const string  P1_KEYBOARD_KEYS = "awdxz";
const string  P2_KEYBOARD_KEYS = "jilmn";
const Point P1_DEFULT_POSITION(10, 9);
const Point P2_DEFULT_POSITION(70, 9);
const Direction::value P1_DEFULT_DIRECTION = Direction::RIGHT;
const Direction::value P2_DEFULT_DIRECTION = Direction::LEFT;
const int NUM_OF_LIVES = 3;
const int NUM_OF_BULLETS = 5;


class Player :  public MovingScreenObject
{
	const char playerChar;
	const string keyboardKeys;
	int numberOfLives;
	int score;
	bool playerSolved;
	Point position;
	Direction::value direction;
	int bullets;

public:
	Player(const char & ch, const string & str) :playerChar(ch), keyboardKeys(str), score(0), playerSolved(false), bullets(NUM_OF_BULLETS) {}; // constract the play with the defult attributes (player char , keyboard commands and starting score
	void SetToStart(const Point & p, const Direction::value & d); // retrun the player to deuflt start level settings
	void SetDirection(const Direction::value & d){ direction = d; }; // set the direction of the player
	void SetNumberOfLives(const int & num){ numberOfLives = num; };// set the number of lives of the player
	char getPlayerChar()const { return playerChar; } // get the player symbol
	int getNumberOfLives()const { return numberOfLives; }; // get the number of lives
	int getScore()const { return score; } /// get the player current score
	string GetKeyboardKeys()const{ return keyboardKeys; } // returns the player valid keyboards keys
	void FoundTheSolution(){ playerSolved = true; ++score; } // set the player equation status to solved and add a point to the player
	void WrongSolution(){ numberOfLives--; } // removes 1a live from the player 
	bool IsSolutionFound()const{ return playerSolved; }  // checks if the player solved the his equation. used to end the level
	int getNumberOfBullets()const{ return bullets; }
	void removeBullet(){ bullets--; }
	void resetNumberOfBullets(){ bullets = NUM_OF_BULLETS; }


	virtual Direction::value getDirection()const { return direction; }; // gets the player current directions
	virtual void Move(const Point & p){ position = p; } // moves the player to a new position p according to this direction
	virtual char Type()const{ return 'p'; } // inherited  from the Screenobject class , returns the type of the screen object in this case p for player
	virtual void Draw()const; //inherited  from the Screenobject class draws the player
	virtual void Clear()const;//inherited  from the Screenobject class, removes the player char form the screen
	virtual Point GetPosition()const{ return position; }//inherited  from the Screenobject class, returns the current position of the player
	virtual unsigned int GetData()const { return score; } //inherited  from the Screenobject class but not really needed in this class
	virtual unsigned int GetLength()const{ return 1; } // inherited  from the Screenobject class, returns the length of the player symobl
	virtual void GotHit();
};


#endif