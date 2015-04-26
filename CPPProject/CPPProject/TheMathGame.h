//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// TheMathGame.h
// -------------
// This class  will store all the objects related to the game
// will manage the movment and displaying of objects on screen
// manages the keystroke and the follow of game play
//
// Author: Ido Perry and Alex Odesser
// First version: 2015-04-04
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef _THE_METH_GAME_H_
#define _THE_METH_GAME_H_

#include "ISpecificGame.h"
#include "Equation.h"
#include "Point.h"
#include "Direction.h"
#include "Player.h"
#include "color.h"
#include "Screen.h"

const unsigned int MAX_TURNS_PER_LEVEL = 1500;


class TheMathGame : public ISpecificGame
{
	unsigned int currentLevel;
	unsigned int maxLevel;
	unsigned int currentTurn;
	bool levelDone;
	void PrintScores();
	void EndTurn(); 
	void keyStrokeManager(const list<char>& keyHits);
	void PlayerMovment(const Point & toMove, Player & p, Equation & eq);
	void clearAndMove(Player & p, const Point & toMove, ScreenObject * obj);
	void CheckSolution(Equation eq, const ScreenObject * obj, Player & p);
	void DrawEquations()const;
	Point GetPointToMove(const Player & p);
	Equation equation1, equation2;
	Player player1, player2;
	Screen * currentScreen;
	Direction::value MapKeyToDirection(const char & keyHit, const Player & p);
	Color GetColorForText()const;

public:

	TheMathGame() : currentLevel(0), maxLevel(MAX_LEVEL), currentTurn(0), levelDone(false), equation1(P1_EQUATION_POSITION), equation2(P2_EQUATION_POSITION),
		player1(P1_DEFULT_CHAR, P1_KEYBOARD_KEYS), player2(P2_DEFULT_CHAR, P2_KEYBOARD_KEYS){currentScreen=NULL;};
	virtual bool isLevelDone()const{ return levelDone; } 
	virtual bool hasNextLevel()const{ return (currentLevel < maxLevel); };
	virtual void startLevel(unsigned int level);
	virtual void doIteration(const list<char>& keyHits);
	virtual void doSubIteration();
	unsigned int GetCurrentTurn()const{ return currentTurn; }
	virtual void ResumeLevel() ;

};

#endif