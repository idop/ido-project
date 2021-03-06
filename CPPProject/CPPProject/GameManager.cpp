//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// GameManager.cpp
// ---------------
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
// In the file itself, add above each change/addition a remark saying: "NEW CODE EX1, author=<name>, date=<YYYY-MM-DD>"
// and close it at the end with a remark saying "END of NEW CODE EX1" 
//2015-04-10	 Ido Perry	And Alex Odesser			 removed the end level notification from this object and moved it to the TheMathGame object
//2015-04-10	 Ido Perry	And Alex Odesser			 changed ISoecificGame function start level to send the current level to the game
//2015-04-10     Ido Perry  And Alex Odesser             handle all main manu option
//2015-04-10	 Ido Perry	And Alex Odesser			 added print insturctions fucntion
//2015-04-10     Ido Perry  And Alex Odesser             clear screen after game ended
//2015-04-10     Ido Perry  and Alex Odesser             added function to show make a sub menu
//2015-04-10     Ido Perry  and Alex Odesser             print sub manu in esc press
//2015-04-10     Ido Perry  and Alex Odesser             handle sub manu options
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <list>
#include "GameManager.h"
#include "ISpecificGame.h"
#include "io_utils.h"
#include "Color.h" //added color.h for menus color change

using namespace std;

char GameManager::mainMenu()const
{
	// TODO: you may want to improve the menu appearance
	cout << "1. instructions" << endl;
	cout << "2. play game" << endl;
	cout << "3. start from a specific level" << endl;
	cout << "9. exit" << endl;
	char selection = 0;
	do {
		selection = _getch();
	} while(!GameManager::MainMenuOptions::isValidOption(selection));
	return selection;
}

//NEW CODE EX 12015-04-10      Ido Perry and Alex Odesser        added function to show make a sub menu
void GameManager::subMenu()const
{

	clear_screen();
	cout << "1. Exit game" << endl;
	cout << "2. Return to main manu" << endl;
	cout << "3. return to level" << endl;
	cout << "4. restart level" << endl;
	cout << "5. start level" << endl;
}
//END of NEW CODE EX1

void GameManager::run()
{
	bool userWantsToPlay = true;
	// we run as long as the user wants
	while(userWantsToPlay) {
		char menuSelection = mainMenu();
		//NEW CODE EX1 Ido Perry and Alex Odesser 2015-04-10  handle all main manu option
		switch(menuSelection)
		{
		case GameManager::MainMenuOptions::PLAY_GAME:
			init();
			userWantsToPlay = playGame();
			break;
		case GameManager::MainMenuOptions::PRESENT_INSTRUCTIONS:
			PrintInsturctions();	
			while (!_kbhit()){}
			clear_screen();
			userWantsToPlay = true;
			break;
		case GameManager::MainMenuOptions::PLAY_FROM_SELECTED_SCREEN:
			int num;
			clear_screen();
			cout << "Please enter a level number between 1 to " << MAX_LEVEL <<": ";
			cin >> num;
			while (num < 1 || num > MAX_LEVEL)
				{
					clear_screen(); 
					cout << "Invalid level Please enter a level number between 1 to " << MAX_LEVEL << ": ";
					cin >> num;
				}
			init(num);
			userWantsToPlay = playGame(); //END of NEW CODE EX1
			break;
		case GameManager::MainMenuOptions::EXIT_APPLICATION:
			userWantsToPlay = false;
			break;
		default: // normally we shouldn't get to here...
			userWantsToPlay = false;
		}
	}
}

bool GameManager::playGame()
{
	// we assume that we have multiple levels so there is a need to loop through levels
	// till all levels were played or till user quits - if user quits we do not continue to next level
	//-------------------------------------------------------------
	// this is the game LEVELS loop
	//-------------------------------------------------------------
	char action = GameManager::LevelOptions::NEXT_LEVEL;
	while(actualGame.hasNextLevel() && action == GameManager::LevelOptions::NEXT_LEVEL) {
		action = playNextLevel();
	}
	//-------------------------------------------------------------
	// END of game LEVELS loop
	//-------------------------------------------------------------
	
	// return true if the user wants to keep playing
	//NEW CODE EX1 Ido Perry and Alex Odesser 2015-04-10  clear screen after game ended
	clear_screen(); 
	//END of NEW CODE EX1
	return (action != GameManager::LevelOptions::EXIT_APPLICATION);
}

// return action to take in case of ESC
char GameManager::playNextLevel()
{
	++currentLevel;
	actualGame.startLevel(currentLevel);
	
	//------------------------------------------------------------------------------
	// here we control the ESC menu
	//------------------------------------------------------------------------------
	bool keepRunning = true;
	char action = 0;
	while(keepRunning)
	{
		//=============================================================================================
		// this is the actual call to play game iterations
		action = doLevelIterations();
		//=============================================================================================
		//NEW CODE EX1 Ido Perry and Alex Odesser 2015-04-10  handle all sub manu options
			// check action based on game ended (action==BACK_TO_MAIN_MENU) or input from user on ESC menu
		switch (action) {
		case GameManager::LevelOptions::CONTINUE:
			// keepRunning is true, so we only need resume the level
			actualGame.ResumeLevel();
			break;
		case GameManager::LevelOptions::REPLAY_LEVEL:
			// keepRunning is true, so we only need to set thing right and then - keepRunning!
			//--------------------------------------------------------------------------------
			actualGame.startLevel(currentLevel);
			break;
		case GameManager::LevelOptions::BACK_TO_MAIN_MENU:
			clear_screen();
			keepRunning = false;
			break;
		case GameManager::LevelOptions::EXIT_APPLICATION:
			// get out from the loop
			clear_screen();
			keepRunning = false;
			break;
		case GameManager::LevelOptions::NEXT_LEVEL:
			// get out from the loop so we get to the next level
			keepRunning = false;
			break;
		}
		//END OF NEW CODE EX 1
		//---------------------------------------
		// END of sub menu action switch
		//---------------------------------------
	}
	//------------------------------------------
	// END of Level keepRunning loop (sub menu)
	//------------------------------------------

	// the actions that may get out from this method are: BACK_TO_MAIN_MENU and EXIT_APPLICATION
	return action;
}

// return action to take in case of ESC
char GameManager::doLevelIterations()
{
	char action;
	bool escapePressed = false;
	//---------------------------------------
	// this is the game iterations loop
	//---------------------------------------
	while(!actualGame.isLevelDone() && !escapePressed) {
		escapePressed = !doIteration();
	}
	//-----------------------------------------------------
	// END of game iterations loop or exit on ESC
	//-----------------------------------------------------

	// check why we are here
	if(actualGame.isLevelDone()) {
	  //NEW CODE EX1, author=Ido Perry and Alex Odesser date=2015-04-10 removed the end level notification from this object and moved it to the TheMathGame object
		action = GameManager::LevelOptions::NEXT_LEVEL;
	  //END of NEW CODE EX1
	}
	else if(escapePressed) {

		action = 0;
		//NEW CODE EX1 Ido Perry and Alex Odesser 2015-04-10  create the sub menu on esc Press
		subMenu();
 
		do {
			action = _getch();
		} while(!GameManager::LevelOptions::isValidOption(action));
		clear_screen();
		//END OF NEW CODE EX 1
	}
	// end of esc pressed
	
	return action;
}

bool GameManager::doIteration()
{
	unsigned int sleepLength = clockCycleInMillisec/iterationsPerClockCycle;
	for(unsigned int i=0; i<iterationsPerClockCycle-1; ++i) {
		Sleep(sleepLength);
		actualGame.doSubIteration();
	}
	return doInputIteration();
}

bool GameManager::doInputIteration()
{
	list<char> keyHits(KEYBOARD_HIT_LOOP); // set vector initialize size to the max key strokes that we may collect
	bool shouldContinue = true;
	// get keyboard input in a loop, to get enough keyboard hits
	unsigned int sleepLength = clockCycleInMillisec/iterationsPerClockCycle / KEYBOARD_HIT_LOOP;
	for(unsigned int i=0; i<KEYBOARD_HIT_LOOP; ++i) {
		Sleep(sleepLength);
		if (_kbhit()) {
			char ch = _getch();
			if(ch == ESC) {
				// ESC pressed
				shouldContinue = false;
			}
			else {
				// we got keyHits byref, so we actually set input into the original list sent here
				keyHits.push_front(ch); // we want recent keys to come first, thus we use push_front
			}
		}
	}
	// send the keystrokes to the game
	// (even if ESC was hit, we may still have something in the keystrokes vector and should use it)
	actualGame.doIteration(keyHits);

	return shouldContinue;
}

//NEW CODE EX1 Ido Perry and Alex Odesser 2015-04-10  added function to print the insturctions page
void GameManager::PrintInsturctions()
{
	clear_screen();
	cout << "Welcome to the amazing math Game." << endl;
	cout << "This is a two player console game with 20 levels" << endl;
	cout << "Player 1: starts at the left of the screen and is represented by the char @." << endl;
	cout << "Player 2: starts at the right of the screen and is represented by the char #." << endl;
	cout << "on the start of the level an equation will be generated to each player." << endl;
	cout << "Player 1 equation will be shown at the top left of the screen" << endl;
	cout << "and player 2 equation will be shown at the top right of the screen." << endl; 
	cout << "Each equation will hide one of its numbers and the player" << endl;
	cout << "will need to solve the equation in order to finish the level." << endl;
	cout << "Possible solution to 1 of the equatiosn will be placed" << endl;
	cout << "randomly on the screen every other turn." << endl; 
	cout << "The players will be in constant movement, they will move tile each turn." << endl;
	cout << "player 1 movement controls  are : a - left, w - up, d - right , x - down " << endl;
	cout << "player 2 movement controls  are : j - left, i - up, l - right , m - down " << endl;
	cout << "Each Player starts the level with 3 lives." << endl;
	cout << "the players will try to move to a solution. If a player got the right number " << endl;
	cout << "his score will increase by 1 and the level will end." << endl;
	cout << "However wrong solution will cause the player to lose a live and when" << endl;
	cout << "the lives reach 0 the player will be thrown out of the current level." << endl;
	cout << "Have Fun!!!!!!!!!" << endl << endl;
	cout << "press any key to return to main menu" << endl;

}
//END of NEW CODE EX1