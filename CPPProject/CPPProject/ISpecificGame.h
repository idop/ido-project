//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ISpecificGame.h
// ---------------
// ISpecificGame is an abstract base class without any implementation.
// (We call such a class "interface" though there are no interfaces in C++).
// This class is the base class for any actual game that wants to be managed by GameManager.
// All relevant operations that GameManager needs from an actual game will be declared here, however specific operations
// which are specific for a certain game and are not generic will not be declared here.
// NOTE that this class doesn't have any cpp file as there are NO actual implemenations, only signatures.
//
// Authors: Amir Kirsh, Iris Gaber
// First version: 2014-12-09
// 
// This code is part of a solution for "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// In the file itself, add above each change/addition a remark saying: "NEW CODE EX1, author=<name>, date=<YYYY-MM-DD>"
// and close it at the end with a remark saying "END of NEW CODE EX1" 
//2015-04-10	 Ido Perry	And Alex Odessr			 changed ISpecificGame function start level to send the current level to the game
//2015-04-10	 Ido Perry	And Alex Odessr			 added const for max level
//2015-04-10	 Ido Perry	And Alex Odessr			 added resumeLevel Function
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef _ISPECIFIC_GAME_H_
#define _ISPECIFIC_GAME_H_

#include <list>

using namespace std;

//NEW CODE EX1!! 2015-04-10	 Ido Perry And Alex Odessr added const for max level
const unsigned int MAX_LEVEL = 40;
//END of NEW CODE EX1

// this is a base class for actual games
// actual games will inherit from this class and implement the required methods
class ISpecificGame
{
public:
	// virtual fucnction with =0 is called an "abstract method"
	// abstract method must be implemented by non-abstract inherited class
	virtual bool isLevelDone()const=0;
	virtual bool hasNextLevel()const=0;
	//NEW CODE EX1!! 2015-04-10	 Ido Perry And Alex Odessr  changed ISpecificGame function start level to send the current level to the game
	virtual void startLevel(unsigned int level)=0; 
	//END of NEW CODE EX1
	//NEW CODE EX1!! 2015-04-10	 Ido Perry And Alex Odessr  added  function  to resume the game (after sub menu action continue)
	virtual void ResumeLevel() = 0;
	//END of NEW CODE EX1
	
	// get a list with keyHits and returns a list with the keys that were used
	virtual void doIteration(const list<char>& keyHits)=0;
	virtual void doSubIteration()=0;
};

#endif