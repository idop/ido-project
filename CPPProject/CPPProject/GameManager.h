
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// GameManager.h
// -------------
// GameManager is the top level manager, the game starts from here.
// This class manages the game iterations, menus etc., but WITHOUT knowing anything about the actual game itself.
//
// Author: Amir Kirsh
// First version: 2014-12-09
// 
// This code is part of "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
//2015-04-03      Ido Perry and Alex Odesser        fixed bug in sub manu string validOptions
//2015-04-10      Ido Perry and Alex Odesser        added another init function to start a game from a spesific level
//2015-04-10      Ido Perry and Alex Odesser        added function to show make a sub menu
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "ISpecificGame.h"
#include <string>
#include <list>
using namespace std;

class GameManager
{
	ISpecificGame& actualGame;
	unsigned int currentLevel;
	unsigned int clockCycleInMillisec;
	unsigned int iterationsPerClockCycle;
	const static unsigned int KEYBOARD_HIT_LOOP = 10;  // const static can be initialized like this! :-)
	const static char ESC = 27; // the ESC key
	
	//NEW CODE EX1 Ido Perry and Alex Odesser 2015-04-10  added function to print the insturctions page
	void PrintInsturctions(); 
	//ENd OF NEW CODE
public:
	GameManager(ISpecificGame& theSpecificGame, unsigned int clockCycleLengthInMillisec, unsigned int numIterationsPerClockCycle)
		:actualGame(theSpecificGame), currentLevel(0), clockCycleInMillisec(clockCycleLengthInMillisec), iterationsPerClockCycle(numIterationsPerClockCycle) {}
	void run();
private:
	// helper methods
	void init()
	{
		currentLevel = 0;
	}
	//NEW CODE EX1 Ido Perry and Alex Odesser 2015-04-10  added another init function to start a game from a spesific level
	void init(unsigned int level) 
	{
		currentLevel = level - 1;
	}
	//ENd OF NEW CODE
	char mainMenu()const;
	//NEW CODE EX1 Ido Perry and Alex Odesser 2015-04-10  added function to make a sub menu
	void subMenu()const;
	//END OF NEW CODE
	bool playGame();
	char playNextLevel();
	char doLevelIterations();
	bool doIteration();
	bool doInputIteration();
public:
	class MainMenuOptions
	{
	public:
		static bool isValidOption(char option) {
			string validOptions = "1239";
			return (validOptions.find(option) != string::npos);
		}
		enum
		{
			PRESENT_INSTRUCTIONS		=	'1',
			PLAY_GAME					=	'2',
			PLAY_FROM_SELECTED_SCREEN	=	'3',
			EXIT_APPLICATION			=	'9'
		};
	};
	class LevelOptions
	{
	public:
		static bool isValidOption(char option) {
			// NEW CODE EX1,  2015-04-03, Ido Perry and Alex Odesser    fixed bug in sub manu string validOptions
			string validOptions = "12345"; 
			//END OF NEW CODE
			return (validOptions.find(option) != string::npos);
		}
		enum
		{
			EXIT_APPLICATION			=	'1',
			BACK_TO_MAIN_MENU			=	'2',
			CONTINUE					=	'3',
			REPLAY_LEVEL				=	'4',
			NEXT_LEVEL					=	'5'
		};
	};
};

#endif