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
#include "Bullet.h"
#include "Creature.h"

const unsigned int MAX_TURNS_PER_LEVEL = 1500;

const unsigned int LEFT = 0;
const unsigned int UP = 1;
const unsigned int RIGHT = 2;
const unsigned int DOWN = 3;
const unsigned int SHOOT = 4;


class TheMathGame : public ISpecificGame
{
protected:
	~TheMathGame()
	{
	}

private:
	unsigned int currentLevel;
	unsigned int maxLevel;
	unsigned int currentTurn;
	bool levelDone;
	Equation equation1, equation2;
	Player player1, player2;
	Screen* currentScreen;
	list<Bullet*> bulletList;
	Creature creatureList[6];

	void PrintScores ()const;// this function prints the game/level stats (scores, lives,current level and current turn), refreshes each time there is a change
	void EndTurn (); //this function handles all end of turn events.
	void keyStrokeManager ( const list<char> & keyHits ); //this function will handle the players keystorkes and change theier direction accordingly
	void PlayerMovment (Player & p, Equation & eq);// this function manages the player movment
	void clearAndMove ( MovingScreenObject & p , const Point & toMove , ScreenObject * obj );//halper function to Player movment
	void CheckSolution ( Equation & eq , const ScreenObject * obj , Player & p );//checks if the player found a valid solution or not and acts accordingly
	void DrawEquations ()const;//draws the 2 equations to the screen
	Direction::value MapKeyToDirection ( const char & keyHit , Player & p );//helper function to keyStrokeManager
	Color GetColorForText ()const; //this function will retrun a color for the screen text based on the current level. each level we will replace the screen color
	void runCreatuerList(unsigned int len);
	//void RemoveBullet(Bullet * b){ delete b; }
	void AddNewBullet(Bullet b);
	void runBulletList();
	void AddBulletToPlayers();
	void initCreatureList();

public:
	TheMathGame() : currentLevel(0), maxLevel(MAX_LEVEL), currentTurn(0), levelDone(false), equation1(P1_EQUATION_POSITION), equation2(P2_EQUATION_POSITION),
	                player1(P1_DEFULT_CHAR, P1_KEYBOARD_KEYS, P1_DEFULT_POSITION, P1_DEFULT_DIRECTION), player2(P2_DEFULT_CHAR, P2_KEYBOARD_KEYS, P2_DEFULT_POSITION, P2_DEFULT_DIRECTION)
	{
		currentScreen = nullptr;
	}

	virtual bool isLevelDone()const override
	{
		return levelDone;
	}

	virtual bool hasNextLevel()const override;

	virtual void startLevel(unsigned int level) override;
	virtual void doIteration(const list<char>& keyHits) override;
	virtual void doSubIteration() override;

	unsigned int GetCurrentTurn()const
	{
		return currentTurn;
	}

	virtual void ResumeLevel() override;
};

#endif