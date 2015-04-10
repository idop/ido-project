//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Player.h
// -------------
// This class creates and handles the players of the game
// This class will  create the player , draw the player , move the player , etc..
//
// Author: Ido Perry
// First version: 2015-04-03
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Point.h"
#include "ScreenObject.h"
#include <string>
#include "Direction.h"
using namespace std;


const char  P1_DEFULT_CHAR='@';
const char  P2_DEFULT_CHAR='#';
const string  P1_KEYBOARD_KEYS = "awdx";
const string  P2_KEYBOARD_KEYS = "jilm";
const Point P1_DEFULT_POSITION(10, 9);
const Point P2_DEFULT_POSITION(70, 9);
const Direction::value P1_DEFULT_DIRECTION = Direction::RIGHT;
const Direction::value P2_DEFULT_DIRECTION = Direction::LEFT;


class Player : public ScreenObject
{
	const char playerChar;
	const string keyboardKeys;
	int numberOfLives;
	int score;
	bool playerSolved;
	Point position;
	Direction::value direction;
public:
	Player(const char & ch, const string & str) :playerChar(ch), keyboardKeys(str),score(0),playerSolved(false) {}; // constract the play with the defult attributes (player char , keyboard commands and starting score
	void SetToStart(const Point & p, const Direction::value & d); // retrun the player to deuflt start level settings
	void SetDirection(const Direction::value & d){ direction = d; };
	void SetNumberOfLives(const int & num){ numberOfLives = num; };
	char getPlayerChar()const { return playerChar; }
	int getNumberOfLives()const { return numberOfLives; };
	int getScore()const { return score; }
	string GetKeyboardKeys()const{ return keyboardKeys; }
	void FoundTheSolution(){ playerSolved = true; ++score; }
	void WrongSolution(){ numberOfLives--; }
	bool IsSolutionFound()const{ return playerSolved; }
	Direction::value getdirection()const { return direction; };
	void Move(const Point & p){ position = p; }
	virtual char Type()const{ return 'p'; }
	virtual void Draw()const;
	virtual void Clear()const;
	virtual Point GetPosition()const{ return position; }
	virtual unsigned int GetData()const { return score; } //used to get the score . not really needed
	virtual unsigned int GetLength()const{ return 1; }
};


#endif