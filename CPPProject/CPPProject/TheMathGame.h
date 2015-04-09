#ifndef _THE_METH_GAME_H_
#define _THE_METH_GAME_H_

#include "ISpecificGame.h"
#include "Equation.h"
#include "Point.h"
#include "Direction.h"
#include "Player.h"
#include "color.h"
#include "Screen.h"

const unsigned int MAX_LEVEL = 20;

class TheMathGame : public ISpecificGame
{
	unsigned int currentLevel;
	unsigned int maxLevel;
	Equation equation1, equation2;
	Player player1, player2;
	Screen * currentScreen;

public:
	TheMathGame() : currentLevel(0), maxLevel(MAX_LEVEL), equation1(P1_EQUATION_POSITION), equation2(P2_EQUATION_POSITION),
		player1(P1_DEFULT_CHAR, P1_KEYBOARD_KEYS), player2(P2_DEFULT_CHAR, P2_KEYBOARD_KEYS){currentScreen=NULL;};
	virtual bool isLevelDone()const;
	virtual bool hasNextLevel()const{ return (currentLevel < maxLevel); };
	virtual void startLevel();
	virtual void doIteration(const list<char>& keyHits);
	virtual void doSubIteration();
};

#endif