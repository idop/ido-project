//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// main.cpp
// --------
// This is the main entry point of the program.
// Keep the main short!
//
// Author: Amir Kirsh
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
// Add these remarks also at the beginning and end of any new file that you add.
//
// Below lines are an example, replace it with your own if you make any changes (one entry per relevant change!)
// NOTE: the lines shall be added in the file that was changed only!
//
// 2014-12-15     Yovav Ben-Shimshon      implemented the menu
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "GameManager.h"
#include "io_utils.h"
#include "TheMathGame.h"
using namespace std;

// this is for example only!
// delete this class and implement your own properly!

///*
//==========================
//  M  A  I  N
//==========================
int main(){
	srand((unsigned int)time(NULL));
	clear_screen();
	hideCursor();
	GameManager(TheMathGame(), 200, 2).run();
	return 0;
}
//==========================
// E n d   o f   M  A  I  N
//==========================
//*/
/*
#include "Equation.h"
#include "Point.h"
#include "Direction.h"
int main(){
	srand((unsigned int)time(NULL));
	clear_screen();
	hideCursor();
	Direction::value d,e;

	d = Direction::RIGHT;
	e = d;
	if (e == Direction::LEFT)
		cout << "OK" << endl;
	else
		cout << "fucking stupid" << endl;
	return 0;
}
*/